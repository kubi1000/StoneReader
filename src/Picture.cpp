//
// Created by michal on 24-03-2018.
//

#include "Picture.h"

void Picture::setFilePath(std::string &&path) {

    filePath_ = path;

    if(!filePath_.empty())
    {
        pictures_.push_back(cv::imread(filePath_));
    }
    pictures_.push_back(pictures_[0]);

}
