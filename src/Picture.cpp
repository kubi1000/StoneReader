//
// Created by michal on 24-03-2018.
//

#include "Picture.h"


void Picture::loadFile() {

    std::cout<<"Opening file: "<<filePath_<<std::endl;
    picture_ = cv::imread(filePath_);
}

Glib::RefPtr<Gdk::Pixbuf>
Picture::convertOpenCv2Gtk(cv::Mat *src, const int dst_w, const int dst_h) {

    cv::Mat *gtkMask = src;
    cvCvtColor(src, &gtkMask, CV_BGR2RGB);
    Glib::RefPtr<Gdk::Pixbuf> pix = Gdk::Pixbuf::create_from_data(static_cast<const guint8 *>(gtkMask->data),
                                        Gdk::COLORSPACE_RGB,
                                        FALSE,
                                        gtkMask->depth(),
                                        gtkMask->cols,
                                        gtkMask->rows,
                                        static_cast<int>(gtkMask->step));
    decltype(pix) rpix;
    pix = rpix->Gdk::Pixbuf::scale_simple(dst_h,dst_w,Gdk::INTERP_BILINEAR);
    return rpix;
}

void Picture::setFilePath(std::string path) {

    filePath_ = path;

    if(!filePath_.empty())
    {
        picture_ = cv::imread(path);

        std::cout<<picture_<<std::endl;
    }

}
