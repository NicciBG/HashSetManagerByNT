// ImportView.h

#pragma once

#include <FL/Fl_Group.H>
#include <vector>

class Fl_Scroll;
class Fl_Button;

/// View for importing data via plugins.
/// Shows a scrollable list of plugin selectors on the left,
/// and a dynamic content panel on the right where the selected
/// plugin builds its import UI.
class ImportView : public Fl_Group {
public:
    /// Constructs the import view at position (X,Y) with size (W,H).
    ImportView(int X, int Y, int W, int H);
    ~ImportView();

    /// Returns the right‐hand content panel where plugins place their controls.
    Fl_Group* contentPanel() const;

    /// Clears all widgets from the content panel.
    void clearContent();

private:
    Fl_Scroll*                    leftScroll_;    // scrollable area for plugin selectors
    Fl_Group*                     contentPanel_;  // dynamic area for plugin UI
    std::vector<Fl_Button*>       pluginButtons_; // one button per available plugin
};
