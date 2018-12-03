//
// Created by michal on 27-05-2018.
//

#ifndef GUI_HISTOGRAMWINDOW_H
#define GUI_HISTOGRAMWINDOW_H

#include "MainApp.h"

class HistogramWindow
{
    Gtk::Window *histWindow_;

    Gtk::Image *histImage_;

public:

    void loadFromFile(const std::string &);

    void showWindow();

    HistogramWindow();

    ~HistogramWindow();
};


#endif //GUI_HISTOGRAMWINDOW_H
