//
// Created by michal on 23-04-2018.
//

#include "HistogramDialogWindow.h"

HistogramDialogWindow::HistogramDialogWindow(Controller &controller) :controller_(&controller)
{
    SRefBuilder::getRefBuilder()->get_widget("histWindow",histogramWindow_);

    SRefBuilder::getRefBuilder()->get_widget("entryScale", entryScale_);

    SRefBuilder::getRefBuilder()->get_widget("btnScale", btnScale_);

    SRefBuilder::getRefBuilder()->get_widget("btnHistogram",btnHistogram_);

    SRefBuilder::getRefBuilder()->get_widget("btnGenerateHistogram",btnGenerateHistogram_);

    SRefBuilder::getRefBuilder()->get_widget("entryNumberOfBins",entryNumberOfBeans_);

    SRefBuilder::getRefBuilder()->get_widget("checkPrintHistogram",checkPrintHistogram_);

    SRefBuilder::getRefBuilder()->get_widget("lblFirstPoint", lblFirstPoint_);

    SRefBuilder::getRefBuilder()->get_widget("lblSecondPoint", lblSecondPoint_);

    SRefBuilder::getRefBuilder()->get_widget("lblLength", lblLength_);

    if(btnHistogram_)
    {
        btnHistogram_->signal_clicked().connect
                (sigc::mem_fun(*this,&HistogramDialogWindow::showHistogramWindow));
    }

    if(entryScale_)
    {
        entryScale_->signal_changed().connect
                (sigc::bind<Gtk::Entry*>
                         (sigc::mem_fun(controller,&Controller::on_entryScale_changed),entryScale_));
    }

    if(btnGenerateHistogram_)
    {
        btnGenerateHistogram_->signal_clicked().connect
                (sigc::mem_fun(*this, &HistogramDialogWindow::on_btnGenerateHistogram_clicked));
    }

    if(entryNumberOfBeans_)
    {
        entryNumberOfBeans_->signal_changed().connect
                (sigc::bind<Gtk::Entry*>
                         (sigc::mem_fun(controller,&Controller::on_entryNumberOfBeans_changed),entryNumberOfBeans_));
    }

    if(btnScale_)
    {
        btnScale_->signal_clicked().connect
                (sigc::mem_fun(controller,&Controller::on_btnScale_clicked));
    }

    if(checkPrintHistogram_)
    {
        checkPrintHistogram_->signal_toggled().connect
                (sigc::mem_fun(controller,&Controller::on_checkPrintHistogram_toggled));
    }
}

HistogramDialogWindow::~HistogramDialogWindow()
{
    delete histogramWindow_;
}

void HistogramDialogWindow::showHistogramWindow()
{
    histogramWindow_->show();
}

void HistogramDialogWindow::on_btnGenerateHistogram_clicked()
{
    controller_->generateHistogram();

    histogramWindow_->hide();
}

void HistogramDialogWindow::setLabels(double value)
{
    auto temp = std::to_string(value);

    lblFirstPoint_->set_label(temp);
}

void HistogramDialogWindow::setLabels(double value, double result)
{
    auto valueStr = std::to_string(value);

    auto resultStr = std::to_string(result);

    lblSecondPoint_->set_label(valueStr);

    lblLength_->set_label(resultStr);
}

void HistogramDialogWindow::switchVisibility()
{
    auto test = histogramWindow_->is_visible();

    histogramWindow_->set_visible(!test);
}
