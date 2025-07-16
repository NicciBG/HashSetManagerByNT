// AboutDialog.cpp

#include "AboutDialog.h"
#include <FL/Fl_Window.H>
#include <FL/Fl_Box.H>
#include <FL/Fl_Button.H>
#include <FL/Fl_PNG_Image.H>
#include <FL/Fl.H>

void AboutDialog::show() {
    const int W = 450, H = 320;
    Fl_Window* dlg = new Fl_Window(W, H, "About HashSetManagerByNT");
    dlg->begin();

      // 256×256 icon
      Fl_PNG_Image* icon = new Fl_PNG_Image("resources/icon256.png");
      Fl_Box* img = new Fl_Box(10, 10, 256, 256);
      img->image(icon);

      // Program name
      Fl_Box* title = new Fl_Box(280, 20, W - 300, 30, "HashSetManagerByNT");
      title->labelfont(FL_BOLD);
      title->labelsize(18);

      // Version
      Fl_Box* ver = new Fl_Box(280, 60, W - 300, 20, "Version 1.0.0");
      ver->labelsize(14);

      // Author
      Fl_Box* auth = new Fl_Box(280, 90, W - 300, 20, "Created by NT");
      auth->labelsize(14);

      // OK button
      Fl_Button* ok = new Fl_Button((W/2) - 40, H - 50, 80, 30, "OK");
      ok->callback([](Fl_Widget* w, void* data){
        static_cast<Fl_Window*>(data)->hide();
      }, dlg);

    dlg->end();
    dlg->set_modal();
    dlg->show();

    // Block until user closes
    while (dlg->shown()) {
      Fl::wait();
    }

    delete icon;
    delete dlg;
}
