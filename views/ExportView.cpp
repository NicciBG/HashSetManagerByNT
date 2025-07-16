// ExportView.cpp

#include "ExportView.h"
#include "PluginManager.h"
#include "IPlugin.h"

#include <FL/Fl_Scroll.H>
#include <FL/Fl_Check_Button.H>
#include <FL/Fl_Group.H>

#include <vector>

extern PluginManager pluginManager;   // must be defined in main or a shared module

static constexpr int LEFT_PANEL_WIDTH = 200;
static constexpr int BUTTON_HEIGHT     = 25;
static constexpr int BUTTON_SPACING    = 5;

// callback when a plugin checkbox is toggled
static void plugin_toggle_cb(Fl_Widget* w, void* data) {
    auto view = static_cast<ExportView*>(data);
    auto btn  = static_cast<Fl_Check_Button*>(w);
    auto plugin = static_cast<IPlugin*>(btn->user_data());

    // clear any existing UI in the right panel
    view->clearContent();

    if (btn->value()) {
        // plugin populates its export UI into view->contentPanel()
        plugin->activateExportUI();
    }

    view->contentPanel()->redraw();
}

ExportView::ExportView(int X, int Y, int W, int H)
  : Fl_Group(X, Y, W, H)
{
    begin();

    // Left scrollable panel with checkboxes
    leftScroll_ = new Fl_Scroll(X, Y, LEFT_PANEL_WIDTH, H);
    leftScroll_->type(Fl_Scroll::VERTICAL_ALWAYS);
    leftScroll_->begin();

    int yOff = Y + BUTTON_SPACING;
    for (auto& plugin : pluginManager.plugins()) {
        Fl_Check_Button* cb = new Fl_Check_Button(
            X + 10, yOff,
            LEFT_PANEL_WIDTH - 20, BUTTON_HEIGHT,
            plugin->name().c_str()
        );
        cb->user_data(plugin.get());
        cb->callback(plugin_toggle_cb, this);
        checkButtons_.push_back(cb);
        yOff += BUTTON_HEIGHT + BUTTON_SPACING;
    }

    leftScroll_->end();

    // Right content area (initially empty)
    contentPanel_ = new Fl_Group(X + LEFT_PANEL_WIDTH, Y, W - LEFT_PANEL_WIDTH, H);
    contentPanel_->begin();
    contentPanel_->end();

    end();
    hide();  // view not shown until menu selects "Export"
}

ExportView::~ExportView() {
    // cleanup if needed (FLTK will delete children automatically)
}

Fl_Group* ExportView::contentPanel() const {
    return contentPanel_;
}

void ExportView::clearContent() {
    // Remove and delete all children widgets from contentPanel_
    int n = contentPanel_->children();
    for (int i = n - 1; i >= 0; --i) {
        Fl_Widget* child = contentPanel_->child(i);
        contentPanel_->remove(child);
        delete child;
    }
}
