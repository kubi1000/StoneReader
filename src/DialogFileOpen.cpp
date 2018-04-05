//
// Created by michal on 23-03-2018.
//

#include <opencv2/opencv.hpp>
#include "DialogFileOpen.h"
#include "MainApp.h"

DialogFileOpen::DialogFileOpen()
{
    SRefBuilder::getRefBuilder()->get_widget("fileChooserOpen",chooser_);

    SRefBuilder::getRefBuilder()->get_widget("btnMainDialogFileOpen",openButton_);

    if(openButton_)
    {
        openButton_->signal_clicked().connect(sigc::mem_fun(*this, &Controller::on_btnMainDialogFileOpen_clicked));
    }
}


DialogFileOpen::~DialogFileOpen()
{
    delete chooser_;

    delete openButton_;
}

