//
// Created by michal on 23-03-2018.
//

#ifndef GUI_MAINWINDOW_H
#define GUI_MAINWINDOW_H

#include <gtkmm.h>
#include <iostream>
#include <opencv2/core/mat.hpp>
#include "Controller.h"

class Controller;
class Picture;

class MainWindow
{
    friend class MainApp;

private:

    const Glib::ustring mainWindowName_ = "appWindow";

    Gtk::Window *window_ ;

    Gtk::Button *exitButton_;

    explicit MainWindow (Controller &pController);

    virtual ~MainWindow ();

protected:


public:

    bool update(Picture *picture);

    Glib::RefPtr<Gdk::Pixbuf> convertOpenCv2Gtk (cv::Mat *src, int dst_w, int dst_h);

    void refreshDrawingArea (std::string widgetName, cv::Mat *src);

};


#endif //GUI_MAINWINDOW_H
