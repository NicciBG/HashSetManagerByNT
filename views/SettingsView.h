// SettingsView.h

#pragma once

#include <FL/Fl_Group.H>

class Fl_Tree;
class Fl_Button;

/// Settings view for HashSetManagerByNT.
/// Mimics an MSVS “Project Settings” window:
///   • Manage installed plugins (DLL/SO)
///   • Manage available languages (.ini files)
class SettingsView : public Fl_Group {
public:
    /// Constructs the settings view at position (X,Y) with size (W,H).
    SettingsView(int X, int Y, int W, int H);
    ~SettingsView();

private:
    // Left tree: installed plugins
    Fl_Tree*    pluginTree_;
    Fl_Button*  installPluginBtn_;
    Fl_Button*  removePluginBtn_;

    // Right tree: available languages
    Fl_Tree*    languageTree_;
    Fl_Button*  addLanguageBtn_;
    Fl_Button*  removeLanguageBtn_;

    /// Refreshes the pluginTree_ from the "plugins/" folder.
    void refreshPluginList();

    /// Refreshes the languageTree_ from the "Languages/" folder.
    void refreshLanguageList();

    // Callbacks for buttons
    static void cb_installPlugin(Fl_Widget* w, void* data);
    static void cb_removePlugin(Fl_Widget* w, void* data);
    static void cb_addLanguage(Fl_Widget* w, void* data);
    static void cb_removeLanguage(Fl_Widget* w, void* data);
};
