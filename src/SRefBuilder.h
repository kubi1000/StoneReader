//
// Created by michal on 05-04-2018.
//

#ifndef GUI_SREFBUILDER_H
#define GUI_SREFBUILDER_H


#include <gtkmm/builder.h>
#include <giomm.h>
#include <iostream>

class SRefBuilder
{

private:

    const Glib::ustring gladeFileName_ = "exp.glade";

    Glib::RefPtr<Gtk::Builder> refBuilder_;

    SRefBuilder()
    {
        refBuilder_ = Gtk::Builder::create();

        try {

            refBuilder_->add_from_file(gladeFileName_);
        }
        catch(const Glib::FileError& ex)
        {
            std::cerr << "FileError: " << ex.what() << std::endl;

            exit(1);
        }
        catch(const Glib::MarkupError& ex)
        {
            std::cerr << "MarkupError: " << ex.what() << std::endl;

            exit(1);
        }
        catch(const Gtk::BuilderError& ex)
        {
            std::cerr << "BuilderError: " << ex.what() << std::endl;

            exit(1);
        }
    }

public:

    static Glib::RefPtr<Gtk::Builder> &getRefBuilder()
    {
        static SRefBuilder refBuilder;

        return refBuilder.refBuilder_;
    }
};

#endif //GUI_SREFBUILDER_H
