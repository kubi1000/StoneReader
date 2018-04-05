//
// Created by michal on 05-04-2018.
//

#include "Controller.h"


void Controller::on_btnMainDialogFileOpen_clicked() {

    auto &chooser = mainApp_->getDialogFileOpen().getFileChooserDialog();

    int response = chooser.run();

    switch(response){

        case(1):
        {
            std::cout << "Select clicked." << std::endl;

            std::cout << "File selected: " << chooser.get_filename()
                      << std::endl;

            picture_->setFilePath(chooser.get_filename());

            chooser.close();

            break;
        }
        case(0):
        {
            std::cout << "Cancel clicked." << std::endl;

            chooser.close();

            break;
        }
        default:
        {
            std::cout<<"Unexpected button clicked."<<std::endl;

            chooser.close();

            break;
        }
    }
}
