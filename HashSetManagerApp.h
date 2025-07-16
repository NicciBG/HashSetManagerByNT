// HashSetManagerApp.h

#pragma once

#include <FL/Fl.H>
#include <FL/Fl_Window.H>
#include <FL/Fl_Menu_Bar.H>
#include <FL/Fl_Group.H>
#include <FL/Fl_Status_Bar.H>   // Substitute with Fl_Box if not available

#include "PluginManager.h"
#include "SettingsView.h"
#include "ImportView.h"
#include "ExportView.h"
#include "SearchView.h"

class HashSetManagerApp {
public:
  // Constructs the main window, menu, views, and loads plugins
  HashSetManagerApp();

  // Launches the FLTK event loop
  void run();

private:
  // Builds the menu bar items and attaches callbacks
  void buildMenu();

  // Hides all client views and shows only the specified one
  void showView(Fl_Group* view);

  // Main window handle
  Fl_Window*      window_;

  // Menu bar at the top
  Fl_Menu_Bar*    menuBar_;

  // Container for swapping different views (Settings, Import, Export, Search)
  Fl_Group*       clientArea_;

  // Status bar at the bottom
  Fl_Status_Bar*  statusBar_;

  // Individual views for each function
  SettingsView*   settingsView_;
  ImportView*     importView_;
  ExportView*     exportView_;
  SearchView*     searchView_;

  // Manages loading and lifetime of plugin DLLs/SOs
  PluginManager   pluginManager_;
};
