//
// Created by michal on 23-04-2018.
//

#ifndef GUI_HISTOGRAMDIALOGWINDOW_H
#define GUI_HISTOGRAMDIALOGWINDOW_H


#include "Controller.h"

class HistogramDialogWindow
{
private:

    Gtk::Window *histogramWindow_ = nullptr;

    Gtk::Entry *entryScale_ = nullptr;

    Gtk::Button *btnScale_ = nullptr;

    Gtk::ToolButton *btnHistogram_ = nullptr;

    Gtk::Button *btnGenerateHistogram_ = nullptr;

    Gtk::Entry *entryNumberOfBeans_ = nullptr;

    Gtk::CheckButton *checkPrintHistogram_ = nullptr;

    Controller *controller_ = nullptr;

    Gtk::Label *lblFirstPoint_ = nullptr;

    Gtk::Label *lblSecondPoint_ = nullptr;

    Gtk::Label *lblLength_ = nullptr;

public:

    explicit HistogramDialogWindow(Controller &controller);

    ~HistogramDialogWindow();

    void showHistogramWindow();

    void on_btnGenerateHistogram_clicked();

    void setLabels(double);

    void setLabels(double, double);

    void switchVisibility();
};


#endif //GUI_HISTOGRAMDIALOGWINDOW_H
