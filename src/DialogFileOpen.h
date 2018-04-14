//
// Created by michal on 23-03-2018.
//

#ifndef GUI_DIALOGFILEOPEN_H
#define GUI_DIALOGFILEOPEN_H

#include <gtkmm.h>
#include <iostream>
#include "Controller.h"

class Controller;

class DialogFileOpen
{

private:

    Gtk::FileChooserDialog *chooser_ = nullptr;

    Gtk::ToolButton *openButton_ = nullptr;

public:

    explicit DialogFileOpen(Controller &pController);

    ~DialogFileOpen();

    Gtk::FileChooserDialog &getFileChooserDialog() { return *chooser_; }
};


#endif //GUI_DIALOGFILEOPEN_H
