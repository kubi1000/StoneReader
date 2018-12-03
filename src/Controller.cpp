//
// Created by michal on 05-04-2018.
//

#include "Controller.h"

bool Controller::draw_ = false;

void Controller::on_btnMainDialogFileOpen_clicked(Gtk::FileChooserDialog *chooser) {

    int response = chooser->run();

    switch(response) {

        case (1): {

            picture_->clearVector();

            picture_->setFilePath(std::move(chooser->get_filename()));

            chooser->close();

            break;
        }
        case (0): {

            chooser->close();

            break;
        }
        default: {

            chooser->close();

            break;
        }
    }
}

void Controller::on_btnMainQuit_clicked(Gtk::Window *window)
{
        window->close();
}

void Controller::startProcessing(const ProcessParameters & parameters)
{

    if(picture_->hasPicture())
    {
        picture_->processWithNewParam();

        picture_->automaticBrightContrast();

        picture_->morphOperations(parameters);

        picture_->performThresholding(parameters);

        numberOfContours_ = picture_->watershedSegmentation(parameters);
    }
}


void Controller::refactorScale(gdouble &xCoordinate)
{
  static double coordinates[2]{};

  if (coordinates[0] == 0)
  {
      coordinates[0] = xCoordinate;

      histogramDialog_->setLabels(coordinates[0]);
  }
  else if (coordinates[0] != 0)
  {
      histogramDialog_->switchVisibility();

      coordinates[1] = xCoordinate;

      auto scale = sqrt(pow((coordinates[0] - coordinates[1]),2));

      histogramDialog_->setLabels(coordinates[1], scale);

      std::fill(std::begin(coordinates),std::end(coordinates),0);

      Picture::setScale(scale);

      mainWindow_->switchDrawingEvent();
  }
}

void Controller::generateHistogram()
{
    if(picture_->isProcessed() && numberOfContours_ > 0)
    {
        auto fileName = picture_->createHistogram(numberOfContours_);

        if(draw_ && !fileName.empty())
        {
            histogramWindow_->loadFromFile(fileName);
        }

        MainWindow::currentDisplayChooser_ = DisplayChooser::RESULTS;
    }
}

void Controller::on_entryScale_changed(Gtk::Entry *entry)
{
    auto temp = entry->get_text();

    char *end;

    if(temp.empty())
    {
        return;
    }

    auto value = static_cast<int>(std::strtol(temp.c_str(), &end, 10));

    if(value <= 0)
    {
        value = 1;
    }

    Picture::setScaleFactor(value);
}

void Controller::on_entryNumberOfBeans_changed(Gtk::Entry *entry)
{
    auto temp = entry->get_text();

    char *end;

    if(temp.empty())
    {
        return;
    }

    auto value = static_cast<int>(std::strtol(temp.c_str(), &end, 10));

    if(value <= 0)
    {
        value = 1;
    }
    Picture::setNumberOfBins(value);
}

void Controller::on_btnScale_clicked()
{
    histogramDialog_->switchVisibility();

    mainWindow_->switchDrawingEvent();

    MainWindow::currentDisplayChooser_ = DisplayChooser::HISTOGRAM_EQ;
}

void Controller::on_checkPrintHistogram_toggled()
{
    draw_ = !draw_;
}