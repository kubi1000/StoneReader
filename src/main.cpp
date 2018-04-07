#include "MainApp.h"

int main() {

    auto picture = new Picture();

    auto controller = new Controller(picture);

    auto mainApp = new MainApp(controller, picture);

    mainApp->runApplication();

    delete mainApp;

    delete controller;

    delete picture;

    return 0;
}