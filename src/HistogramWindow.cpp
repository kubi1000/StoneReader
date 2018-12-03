//
// Created by michal on 27-05-2018.
//

#include "HistogramWindow.h"

HistogramWindow::HistogramWindow()
{
    SRefBuilder::getRefBuilder()->get_widget("histWindowDisplay",histWindow_);

    SRefBuilder::getRefBuilder()->get_widget("histImage",histImage_);
}

HistogramWindow::~HistogramWindow()
{
    delete histWindow_;
}

void HistogramWindow::loadFromFile(const std::string &filePath)
{
    showWindow();

    histImage_->set(filePath);
}

void HistogramWindow::showWindow()
{
    histWindow_->set_visible(true);

}
