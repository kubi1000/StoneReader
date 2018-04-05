//
// Created by michal on 23-03-2018.
//

#include "MainWindow.h"
#include "MainApp.h"


MainWindow::MainWindow()
{
    SRefBuilder::getRefBuilder()->get_widget(mainWindowName_,window_);

    SRefBuilder::getRefBuilder()->get_widget("btnMainQuit",exitButton_);

    if(exitButton_)
    {
        exitButton_->signal_clicked().connect(sigc::mem_fun(*this,&MainWindow::on_btnMainQuit_clicked));
    }
}


MainWindow::~MainWindow()
{
    delete window_;
}
void MainWindow::on_btnMainQuit_clicked()
{
    window_->close();
}

void MainWindow::refreshDrawingArea(char *widgetName, cv::Mat *src)
{


}

