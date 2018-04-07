//
// Created by michal on 22-03-2018.
//

#include "MainApp.h"

MainApp::MainApp(Controller *pController, Picture *pPicture) : controller_(pController), picture_(pPicture) {

    app_ = Gtk::Application::create();

    SRefBuilder::getRefBuilder();

    mainWindow_ = new MainWindow(*controller_);

    dialogFileOpen_ = new DialogFileOpen(*controller_);

    sigc::slot<bool> timerSlot = sigc::bind<Picture*> (sigc::mem_fun(mainWindow_, &MainWindow::update),picture_);

    sigc::connection timerConnection = Glib::signal_timeout().connect(timerSlot, TIME_INTERVAL);


}

MainApp::~MainApp() {

    delete dialogFileOpen_;

    delete mainWindow_;
}

void MainApp::runApplication() {

    app_->run(*mainWindow_->window_);
}
