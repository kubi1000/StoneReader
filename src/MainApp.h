//
// Created by michal on 22-03-2018.
//

#ifndef GUI_MAINAPP_H
#define GUI_MAINAPP_H



#include <gtkmm.h>
#include <iostream>
#include "SRefBuilder.h"
#include "DialogFileOpen.h"
#include "MainWindow.h"
#include "Picture.h"
#include "Controller.h"

/* As view it should contains all render methods
 * connections to signals, but without implementation of methods.
 * It should contains also connection to controller and model*/


class MainApp {

protected:

private:

    // Attributes

    Picture *picture_;

    Glib::RefPtr<Gtk::Application> app_;

    DialogFileOpen *dialogFileOpen_;

    MainWindow *mainWindow_;

    Controller *controller_;

    // Methods

public:

    // Attributes



    // Methods

    MainApp();

    virtual ~MainApp();

    void runApplication();

    DialogFileOpen &getDialogFileOpen() { return *dialogFileOpen_; }
};




#endif //GUI_MAINAPP_H
