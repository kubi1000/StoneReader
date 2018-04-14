//
// Created by michal on 24-03-2018.
//

#include "Picture.h"

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

void Picture::convert2Binary(const processParameters &parameters) {

    auto lastPicture = pictures_.size() - 1;

    cv::Mat matrix = pictures_.at(lastPicture).clone();

    matrix.convertTo(matrix,CV_8U);

    /*
     *     CV_SHAPE_RECT      =0,
     *     CV_SHAPE_CROSS     =1,
     *     CV_SHAPE_ELLIPSE   =2,
     *
     */

    int morph_type = parameters.structuringElementParams[0] - 1;

    int morph_size = parameters.structuringElementParams[1];

    double threshold_value=0;

    cv::cvtColor(matrix,matrix,CV_BGR2GRAY);

        //cv::Mat kernel = cv::Mat::ones(3,3,CV_8UC1);

    cv::Mat kernel = cv::getStructuringElement(morph_type,cv::Size(1+morph_size*2,1+morph_size*2),
                                                   cv::Point(morph_size,morph_size));

    std::cout<<kernel;

    //cv::morphologyEx(matrix,matrix,2,kernel);

    cv::morphologyEx(matrix,matrix,CV_MOP_CLOSE,kernel);

    cv::morphologyEx(matrix,matrix,CV_MOP_OPEN,kernel);

    cv::morphologyEx(matrix,matrix,CV_MOP_DILATE,kernel);

    for(int i =1; i <10 ; i+=2)
    {
        cv::medianBlur(matrix,matrix,i);
    }

    pictures_.push_back(matrix);
}

void Picture::clearVector()
{
    pictures_.clear();

}
