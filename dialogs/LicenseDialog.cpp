// LicenseDialog.cpp

#include "LicenseDialog.h"
#include <FL/Fl_Window.H>
#include <FL/Fl_Text_Display.H>
#include <FL/Fl_Text_Buffer.H>
#include <FL/Fl_Button.H>
#include <FL/Fl.H>

#include <fstream>
#include <sstream>

void LicenseDialog::show() {
    const int W = 600;
    const int H = 450;
    Fl_Window* dlg = new Fl_Window(W, H, "License – HashSetManagerByNT");
    dlg->begin();

      // Read the LICENSE.txt file
      std::ifstream file("LICENSE.txt");
      std::stringstream ss;
      if (file.is_open()) {
          ss << file.rdbuf();
          file.close();
      } else {
          ss << "Unable to load LICENSE.txt.";
      }

      // Text display with scrollbar
      Fl_Text_Buffer* buffer = new Fl_Text_Buffer;
      buffer->text(ss.str().c_str());
      Fl_Text_Display* display = new Fl_Text_Display(10, 10, W - 20, H - 70);
      display->buffer(buffer);
      display->box(FL_DOWN_FRAME);
      display->wrap_mode(FL_WRAP_AT_BOUNDS, 0);

      // OK button
      Fl_Button* ok = new Fl_Button((W / 2) - 40, H - 50, 80, 30, "OK");
      ok->callback([](Fl_Widget* w, void* data) {
          static_cast<Fl_Window*>(data)->hide();
      }, dlg);

    dlg->end();
    dlg->set_modal();
    dlg->show();

    // Wait until closed
    while (dlg->shown()) {
        Fl::wait();
    }

    delete buffer;
    delete dlg;
}
