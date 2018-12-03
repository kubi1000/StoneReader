//
// Created by michal on 23-03-2018.
//

#include "MainWindow.h"

MainWindow::MainWindow(Controller &pController) : controllerHandler_(&pController)
{
    SRefBuilder::getRefBuilder()->get_widget(mainWindowName_,window_);

    SRefBuilder::getRefBuilder()->get_widget("btnMainQuit",exitButton_);

    SRefBuilder::getRefBuilder()->get_widget("btnStart",startButton_);

    SRefBuilder::getRefBuilder()->get_widget("scaleElementSize",scaleElementSize_);

    SRefBuilder::getRefBuilder()->get_widget("scaleElementType",scaleElementType_);

    SRefBuilder::getRefBuilder()->get_widget("scaleMaxValue",scaleMaxValue_);

    SRefBuilder::getRefBuilder()->get_widget("scaleThreshold",scaleThreshold_);

    SRefBuilder::getRefBuilder()->get_widget("displayChooser",displayChooser_);

    SRefBuilder::getRefBuilder()->get_widget("drawing2",mainDrawingArea_);

    SRefBuilder::getRefBuilder()->get_widget("checkBlackGrains",checkBlackGrains_);

    SRefBuilder::getRefBuilder()->get_widget("checkAutomaticThresh",checkAutomaticThresh_);

    SRefBuilder::getRefBuilder()->get_widget("checkOpening", checkOpening_);

    SRefBuilder::getRefBuilder()->get_widget("checkClosing", checkClosing_);

    SRefBuilder::getRefBuilder()->get_widget("toggleReverse", toggleReverse_);

    SRefBuilder::getRefBuilder()->get_widget("scaleDistance", scaleDistance_);

    SRefBuilder::getRefBuilder()->get_widget("scaleNormalize", scaleNormalize_);

    SRefBuilder::getRefBuilder()->get_widget("scaleMinThreshold", scaleMinThreshold_);

    SRefBuilder::getRefBuilder()->get_widget("entryLower",entryLower_);

    SRefBuilder::getRefBuilder()->get_widget("entryUpper",entryUpper_);

    if(exitButton_)
    {
        exitButton_->signal_clicked().connect
                (sigc::bind<Gtk::Window*>
                         (sigc::mem_fun(controllerHandler_,&Controller::on_btnMainQuit_clicked),
                             window_));
    }

    if(startButton_)
    {
        startButton_->signal_clicked().connect(sigc::mem_fun(*this, &MainWindow::on_btnStart_clicked));
    }

    if(scaleElementSize_ && scaleElementType_ && scaleMaxValue_ && scaleThreshold_)
    {
        scaleElementSize_->signal_value_changed().connect
                (sigc::mem_fun(*this, &MainWindow::on_scaleElementSize_value_changed));

        scaleElementType_->signal_value_changed().connect
                (sigc::mem_fun(*this, &MainWindow::on_scaleElementType_value_changed));

        scaleThreshold_->signal_value_changed().connect
                (sigc::mem_fun(*this, &MainWindow::on_scaleThreshold_value_changed));

        scaleMaxValue_->signal_value_changed().connect
                (sigc::mem_fun(*this, &MainWindow::on_scaleMaxValue_value_changed));
    }

    if(displayChooser_)
    {
        displayChooser_->signal_changed().connect
                (sigc::mem_fun(*this, &MainWindow::on_displayChooser_changed));
    }

    if(mainDrawingArea_)
    {
        mainDrawingArea_->add_events(Gdk::BUTTON_PRESS_MASK);

        mainDrawingArea_->signal_button_press_event().connect
                (sigc::mem_fun(*this, &MainWindow::on_drawing2_button_press_event));
    }

    if(checkBlackGrains_)
    {
        checkBlackGrains_->signal_toggled().connect
                (sigc::mem_fun(*this, &MainWindow::checkBlackGrains_toggled_cb));
    }

    if(checkAutomaticThresh_)
    {
        checkAutomaticThresh_->signal_toggled().connect
                (sigc::mem_fun(*this, &MainWindow::checkAutomaticThresh_toggled_cb));
    }

    if (checkOpening_ && checkClosing_ && toggleReverse_)
    {
        checkClosing_->signal_toggled().connect
                (sigc::mem_fun(*this, &MainWindow::queueMorphologicalOperations));

        checkOpening_->signal_toggled().connect
                (sigc::mem_fun(*this, &MainWindow::queueMorphologicalOperations));

        toggleReverse_->signal_toggled().connect
                (sigc::mem_fun(*this, &MainWindow::queueMorphologicalOperations));
    }

    if(scaleDistance_ && scaleNormalize_ && scaleMinThreshold_)
    {
        scaleDistance_->signal_value_changed().connect
                (sigc::mem_fun(*this, &MainWindow::on_scaleDistance_value_changed));

        scaleNormalize_->signal_value_changed().connect
                (sigc::mem_fun(*this, &MainWindow::on_scaleNormalize_value_changed));

        scaleMinThreshold_->signal_value_changed().connect
                (sigc::mem_fun(*this, &MainWindow::on_scaleMinThreshold_value_changed));
    }

    if(entryUpper_ && entryLower_)
    {
        entryUpper_->signal_changed().connect
                (sigc::mem_fun(*this, &MainWindow::on_entryUpper_changed));
        entryLower_->signal_changed().connect
                (sigc::mem_fun(*this, &MainWindow::on_entryLower_changed));
    }


    on_scaleElementType_value_changed();

    on_scaleElementSize_value_changed();

    on_scaleThreshold_value_changed();

    on_scaleMaxValue_value_changed();

    queueMorphologicalOperations();

    on_scaleDistance_value_changed();

    on_scaleNormalize_value_changed();

    on_scaleMinThreshold_value_changed();

    parameters.blackGrains_ = false;

    parameters.automaticThresh_ = true;

    parameters.repeatMorph_ = false;

    parameters.upperLimit_ = std::numeric_limits<int>::max();

    parameters.lowerLimit_ = std::numeric_limits<int>::lowest();

}

