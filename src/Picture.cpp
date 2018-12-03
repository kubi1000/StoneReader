//
// Created by michal on 24-03-2018.
//
#include "Picture.h"
#include "gnuplot_i.hpp"

double Picture::scale_ = 1;
unsigned int Picture::scaleFactor_ = 20;
unsigned int Picture::nbOfBins_ = 4;

void Picture::setFilePath(std::string &&path)
{
    filePath_ = path;

    if(!filePath_.empty())
    {
        pictures_.push_back(cv::imread(filePath_));
    }
}

void Picture::automaticBrightContrast()
{
    cv::Mat lab_img;

    auto &src = pictures_.at(0);

    cv::cvtColor(src,lab_img,CV_BGR2Lab);

    std::vector<cv::Mat> lab_imgs(3);

    cv::split(lab_img,lab_imgs);

    auto clahe = cv::createCLAHE();

    clahe->setClipLimit(4);

    cv::Mat dest;

    clahe->apply(lab_imgs[0],dest);

    dest.copyTo(lab_imgs[0]);

    cv::merge(lab_imgs,lab_img);

    cv::Mat temp;

    cv::cvtColor(lab_img,temp,CV_Lab2BGR);

    pictures_.push_back(temp);
}

void Picture::morphOperations(const ProcessParameters &parameters) {


    cv::Mat matrix;

    matrix = pictures_.at(DisplayChooser::HISTOGRAM_EQ).clone();

    matrix.convertTo(matrix,CV_8U);

    int morph_type = parameters.elementType_;

    int morph_size = parameters.elementSize_;

    cv::Mat kernel = cv::getStructuringElement(morph_type,cv::Size(1+morph_size*2,1+morph_size*2),
                                                   cv::Point(morph_size,morph_size));

    for(const auto & x : parameters.operationOrder_)
    {
        cv::morphologyEx(matrix,matrix,x,kernel);
    }
    pictures_.push_back(matrix);
}

void Picture::clearVector()
{
    pictures_.clear();
}

void Picture::performThresholding(const ProcessParameters &parameters)
{
    cv::Mat dst;

    cv::cvtColor(pictures_.at(DisplayChooser::MORPHOLOGICAL_OP),dst,CV_BGR2GRAY);

    if(parameters.blackGrains_)
    {
        cv::bitwise_not(dst,dst);
    }

    dst.convertTo(dst,CV_8UC3);

    if(parameters.automaticThresh_)
    {
        cv::threshold(dst,
                          dst,
                              parameters.threshodValue_,
                                  parameters.thresholdMaxValue_,
                                      CV_THRESH_BINARY | CV_THRESH_OTSU);
    }
    else
    {
        cv::threshold(dst,
                          dst,
                              parameters.threshodValue_,
                                  parameters.thresholdMaxValue_,
                                      CV_THRESH_BINARY);
    }

    auto top = (int) (0.005*dst.rows);
    auto bottom = top;
    auto left = (int) (0.005*dst.cols);
    auto right = left;

    cv::Scalar color = {0,0,0};

    cv::copyMakeBorder(dst ,dst, top, bottom, left, right, cv::BORDER_CONSTANT, color);

    pictures_.push_back(dst);
}

