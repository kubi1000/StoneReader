//
// Created by michal on 22-03-2018.
//

#include "MainApp.h"

MainApp::MainApp() {

    app_ = Gtk::Application::create();

    SRefBuilder::getRefBuilder();

    mainWindow_ = new MainWindow();

    dialogFileOpen_ = new DialogFileOpen();

    picture_ = new Picture();

    controller_ = new Controller(picture_,this);

}

MainApp::~MainApp() {

    delete dialogFileOpen_;

    delete mainWindow_;

    delete picture_;
}

void MainApp::runApplication() {

    app_->run(*mainWindow_->window_);
}
