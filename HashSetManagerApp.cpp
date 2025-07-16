// HashSetManagerApp.cpp

#include "HashSetManagerApp.h"

#include <FL/Fl.H>
#include <FL/Fl_Window.H>
#include <FL/Fl_Menu_Bar.H>
#include <FL/Fl_Group.H>
#include <FL/Fl_Status_Bar.H>
#include <cstring>
#include <cstdlib>

#ifdef _WIN32
#  include <windows.h>
#  include <shellapi.h>
#endif

#include "DonateDialog.h"
#include "LicenseDialog.h"
#include "AboutDialog.h"

// ——————————————————————————————————
// Static callbacks (must be declared in the header as private static members)
// ——————————————————————————————————
void HashSetManagerApp::menu_cb(Fl_Widget* w, void* data) {
  auto app = static_cast<HashSetManagerApp*>(data);
  const char* lbl = static_cast<Fl_Menu_*>(w)->mvalue()->label();

  if      (std::strcmp(lbl, "Settings") == 0)  app->showView(app->settingsView_);
  else if (std::strcmp(lbl, "Exit")     == 0)  std::exit(0);
  else if (std::strcmp(lbl, "Import")   == 0)  app->showView(app->importView_);
  else if (std::strcmp(lbl, "Export")   == 0)  app->showView(app->exportView_);
  else if (std::strcmp(lbl, "Search")   == 0)  app->showView(app->searchView_);
  else if (std::strcmp(lbl, "Help")     == 0)  HashSetManagerApp::openHelp();
  else if (std::strcmp(lbl, "Donate")   == 0)  DonateDialog::show();
  else if (std::strcmp(lbl, "License")  == 0)  LicenseDialog::show();
  else if (std::strcmp(lbl, "About")    == 0)  AboutDialog::show();
  // TODO: handle Default language / Add Language / dynamically‐added langs
}

void HashSetManagerApp::openHelp() {
#ifdef _WIN32
  ShellExecuteA(nullptr, "open", "help/index.html", nullptr, nullptr, SW_SHOWNORMAL);
#else
  std::system("xdg-open help/index.html &");
#endif
}

// ——————————————————————————————————
// Constructor / Destructor
// ——————————————————————————————————
HashSetManagerApp::HashSetManagerApp() {
  // 1) Main window
  window_ = new Fl_Window(800, 600, "HashSetManagerByNT");
  window_->begin();

    // 2) Menu bar
    menuBar_ = new Fl_Menu_Bar(0, 0, 800, 25);
    buildMenu();

    // 3) Client area (views)
    clientArea_ = new Fl_Group(0, 25, 800, 550);
      clientArea_->begin();
        settingsView_ = new SettingsView(0, 0, 800, 550);
        importView_   = new ImportView(0, 0, 800, 550);
        exportView_   = new ExportView(0, 0, 800, 550);
        searchView_   = new SearchView(0, 0, 800, 550);
      clientArea_->end();

    // 4) Status bar
    statusBar_ = new Fl_Status_Bar(0, 575, 800, 25);

  window_->end();
  window_->resizable(clientArea_);

  // 5) Load all plugins
  pluginManager_.loadPlugins();

  // 6) Show settings view by default
  showView(settingsView_);
}

void HashSetManagerApp::run() {
  window_->show();
  Fl::run();
}

// ——————————————————————————————————
// Menu & View Management
// ——————————————————————————————————
void HashSetManagerApp::buildMenu() {
  menuBar_->add("Program/Settings",          0, menu_cb, this);
  menuBar_->add("Program/Exit",              0, menu_cb, this);

  menuBar_->add("Actions/Import",            0, menu_cb, this);
  menuBar_->add("Actions/Export",            0, menu_cb, this);
  menuBar_->add("Actions/Search",            0, menu_cb, this);

  menuBar_->add("Language/Default language", 0, menu_cb, this);
  menuBar_->add("Language/Add Language",     0, menu_cb, this);
  // TODO: Dynamically add entries for each loaded .ini language

  menuBar_->add("Help/Help",                 0, menu_cb, this);
  menuBar_->add("Help/Donate",               0, menu_cb, this);
  menuBar_->add("Help/License",              0, menu_cb, this);
  menuBar_->add("Help/About",                0, menu_cb, this);
}

void HashSetManagerApp::showView(Fl_Group* view) {
  // hide all
  settingsView_->hide();
  importView_  ->hide();
  exportView_  ->hide();
  searchView_  ->hide();

  // show requested
  view->show();
  clientArea_->redraw();
}
