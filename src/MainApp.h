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

#define TIME_INTERVAL 3000

class MainWindow;
class DialogFileOpen;
class Picture;
class Controller;

class MainApp
{
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

    MainApp(Controller *pController, Picture *pPicture);

    ~MainApp();

    void runApplication();

    DialogFileOpen &getDialogFileOpen() { return *dialogFileOpen_; }

};


#endif //GUI_MAINAPP_H
