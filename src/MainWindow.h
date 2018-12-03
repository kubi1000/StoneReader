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

enum DisplayChooser
{
    RESULTS = 7,
    WATERSHED_RES = 6,
    HISTOGRAM_EQ = 1,
    ORIGINAL_PIC = 0,
    MORPHOLOGICAL_OP = 2,
    THRESHOLD_CONV = 3,
    DISTANCE_TRANSF = 4
};

struct ProcessParameters
{
    int elementType_;

    int elementSize_;

    bool blackGrains_;

    double thresholdMaxValue_;

    double threshodValue_;

    bool automaticThresh_;

    bool repeatMorph_;

    std::vector<int> operationOrder_;

    int distance_;

    double normalize_;

    double minThreshold;

    int lowerLimit_;

    int upperLimit_;
};

class MainWindow : public Gtk::Window
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

    Gtk::Scale *scaleThreshold_;

    Gtk::CheckButton *checkBlackGrains_;

    Gtk::Scale *scaleMaxValue_;

    Gtk::ComboBox *displayChooser_;

    Gtk::DrawingArea *mainDrawingArea_;

    Gtk::CheckButton *checkAutomaticThresh_;

    Gtk::CheckButton *checkOpening_;

    Gtk::CheckButton *checkClosing_;

    Gtk::ToggleButton *toggleReverse_;

    Gtk::Scale *scaleDistance_;

    Gtk::Scale *scaleNormalize_;

    Gtk::Scale *scaleMinThreshold_;

    Gtk::Entry *entryLower_;

    Gtk::Entry *entryUpper_;

    ProcessParameters parameters;

    bool drawingControl_ = false;

    explicit MainWindow (Controller &pController);

    virtual ~MainWindow ();

    void on_scaleElementSize_value_changed();

    void on_scaleElementType_value_changed();

    void on_btnStart_clicked();

    void on_displayChooser_changed();

    void on_scaleThreshold_value_changed();

    void on_scaleMaxValue_value_changed();

    gboolean on_drawing2_button_press_event(GdkEventButton *event);

    void checkBlackGrains_toggled_cb();

    void checkAutomaticThresh_toggled_cb();

    void queueMorphologicalOperations();

    void on_scaleDistance_value_changed();

    void on_scaleNormalize_value_changed();

    void on_scaleMinThreshold_value_changed();

    void on_entryLower_changed();

    void on_entryUpper_changed();

public:

    static int currentDisplayChooser_;

    const ProcessParameters &getProcessParameters() const { return parameters; }

    bool update(Picture *picture);

    Glib::RefPtr<Gdk::Pixbuf> convertOpenCv2Gtk (cv::Mat *src, int dst_w, int dst_h, int code);

    void refreshDrawingArea (std::string widgetName, cv::Mat *src, int code = CV_BGR2RGB);

    void switchDrawingEvent();

    Gtk::Window &getWindow() {return *window_;}

};

#endif //GUI_MAINWINDOW_H
