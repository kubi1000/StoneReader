//
// Created by michal on 24-03-2018.
//

#ifndef GUI_PICTURE_H
#define GUI_PICTURE_H

#include <opencv2/core/core.hpp>
#include <opencv2/opencv.hpp>
#include <gdk-pixbuf/gdk-pixbuf.h>
#include <vector>
#include <iostream>
#include <cmath>
#include <thread>
#include <future>
#include <sys/stat.h>

#include "MainWindow.h"

struct ProcessParameters;

struct AreaTable
{
    double max;

    double min;

    std::map<double,int> map;

};

class Picture {

private:

    std::string filePath_;

    std::vector <cv::Mat> pictures_;

    static double scale_;

    static unsigned int scaleFactor_;

    static unsigned int nbOfBins_;

    std::vector<double> areaVector_;

    double max_{};

    double min_{};

    std::map<double,int> histogram_;

    bool insertAreasInTable(double, AreaTable &);

    bool fillHistogram(const AreaTable &, int &);

public:

    Picture() = default;

    virtual ~Picture() = default;

    void setFilePath(std::string &&path);

    const std::vector <cv::Mat> &getPictures () const {  return pictures_; }

    void automaticBrightContrast();

    void morphOperations(const ProcessParameters &);

    void processWithNewParam();

    void clearVector();

    void performThresholding(const ProcessParameters &);

    int watershedSegmentation(const ProcessParameters &);

    static void setScale(double &);

    static void setScaleFactor(int sf) { scaleFactor_ = static_cast<unsigned int>(sf);}

    static void setNumberOfBins(int nbOB) { nbOfBins_ = static_cast<unsigned int>(nbOB + 1);}

    std::string createHistogram(int);

    void drawHistogram(const std::string&, int);

    void calculateArea(size_t);

    bool isProcessed();

    bool hasPicture();
};


#endif //GUI_PICTURE_H
