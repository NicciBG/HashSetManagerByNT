// main.cpp

#include <FL/Fl.H>
#include <FL/Fl_Window.H>
#include <FL/Fl_Menu_Bar.H>
#include <FL/Fl_Group.H>
#include <FL/Fl_Box.H>
#include <FL/Fl_Status_Bar.H>   // If your FLTK build doesn’t include this, use Fl_Box instead
#include <filesystem>
#include <memory>
#include <string>

// Forward declarations for plugin interface & views/dialogs
#include "PluginManager.h"
#include "SettingsView.h"
#include "ImportView.h"
#include "ExportView.h"
#include "SearchView.h"
#include "AboutDialog.h"
#include "LicenseDialog.h"
#include "DonateDialog.h"

//----------------------------------------------------------------
// HashSetManagerApp: encapsulates the main window & UI logic
//----------------------------------------------------------------
class HashSetManagerApp {
public:
    HashSetManagerApp();
    void run() { window->show(); Fl::run(); }
private:
    Fl_Window*      window;
    Fl_Menu_Bar*    menu;
    Fl_Group*       clientArea;
    Fl_Status_Bar*  statusBar;

    // One view per tab
    SettingsView*   settingsView;
    ImportView*     importView;
    ExportView*     exportView;
    SearchView*     searchView;

    PluginManager   pluginMgr;

    void buildMenu();
    void showView(Fl_Group* view);
};

//----------------------------------------------------------------
// Callbacks
//----------------------------------------------------------------
static void menuCallback(Fl_Widget* widget, void* userdata) {
    auto app = static_cast<HashSetManagerApp*>(userdata);
    const char* label = static_cast<Fl_Menu_*>(widget)->mvalue()->label();

    if (!strcmp(label, "Settings")) {
        app->showView(app->settingsView);
    }
    else if (!strcmp(label, "Exit")) {
        exit(0);
    }
    else if (!strcmp(label, "Import")) {
        app->showView(app->importView);
    }
    else if (!strcmp(label, "Export")) {
        app->showView(app->exportView);
    }
    else if (!strcmp(label, "Search")) {
        app->showView(app->searchView);
    }
    else if (!strcmp(label, "Help")) {
        #ifdef _WIN32
            ShellExecuteA(NULL, "open", "help/index.html", NULL, NULL, SW_SHOWNORMAL);
        #else
            system("xdg-open help/index.html &");
        #endif
    }
    else if (!strcmp(label, "Donate")) {
        DonateDialog::show();
    }
    else if (!strcmp(label, "License")) {
        LicenseDialog::show();
    }
    else if (!strcmp(label, "About")) {
        AboutDialog::show();
    }
    // TODO: handle language submenu items
}

static void openHelp() {
    #ifdef _WIN32
        ShellExecuteA(NULL, "open", "help/index.html", NULL, NULL, SW_SHOWNORMAL);
    #else
        system("xdg-open help/index.html &");
    #endif
}

//----------------------------------------------------------------
// HashSetManagerApp implementation
//----------------------------------------------------------------
HashSetManagerApp::HashSetManagerApp() {
    // 1) Main window
    window = new Fl_Window(800, 600, "HashSetManagerByNT");
    window->begin();

    // 2) Menu bar
    menu = new Fl_Menu_Bar(0, 0, 800, 25);
    buildMenu();

    // 3) Client area (holds views)
    clientArea = new Fl_Group(0, 25, 800, 550);
      clientArea->begin();
        settingsView = new SettingsView(0, 0, 800, 550);
        importView   = new ImportView(0, 0, 800, 550);
        exportView   = new ExportView(0, 0, 800, 550);
        searchView   = new SearchView(0, 0, 800, 550);
      clientArea->end();

    // 4) Status bar
    statusBar = new Fl_Status_Bar(0, 575, 800, 25);

    window->end();
    window->resizable(clientArea);

    // 5) Load plugins
    pluginMgr.loadPlugins();

    // 6) Show Settings on start
    showView(settingsView);
}

void HashSetManagerApp::buildMenu() {
    menu->add("Program/Settings"        , 0, menuCallback, this);
    menu->add("Program/Exit"            , 0, menuCallback, this);

    menu->add("Actions/Import"          , 0, menuCallback, this);
    menu->add("Actions/Export"          , 0, menuCallback, this);
    menu->add("Actions/Search"          , 0, menuCallback, this);

    menu->add("Language/Default language", 0, menuCallback, this);
    menu->add("Language/Add Language"    , 0, menuCallback, this);
    // TODO: dynamically populate discovered languages here

    menu->add("Help/Help"               , 0, menuCallback, this);
    menu->add("Help/Donate"             , 0, menuCallback, this);
    menu->add("Help/License"            , 0, menuCallback, this);
    menu->add("Help/About"              , 0, menuCallback, this);
}

void HashSetManagerApp::showView(Fl_Group* view) {
    // Hide all
    settingsView->hide();
    importView->hide();
    exportView->hide();
    searchView->hide();

    // Show requested
    view->show();
    clientArea->redraw();
}

//----------------------------------------------------------------
// Entry point
//----------------------------------------------------------------
int main(int argc, char** argv) {
    // Optional FLTK scheme
    Fl::scheme("plastic");

    // Initialize and run
    HashSetManagerApp app;
    app.run();

    return 0;
}
