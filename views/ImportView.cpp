// ImportView.cpp

#include "ImportView.h"
#include "PluginManager.h"
#include "IPlugin.h"

#include <FL/Fl_Scroll.H>
#include <FL/Fl_Button.H>
#include <FL/Fl_Group.H>

#include <vector>

extern PluginManager pluginManager;  // defined in main or a shared module

static constexpr int LEFT_PANEL_WIDTH = 200;
static constexpr int BUTTON_HEIGHT     = 25;
static constexpr int BUTTON_SPACING    = 5;

// callback when a plugin button is clicked
static void plugin_select_cb(Fl_Widget* w, void* data) {
    auto view   = static_cast<ImportView*>(data);
    auto button = static_cast<Fl_Button*>(w);
    auto plugin = static_cast<IPlugin*>(button->user_data());

    view->clearContent();
    plugin->activateImportUI();
    view->contentPanel()->redraw();
}

ImportView::ImportView(int X, int Y, int W, int H)
  : Fl_Group(X, Y, W, H)
{
    begin();

    // Left scrollable panel with plugin buttons
    leftScroll_ = new Fl_Scroll(X, Y, LEFT_PANEL_WIDTH, H);
    leftScroll_->type(Fl_Scroll::VERTICAL_ALWAYS);
    leftScroll_->begin();

    int yOff = Y + BUTTON_SPACING;
    for (auto& plugin : pluginManager.plugins()) {
        Fl_Button* btn = new Fl_Button(
            X + 10, yOff,
            LEFT_PANEL_WIDTH - 20, BUTTON_HEIGHT,
            plugin->name().c_str()
        );
        btn->user_data(plugin.get());
        btn->callback(plugin_select_cb, this);
        pluginButtons_.push_back(btn);
        yOff += BUTTON_HEIGHT + BUTTON_SPACING;
    }

    leftScroll_->end();

    // Right content area (initially empty)
    contentPanel_ = new Fl_Group(X + LEFT_PANEL_WIDTH, Y, W - LEFT_PANEL_WIDTH, H);
    contentPanel_->begin();
    contentPanel_->end();

    end();
    hide();  // not shown until "Import" is selected from menu
}

ImportView::~ImportView() {
    // FLTK will delete child widgets automatically
}

Fl_Group* ImportView::contentPanel() const {
    return contentPanel_;
}

void ImportView::clearContent() {
    int count = contentPanel_->children();
    for (int i = count - 1; i >= 0; --i) {
        Fl_Widget* child = contentPanel_->child(i);
        contentPanel_->remove(child);
        delete child;
    }
}
