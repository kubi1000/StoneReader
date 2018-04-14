//
// Created by michal on 05-04-2018.
//

#ifndef GUI_CONTROLER_H
#define GUI_CONTROLER_H

#include <iostream>
#include "Picture.h"
#include "MainApp.h"

struct processParameters;

class Controller : public sigc::trackable {

private:

    Picture *picture_;

public:

    // Methods

    explicit Controller(Picture *picture) : picture_(picture) {}

    virtual ~Controller(){}

    virtual void on_btnMainDialogFileOpen_clicked(Gtk::FileChooserDialog *);

    virtual void on_btnMainQuit_clicked(Gtk::Window *);

    virtual void startProcessing(const processParameters &);
};


#endif //GUI_CONTROLER_H
