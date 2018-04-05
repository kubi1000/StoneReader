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

    cv::Mat picture_;

    // Methods

    void loadFile();

public:

    //Attributes

    //Methods

    Picture(){}

    virtual ~Picture(){}

    static void setPicture();

    void setFilePath(std::string path);

    Glib::RefPtr<Gdk::Pixbuf> convertOpenCv2Gtk(cv::Mat *src,const int dst_w, const int dst_h);


};


#endif //GUI_PICTURE_H
