// SettingsView.cpp

#include "SettingsView.h"

#include <FL/Fl_Tree.H>
#include <FL/Fl_Button.H>
#include <FL/Fl_File_Chooser.H>
#include <FL/fl_ask.H>

#include <filesystem>
#include <string>

namespace fs = std::filesystem;

SettingsView::SettingsView(int X, int Y, int W, int H)
  : Fl_Group(X, Y, W, H)
{
    begin();
      int margin = 10;
      int panelW = (W - 3*margin) / 2;
      int panelH = H - 2*margin - 40;

      // Plugin panel
      pluginTree_ = new Fl_Tree(X + margin, Y + margin, panelW, panelH);
      pluginTree_->root_label("Installed Plugins");
      pluginTree_->showroot(false);

      installPluginBtn_ = new Fl_Button(
          X + margin,
          Y + margin + panelH + 5,
          panelW/2 - 5, 30,
          "Install Plugin"
      );
      removePluginBtn_ = new Fl_Button(
          X + margin + panelW/2 + 5,
          Y + margin + panelH + 5,
          panelW/2 - 5, 30,
          "Remove Plugin"
      );

      // Language panel
      languageTree_ = new Fl_Tree(
          X + 2*margin + panelW,
          Y + margin,
          panelW,
          panelH
      );
      languageTree_->root_label("Available Languages");
      languageTree_->showroot(false);

      addLanguageBtn_ = new Fl_Button(
          X + 2*margin + panelW,
          Y + margin + panelH + 5,
          panelW/2 - 5, 30,
          "Add Language"
      );
      removeLanguageBtn_ = new Fl_Button(
          X + 2*margin + panelW + panelW/2 + 5,
          Y + margin + panelH + 5,
          panelW/2 - 5, 30,
          "Remove Language"
      );

      // Callbacks
      installPluginBtn_->callback(cb_installPlugin, this);
      removePluginBtn_->callback(cb_removePlugin, this);
      addLanguageBtn_->callback(cb_addLanguage, this);
      removeLanguageBtn_->callback(cb_removeLanguage, this);
    end();

    // Populate lists
    refreshPluginList();
    refreshLanguageList();
}

SettingsView::~SettingsView() {
    // FLTK auto-deletes children
}

void SettingsView::refreshPluginList() {
    pluginTree_->clear();
    fs::path folder = "plugins";
    if (!fs::exists(folder)) fs::create_directory(folder);

    for (auto& e : fs::directory_iterator(folder)) {
        if (!e.is_regular_file()) continue;
        auto ext = e.path().extension().string();
#ifdef _WIN32
        if (ext != ".dll") continue;
#else
        if (ext != ".so") continue;
#endif
        std::string name = e.path().filename().string();
        pluginTree_->add(name.c_str());
    }
}

void SettingsView::refreshLanguageList() {
    languageTree_->clear();
    fs::path folder = "Languages";
    if (!fs::exists(folder)) fs::create_directory(folder);

    for (auto& e : fs::directory_iterator(folder)) {
        if (!e.is_regular_file() || e.path().extension() != ".ini") continue;
        std::string name = e.path().filename().string();
        languageTree_->add(name.c_str());
    }
}

void SettingsView::cb_installPlugin(Fl_Widget*, void* data) {
    auto self = static_cast<SettingsView*>(data);
    const char* file = fl_file_chooser(
        "Select Plugin to Install", "*.{dll,so}", nullptr
    );
    if (!file) return;

    fs::path src(file);
    fs::path dst = fs::path("plugins") / src.filename();
    try {
        fs::create_directories("plugins");
        fs::copy_file(src, dst, fs::copy_options::overwrite_existing);
    }
    catch (std::exception& ex) {
        fl_alert("Install failed:\n%s", ex.what());
    }
    self->refreshPluginList();
}

void SettingsView::cb_removePlugin(Fl_Widget*, void* data) {
    auto self = static_cast<SettingsView*>(data);
    auto item = self->pluginTree_->callback_item();
    if (!item) return;
    const char* name = item->label();
    if (fl_choice("Remove plugin '%s'?", name, "No", "Yes", nullptr) != 1)
        return;

    try {
        fs::remove(fs::path("plugins") / name);
    }
    catch (std::exception& ex) {
        fl_alert("Remove failed:\n%s", ex.what());
    }
    self->refreshPluginList();
}

void SettingsView::cb_addLanguage(Fl_Widget*, void* data) {
    auto self = static_cast<SettingsView*>(data);
    const char* file = fl_file_chooser(
        "Select Language INI File", "*.ini", nullptr
    );
    if (!file) return;

    fs::path src(file);
    fs::path dst = fs::path("Languages") / src.filename();
    try {
        fs::create_directories("Languages");
        fs::copy_file(src, dst, fs::copy_options::overwrite_existing);
    }
    catch (std::exception& ex) {
        fl_alert("Add language failed:\n%s", ex.what());
    }
    self->refreshLanguageList();
}

void SettingsView::cb_removeLanguage(Fl_Widget*, void* data) {
    auto self = static_cast<SettingsView*>(data);
    auto item = self->languageTree_->callback_item();
    if (!item) return;
    const char* name = item->label();
    if (fl_choice("Remove language '%s'?", name, "No", "Yes", nullptr) != 1)
        return;

    try {
        fs::remove(fs::path("Languages") / name);
    }
    catch (std::exception& ex) {
        fl_alert("Remove failed:\n%s", ex.what());
    }
    self->refreshLanguageList();
}
