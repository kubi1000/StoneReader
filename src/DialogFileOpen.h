//
// Created by michal on 23-03-2018.
//

#ifndef GUI_DIALOGFILEOPEN_H
#define GUI_DIALOGFILEOPEN_H

#include <gtkmm.h>
#include <iostream>


class DialogFileOpen {


private:
    Gtk::FileChooserDialog *chooser_ = nullptr;

    Gtk::Button *openButton_ = nullptr;

protected:

public:

    DialogFileOpen();

    virtual ~DialogFileOpen();

    Gtk::FileChooserDialog &getFileChooserDialog() { return *chooser_; }

    friend class MainApp;

    friend class Picture;
};


#endif //GUI_DIALOGFILEOPEN_H