MainWindow::~MainWindow()
{
    delete window_;
}

void MainWindow::refreshDrawingArea(std::string widgetName, cv::Mat *src, int code )
{
    auto temp = src->clone();

    Gtk::DrawingArea *dA = nullptr;

    SRefBuilder::getRefBuilder()->get_widget(widgetName, dA);

    if(!dA)
    {
        std::cerr << "MainWindow: Failed to connect to drawing area\n";

        exit(1);
    }

    auto pix = convertOpenCv2Gtk(&temp,dA->get_allocation().get_width(),dA->get_allocation().get_height(),code);

    Cairo::RefPtr<Cairo::Context> context = dA->get_window()->create_cairo_context();

    Gdk::Cairo::set_source_pixbuf(context, pix);

    context->paint();
}

Glib::RefPtr<Gdk::Pixbuf>
MainWindow::convertOpenCv2Gtk (cv::Mat *src, int dst_w, int dst_h, int code) {

    cv::Mat *gtkMask = src;

    cv::Mat temp = *src;

    cv::cvtColor(*src,*gtkMask,code);

    Glib::RefPtr<Gdk::Pixbuf> pix = Gdk::Pixbuf::create_from_data (static_cast<const guint8 *>(gtkMask->data),
                                                                       Gdk::COLORSPACE_RGB,
                                                                           FALSE,
                                                                               8,
                                                                                   gtkMask->cols,
                                                                                       gtkMask->rows,
                                                                                           static_cast<int>(gtkMask->step));
    decltype (pix) rpix;

    rpix = pix->Gdk::Pixbuf::scale_simple (dst_h,dst_w,Gdk::INTERP_BILINEAR);

    return rpix;
}

int MainWindow::currentDisplayChooser_ = DisplayChooser::RESULTS;

bool MainWindow::update (Picture *picture)
{
    if (!picture->getPictures().empty()){

        auto temp = picture->getPictures().at(0).clone();

        refreshDrawingArea("drawing1",&temp);

        if (picture->getPictures().size()>1)
        {
            temp = picture->getPictures().at(static_cast<unsigned long>(currentDisplayChooser_));

            if (currentDisplayChooser_ == DisplayChooser::DISTANCE_TRANSF ||
                     currentDisplayChooser_ == DisplayChooser::THRESHOLD_CONV)
            {
                refreshDrawingArea("drawing2",&temp, CV_GRAY2RGB);
            }
            else if (currentDisplayChooser_ == DisplayChooser::MORPHOLOGICAL_OP ||
                         currentDisplayChooser_ == DisplayChooser::HISTOGRAM_EQ ||
                             currentDisplayChooser_ == DisplayChooser::RESULTS)
            {
                refreshDrawingArea("drawing2",&temp);
            }
        }
    }

    return true;
}

