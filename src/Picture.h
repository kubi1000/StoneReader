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

#include "DialogFileOpen.h"

/* As model it should not contains any objects from view or controller */



class Picture {

private:

    // Attributes
    std::string filePath_;

    std::vector <cv::Mat> pictures_;

    // Methods

    void loadFile();

public:

    //Attributes

    //Methods

    Picture(){}

    virtual ~Picture(){}

    void setFilePath(std::string &&path);

    const std::vector <cv::Mat> &getPictures () const {  return pictures_; }
};


#endif //GUI_PICTURE_H
