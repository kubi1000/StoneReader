//
// Created by michal on 22-03-2018.
//

#include "MainApp.h"

MainApp::MainApp(Controller *pController, Picture *pPicture) : picture_(pPicture),  controller_(pController) {

    app_ = Gtk::Application::create();

    SRefBuilder::getRefBuilder();

    mainWindow_ = new MainWindow(*controller_);

    dialogFileOpen_ = new DialogFileOpen(*controller_);

    histogramDialogWindow_ = new HistogramDialogWindow(*controller_);

    histogramWindow_ = new HistogramWindow();

    sigc::slot<bool> timerSlot = sigc::bind<Picture*> (sigc::mem_fun(mainWindow_, &MainWindow::update),picture_);

    sigc::connection timerConnection = Glib::signal_timeout().connect(timerSlot, TIME_INTERVAL);

    controller_->getGuiContact(*histogramDialogWindow_, *mainWindow_, *histogramWindow_);
}

MainApp::~MainApp() {

    delete histogramWindow_;

    delete dialogFileOpen_;

    delete histogramDialogWindow_;

    delete mainWindow_;
}

void MainApp::runApplication() {

    app_->run(*mainWindow_->window_);
}
