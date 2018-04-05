//
// Created by michal on 05-04-2018.
//

#ifndef GUI_CONTROLER_H
#define GUI_CONTROLER_H

#include <iostream>
#include "Picture.h"
#include "MainApp.h"



class Controller {

private:

    Picture *picture_;
    MainApp *mainApp_;

public:

    // Methods

    Controller(Picture *picture, MainApp *mainApp) :
            picture_(picture), mainApp_(mainApp) {}

    ~Controller(){}

    void on_btnMainDialogFileOpen_clicked();

};


#endif //GUI_CONTROLER_H
