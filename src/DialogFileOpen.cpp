//
// Created by michal on 23-03-2018.
//

#include <opencv2/opencv.hpp>
#include "DialogFileOpen.h"
#include "MainApp.h"

DialogFileOpen::DialogFileOpen(Controller &pController)
{
    SRefBuilder::getRefBuilder()->get_widget("fileChooserOpen",chooser_);

    SRefBuilder::getRefBuilder()->get_widget("btnMainDialogFileOpen",openButton_);

    if(openButton_)
    {
       openButton_->signal_clicked().connect
               (sigc::bind<Gtk::FileChooserDialog*>
                   (sigc::mem_fun(pController, &Controller::on_btnMainDialogFileOpen_clicked),
                       chooser_));
    }
}

DialogFileOpen::~DialogFileOpen()
{
    delete chooser_;
}