int Picture::watershedSegmentation(const ProcessParameters &parameters)
{
    cv::Mat dist, kernel;

    kernel = cv::Mat::ones(3,3,CV_8UC1);

    cv::distanceTransform(pictures_.at(DisplayChooser::THRESHOLD_CONV),dist,CV_DIST_L2,parameters.distance_);

    pictures_.push_back(dist);

    cv::normalize(dist,dist,0,parameters.normalize_,cv::NORM_MINMAX);

    cv::threshold(dist, dist, parameters.minThreshold, parameters.normalize_, CV_THRESH_BINARY);

    kernel = cv::Mat::ones(3,3,CV_8UC1);

    cv::dilate(dist,dist,kernel);

    pictures_.push_back(dist);

    cv::Mat dist_8u;

    dist.convertTo(dist_8u,CV_8U);

    std::vector<std::vector<cv::Point>> contours;

    cv::findContours(dist_8u,contours,CV_RETR_EXTERNAL,CV_CHAIN_APPROX_NONE);

    cv::Mat markers = cv::Mat::zeros(dist.size(),CV_32SC1);

    for (size_t i = 0; i < contours.size(); i++)
    {
        auto temp = cv::contourArea(contours[i]);
        if(temp < parameters.lowerLimit_) continue;
        if(temp > parameters.upperLimit_) continue;
        cv::drawContours(markers,contours, static_cast<int>(i),cv::Scalar::all(static_cast<int>(i)+1),-1);
    }

    cv::circle(markers,cv::Point(5,5),3,CV_RGB(255,255,255),-1);

    cv::Mat gray2Bgr = pictures_.at(DisplayChooser::THRESHOLD_CONV).clone();

    cv::cvtColor(gray2Bgr, gray2Bgr, CV_GRAY2BGR);

    cv::watershed(gray2Bgr,markers);

    pictures_.push_back(markers);

    cv::Mat mark = cv::Mat::zeros(markers.size(),CV_8UC1);

    markers.convertTo(mark,CV_8UC1);

    cv::bitwise_not(mark,mark);

    std::vector<cv::Vec3b> colors;

    for (size_t i = 0; i < contours.size(); i++)
    {
        int b = cv::theRNG().uniform(0, 255);
        int g = cv::theRNG().uniform(0, 255);
        int r = cv::theRNG().uniform(0, 255);
        colors.emplace_back((uchar)b, (uchar)g, (uchar)r);
    }

    cv::Mat dst = cv::Mat::zeros(markers.size(), CV_8UC3);

    for (int i = 0; i < markers.rows; i++)
    {
        for (int j = 0; j < markers.cols; j++)
        {
            int index = markers.at<int>(i,j);
            if (index > 0 && index <= static_cast<int>(contours.size()))
                dst.at<cv::Vec3b>(i,j) = colors[index-1];
            else
                dst.at<cv::Vec3b>(i,j) = cv::Vec3b(0,0,0);
        }
    }

    pictures_.push_back(dst);

    return static_cast<int>(contours.size());

}

void Picture::calculateArea(size_t contoursNumber)
{
    auto watershed_result = pictures_.at(DisplayChooser::WATERSHED_RES).clone();

    areaVector_.clear();

    std::vector<std::vector<cv::Point>> contour;

    for(unsigned int i = 1; i < contoursNumber + 1; i++)
    {
        cv::Mat separate;

        watershed_result.copyTo(separate, (watershed_result == i));

        separate.convertTo(separate,CV_8U);

        if(separate.empty()) continue;

        cv::findContours(separate, contour,CV_RETR_EXTERNAL,CV_CHAIN_APPROX_SIMPLE);

        if(!contour.empty())
        {
            auto area = cv::contourArea(contour[0]);

            areaVector_.push_back(area);
        }
    }
}

void Picture::processWithNewParam()
{
    auto temp = pictures_.at(0).clone();

    clearVector();

    pictures_.push_back(temp);
}

void Picture::setScale(double &scale)
{
    scale_ = scale;
}

std::string Picture::createHistogram(int contoursNumber)
{
    calculateArea(static_cast<size_t>(contoursNumber));

    AreaTable areaTable;

    areaTable.max = std::numeric_limits<decltype(areaTable.max)>::lowest();

    areaTable.min = std::numeric_limits<decltype(areaTable.min)>::max();

    std::transform(std::begin(areaVector_),std::end(areaVector_),std::begin(areaVector_),
    [](auto & item) -> double
    {
        auto temp = pow(scaleFactor_,2) * item / pow(scale_,2);

        return temp;
    });

    for(auto &x : areaVector_)
    {
        insertAreasInTable(x,areaTable);
    }

    max_ = areaTable.max;

    min_ = areaTable.min;

    auto range = -1;

    if(!fillHistogram(areaTable, range))
    {
        std::cerr << "Picture: Failed to fill histogram\n";

        return nullptr;
    }

    std::vector<std::string> separatedFilePath;

    std::istringstream is(filePath_);

    std::string string;

    while(getline(is,string,'/'))
    {
        separatedFilePath.push_back(string);
    }

    std::string fileName = separatedFilePath.back();

    std::ofstream histogramCsv;

    struct stat sb{};

    if(!(stat(fileName.c_str(), &sb ) == 0 && S_ISDIR(sb.st_mode)))
    {
        auto result = mkdir(fileName.c_str(),0777);

        if(result == -1)
        {
            std::cerr << "Picture: Could not create directory.\n";

            return nullptr;
        }

    }

    histogramCsv.open(fileName + "/" + fileName + ".histogram.csv", std::ios::out);

    std::string histogramName = fileName + "/" + fileName + ".histogram.png";

    histogramCsv << "Field ranges in [um2],Amount" << std::endl;

    for(const auto & x : histogram_)
    {
        histogramCsv << x.first << "," << x.second << std::endl;
    }

    histogramCsv << ",,,Areas in pixels" << std::endl;

    for(const auto & x : areaVector_)
    {
        histogramCsv << ",,," << x << std::endl;
    }

    std::thread drawing(&Picture::drawHistogram,this,std::ref(fileName),std::ref(range));

    drawing.join();

    histogram_.clear();

    return histogramName;
}

