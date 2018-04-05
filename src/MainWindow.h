//
// Created by michal on 23-03-2018.
//

#ifndef GUI_MAINWINDOW_H
#define GUI_MAINWINDOW_H

#include <gtkmm.h>
#include <iostream>
#include <opencv2/core/mat.hpp>

class MainWindow{
    friend class MainApp;
    friend void  runApplication();
private:
    const Glib::ustring mainWindowName_ ="appWindow";
    Gtk::Window *window_ ;
    Gtk::Button *exitButton_;
    Gtk::DrawingArea *originalDrawing_;
protected:
    MainWindow();
    virtual ~MainWindow();
    void on_btnMainQuit_clicked();
public:
    static void refreshDrawingArea( char *widgetName, cv::Mat *src);
};


#endif //GUI_MAINWINDOW_H
