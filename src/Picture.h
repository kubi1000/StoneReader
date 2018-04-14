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

#include "MainWindow.h"

/* As model it should not contains any objects from view or controller */
struct processParameters;

class Picture {

private:

    // Attributes

    std::string filePath_;

    std::vector <cv::Mat> pictures_;

    // Methods

public:

    //Attributes

    //Methods

    Picture() = default;

    virtual ~Picture() = default;

    void setFilePath(std::string &&path);

    const std::vector <cv::Mat> &getPictures () const {  return pictures_; }

    void automaticBrightContrast();

    void convert2Binary(const processParameters &);

    void clearVector();


};


#endif //GUI_PICTURE_H
