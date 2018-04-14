//
// Created by michal on 23-03-2018.
//

#include "MainWindow.h"
#include "MainApp.h"


MainWindow::MainWindow(Controller &pController) : controllerHandler_(&pController)
{
    SRefBuilder::getRefBuilder()->get_widget(mainWindowName_,window_);

    SRefBuilder::getRefBuilder()->get_widget("btnMainQuit",exitButton_);

    SRefBuilder::getRefBuilder()->get_widget("btnStart",startButton_);

    SRefBuilder::getRefBuilder()->get_widget("scaleElementSize",scaleElementSize_);

    SRefBuilder::getRefBuilder()->get_widget("scaleElementType",scaleElementType_);


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

    if(scaleElementSize_ && scaleElementType_)
    {
        scaleElementSize_->signal_value_changed().connect
                (sigc::mem_fun(*this, &MainWindow::on_scaleElementSize_value_changed));

        scaleElementType_->signal_value_changed().connect
                (sigc::mem_fun(*this, &MainWindow::on_scaleElementType_value_changed));
    }
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
        std::cerr<<"Failed to connect to drawing area\n";

        exit(1);
    }

    dA->show();

    //Gtk::set_size_request();

    auto pix = convertOpenCv2Gtk(&temp,dA->get_allocation().get_width(),dA->get_allocation().get_height(),code);

    if(pix)
    {
      // Gtk::DrawingArea::set_size_request(pix->get_width()/2,pix->get_height()/2);
    }

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

bool MainWindow::update (Picture *picture)
{
    int counter = 1;

    if(!picture->getPictures().empty()){

        auto temp = picture->getPictures().at(0).clone();

        refreshDrawingArea("drawing1",&temp);

        if(picture->getPictures().size()>1)
        {
            auto size = picture->getPictures().size() - 1;

            temp = picture->getPictures().at(size);

            refreshDrawingArea("drawing2",&temp, CV_GRAY2RGB);
        }
    }

    for(const auto & x :parameters.structuringElementParams)
    {
        std::cout << "parametr: " << x << std::endl;
    }

    return true;
}

void MainWindow::on_scaleElementType_value_changed()
{
    parameters.structuringElementParams[0] = static_cast<int>(scaleElementType_->get_value());
}

void MainWindow::on_scaleElementSize_value_changed()
{
    parameters.structuringElementParams[1] = static_cast<int>(scaleElementSize_->get_value());
}

void MainWindow::on_btnStart_clicked()
{
    controllerHandler_->startProcessing(getProcessParameters());
}