void MainWindow::on_scaleElementSize_value_changed()
{
    parameters.elementSize_ = static_cast<int>(scaleElementSize_->get_value());
}

void MainWindow::on_scaleElementType_value_changed()
{
    parameters.elementType_ = static_cast<int>(scaleElementType_->get_value());
}

void MainWindow::on_btnStart_clicked()
{
    controllerHandler_->startProcessing(getProcessParameters());
}

void MainWindow::on_displayChooser_changed()
{
    Glib::ustring id = displayChooser_->get_active_id();

    if (id == "displayHistogramEq")
    {
        currentDisplayChooser_ = DisplayChooser::HISTOGRAM_EQ;
    }
    else if (id == "displayResults")
    {
        currentDisplayChooser_ = DisplayChooser::RESULTS;
    }
    else if (id == "displayMorph")
    {
        currentDisplayChooser_ = DisplayChooser::MORPHOLOGICAL_OP;
    }
    else if (id == "displayDistance")
    {
        currentDisplayChooser_ = DisplayChooser::DISTANCE_TRANSF;
    }
    else if (id == "displayThreshold")
    {
        currentDisplayChooser_ = DisplayChooser::THRESHOLD_CONV;
    }

}

void MainWindow::on_scaleThreshold_value_changed()
{
    parameters.threshodValue_ = scaleThreshold_->get_value();
}

void MainWindow::on_scaleMaxValue_value_changed()
{
    parameters.thresholdMaxValue_ = scaleMaxValue_->get_value();
}

gboolean MainWindow::on_drawing2_button_press_event(GdkEventButton *event)
{

    if(event->type == GDK_BUTTON_PRESS && drawingControl_)
    {
        controllerHandler_->refactorScale(event->x);
    }

    return true;
}

void MainWindow::checkBlackGrains_toggled_cb()
{
    parameters.blackGrains_ = !parameters.blackGrains_;
}

void MainWindow::checkAutomaticThresh_toggled_cb()
{
    parameters.automaticThresh_ = !parameters.automaticThresh_;
}

void MainWindow::queueMorphologicalOperations()
{
    parameters.operationOrder_.clear();

    if(checkOpening_->get_active())
    {
        // 2 is CV_MOP_OPEN code
        parameters.operationOrder_.push_back(2);
    }
    if(checkClosing_->get_active())
    {
        // 3 is CV_MOP_CLOSE code
        parameters.operationOrder_.push_back(3);
    }
    if(toggleReverse_->get_active())
    {
        auto & x = parameters.operationOrder_;

        std::reverse(std::begin(x), std::end(x));
    }

}

void MainWindow::on_scaleDistance_value_changed()
{
    int temp[3] = {0,3,5};

    parameters.distance_ = temp[static_cast<size_t>(scaleDistance_->get_value())];

}

void MainWindow::on_scaleNormalize_value_changed()
{
    parameters.normalize_ = scaleNormalize_->get_value();
}

void MainWindow::on_scaleMinThreshold_value_changed()
{
    parameters.minThreshold = scaleMinThreshold_->get_value();
}

void MainWindow::switchDrawingEvent()
{
    drawingControl_ = !drawingControl_;
}

void MainWindow::on_entryUpper_changed()
{
    auto temp = entryUpper_->get_text();

    char *end;

    if(!temp.empty())
    {
        auto value =  static_cast<int>(std::strtol(temp.c_str(), &end, 10));

        if(value <=0)
        {
            value = 1;
        }

        parameters.upperLimit_ = value;
    }
    else
    {
        parameters.upperLimit_ = std::numeric_limits<int>::max();
    }

}

void MainWindow::on_entryLower_changed()
{
    auto temp = entryLower_->get_text();

    char *end;

    if(!temp.empty())
    {
        auto value = static_cast<int>(std::strtol(temp.c_str(), &end, 10));

        if(value <= 0)
        {
            value = 1;
        }
        parameters.lowerLimit_ = value;
    }
    else
    {
        parameters.lowerLimit_ = std::numeric_limits<int>::lowest();
    }
}
