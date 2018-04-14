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

struct processParameters
{
    int structuringElementParams[2];
};

class MainWindow
{
    friend class MainApp;

private:

    Controller *controllerHandler_;

    const Glib::ustring mainWindowName_ = "appWindow";

    Gtk::Window *window_ ;

    Gtk::ToolButton *exitButton_;

    Gtk::Button *startButton_;

    Gtk::Scale *scaleElementSize_;

    Gtk::Scale *scaleElementType_;

    processParameters parameters;

    explicit MainWindow (Controller &pController);

    virtual ~MainWindow ();

    void on_scaleElementSize_value_changed();

    void on_scaleElementType_value_changed();

    void on_btnStart_clicked();

protected:


public:

    const processParameters &getProcessParameters() const { return parameters; }

    bool update(Picture *picture);

    Glib::RefPtr<Gdk::Pixbuf> convertOpenCv2Gtk (cv::Mat *src, int dst_w, int dst_h, int code);

    void refreshDrawingArea (std::string widgetName, cv::Mat *src, int code = CV_BGR2RGB);



};



#endif //GUI_MAINWINDOW_H
