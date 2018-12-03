//
// Created by michal on 05-04-2018.
//

#ifndef GUI_CONTROLER_H
#define GUI_CONTROLER_H

#include <iostream>
#include "Picture.h"
#include "MainApp.h"

struct ProcessParameters;
class HistogramDialogWindow;
class MainWindow;
class HistogramWindow;

class Controller : public sigc::trackable {

private:

    Picture *picture_;

    HistogramDialogWindow *histogramDialog_ = nullptr;

    MainWindow *mainWindow_ = nullptr;

    HistogramWindow *histogramWindow_ = nullptr;

    int numberOfContours_;

public:

    static bool draw_;

    explicit Controller(Picture *picture) : picture_(picture) {}

    virtual ~Controller(){}

    virtual void on_btnMainDialogFileOpen_clicked(Gtk::FileChooserDialog *);

    virtual void on_btnMainQuit_clicked(Gtk::Window *);

    virtual void startProcessing(const ProcessParameters &);

    void refactorScale(gdouble &);

    void generateHistogram();

    void on_entryScale_changed(Gtk::Entry *);

    void on_entryNumberOfBeans_changed(Gtk::Entry *);

    void on_btnScale_clicked();

    void on_checkPrintHistogram_toggled();

    void getGuiContact(HistogramDialogWindow &pHist, MainWindow &pMain, HistogramWindow &pHistWind)
    {
        histogramDialog_ = &pHist;

        mainWindow_ = &pMain;

        histogramWindow_ = &pHistWind;
    }

};


#endif //GUI_CONTROLER_H