bool Picture::insertAreasInTable(double val, AreaTable &areaTable)
{
    auto search = areaTable.map.find(val);

    if(search != std::end(areaTable.map))
    {
        areaTable.map.at(val) += 1;

        return true;
    }
    else
    {
        std::pair<double ,int> p (val,1);

        auto result = areaTable.map.insert(p);

        if(!result.second)
        {
            return false;
        }

        areaTable.max = (val > areaTable.max ? val : areaTable.max);

        areaTable.min = (val < areaTable.min ? val : areaTable.min);

        return true;
    }
}

bool Picture::fillHistogram(const AreaTable &aT, int &interval)
{
     interval = static_cast<int>((max_ - min_) / (nbOfBins_ - 1));

    if(nbOfBins_ == areaVector_.size() || nbOfBins_ > areaVector_.size())
    {
        histogram_ = aT.map;

        return true;
    }
        // Creating ranges
    else
    {
        std::vector<int> ranges;

        ranges.push_back(min_);

        for (unsigned int i = 1; i < nbOfBins_; ++i)
        {
            ranges.push_back(static_cast<int &&>(min_ + interval * (i - 1)));
        }

        ranges.push_back(static_cast<int &&>(max_ + 1));

        for(auto & x : ranges)
        {
            std::pair<int,int> p (x,0);

            histogram_.insert(p);
        }

        for(const auto &itAll : aT.map)
        {
            for(auto itHist = std::begin(histogram_), itPrev = std::end(histogram_);
                    itHist != std::end(histogram_);
                        itPrev = itHist, ++itHist )
            {
                if(itAll.first < itHist->first)
                {
                    itPrev->second = itPrev->second + itAll.second;

                    break;
                }
            }
        }

        return !histogram_.empty();
    }

}

void Picture::drawHistogram(const std::string &fileName, int range)
{
    try
    {
        Gnuplot g;

        g.set_title("Histogram");

        g.set_style("boxes smooth freq lc rgb\"green\"");

        g.set_xlabel("Area [{um^2}]");

        g.set_ylabel("Amount [-]");

        std::vector<int> area,amount;

        for(const auto &x : histogram_)
        {
            amount.push_back(x.second);

            area.push_back(static_cast<int &&>(x.first + range/2));
        }

        g << "unset key\n";

        g << "set xtics rotate out\n";

        g << "set terminal png\n";

        g << "set style fill solid border\n";


        auto min = area.at(0) - range/2;

        auto max = area.at(area.size() - 1) - range/2;


        std::string xrange = "set xrange [" + std::to_string(min) + ":"
                             + std::to_string(max - 1)+ "]\n";

        g << xrange;

        g.set_xautoscale();

        g << "set offset graph 0.03,0.01,0.01,0";

        auto middle = static_cast<int>((max - min) / (nbOfBins_ - 1));

        std::string xtics = "set xtics " + std::to_string(min)
                            + "," + std::to_string(middle)
                            + "," + std::to_string(max) + "\n";

        g << xtics;

        g << "set style fill solid 0.5\n";

        g << "set tics out nomirror\n";

        const std::string outputCommand = "set output '" +
                fileName + "/" + fileName + ".histogram.png'\n";

        g << outputCommand;

        if(!area.empty() && !amount.empty())
        {
            g.plot_xy(area,amount);
        }
        else
        {
            std::cerr << "Picture: Cannot plot histogram. No data.\n";
        }

    }
    catch (const GnuplotException &e)
    {
        std::cerr << e.what() << std::endl;

        std::cerr << "Picture: Could not plot histogram\n";
    }
}

bool Picture::isProcessed()
{
    return !(pictures_.empty() || pictures_.size() < 2);
}

bool Picture::hasPicture()
{
    return !pictures_.empty();

}

