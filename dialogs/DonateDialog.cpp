// DonateDialog.cpp

#include "DonateDialog.h"
#include <FL/Fl_Window.H>
#include <FL/Fl_Box.H>
#include <FL/Fl_Button.H>
#include <FL/Fl.H>

#ifdef _WIN32
  #include <windows.h>
  #include <shellapi.h>
#endif

void DonateDialog::show() {
    const int W = 400, H = 240;
    Fl_Window* dlg = new Fl_Window(W, H, "Donate to HashSetManagerByNT");
    dlg->begin();

      // Donation message
      const char* msg =
        "Thank you for using HashSetManagerByNT!\n\n"
        "If you'd like to support development,\n"
        "please consider donating:\n"
        "https://example.com/donate";

      Fl_Box* box = new Fl_Box(20, 20, W - 40, 120, msg);
      box->align(FL_ALIGN_LEFT | FL_ALIGN_WRAP);
      box->labelsize(14);

      // Donate button
      Fl_Button* donateBtn = new Fl_Button(50, H - 60, 120, 30, "Open Donate Page");
      donateBtn->callback([](Fl_Widget*, void*) {
  #ifdef _WIN32
          ShellExecuteA(nullptr, "open", "https://example.com/donate", nullptr, nullptr, SW_SHOWNORMAL);
  #else
          system("xdg-open \"https://example.com/donate\" &");
  #endif
      });

      // Close button
      Fl_Button* closeBtn = new Fl_Button(W - 170, H - 60, 120, 30, "Close");
      closeBtn->callback([](Fl_Widget* w, void* data) {
          static_cast<Fl_Window*>(data)->hide();
      }, dlg);

    dlg->end();
    dlg->set_modal();
    dlg->show();

    // Wait until closed
    while (dlg->shown()) {
      Fl::wait();
    }

    delete dlg;
}
