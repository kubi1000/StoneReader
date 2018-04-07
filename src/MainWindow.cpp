//
// Created by michal on 23-03-2018.
//

#include "MainWindow.h"
#include "MainApp.h"


MainWindow::MainWindow(Controller &pController)
{
    SRefBuilder::getRefBuilder()->get_widget(mainWindowName_,window_);

    SRefBuilder::getRefBuilder()->get_widget("btnMainQuit",exitButton_);

    if(exitButton_)
    {
        exitButton_->signal_clicked().connect
                (sigc::bind<Gtk::Window*>
                         (sigc::mem_fun(pController,&Controller::on_btnMainQuit_clicked),
                             window_));
    }
}

MainWindow::~MainWindow()
{
    delete window_;
}

void MainWindow::refreshDrawingArea(std::string widgetName, cv::Mat *src)
{
    Gtk::DrawingArea *dA = nullptr;

    SRefBuilder::getRefBuilder()->get_widget(widgetName, dA);

    if(!dA)
    {
        std::cerr<<"Failed to connect to drawing area\n";

        exit(1);
    }

    dA->show();

    //Gtk::set_size_request();

    auto pix = convertOpenCv2Gtk(src,dA->get_allocation().get_width(),dA->get_allocation().get_height());

    if(pix)
    {
      // Gtk::DrawingArea::set_size_request(pix->get_width()/2,pix->get_height()/2);
    }

    Cairo::RefPtr<Cairo::Context> context = dA->get_window()->create_cairo_context();

    Gdk::Cairo::set_source_pixbuf(context, pix);

    context->paint();

}

Glib::RefPtr<Gdk::Pixbuf>
MainWindow::convertOpenCv2Gtk (cv::Mat *src, int dst_w, int dst_h) {

    cv::Mat gtkMask = *src;
    cv::Mat temp = *src;
    cv::cvtColor(*src, gtkMask, CV_BGR2RGB);

    Glib::RefPtr<Gdk::Pixbuf> pix = Gdk::Pixbuf::create_from_data (static_cast<const guint8 *>(gtkMask.data),
                                                                       Gdk::COLORSPACE_RGB,
                                                                           FALSE,
                                                                               8,
                                                                                   gtkMask.cols,
                                                                                       gtkMask.rows,
                                                                                           static_cast<int>(gtkMask.step));
    decltype (pix) rpix;

    rpix = pix->Gdk::Pixbuf::scale_simple (dst_h,dst_w,Gdk::INTERP_BILINEAR);

    return rpix;
}

bool MainWindow::update (Picture *picture)
{
    int counter = 1;

    std::vector <cv::Mat> tempPic;

    if(picture->getPictures().size()){

        auto temp = picture->getPictures().at(0);

        refreshDrawingArea("drawing1",&temp);

        temp = picture->getPictures().at(1);

        refreshDrawingArea("drawing2",&temp);
    }
    return true;
}
