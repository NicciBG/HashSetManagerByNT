// SearchView.h

#pragma once

#include <FL/Fl_Group.H>
#include <vector>

class Fl_Scroll;
class Fl_Check_Button;

/// View for searching hashes via plugins.
/// Presents a scrollable list of plugin checkboxes on the left,
/// and a dynamic content panel on the right where the
/// currently highlighted plugin can display its search UI.
class SearchView : public Fl_Group {
public:
    /// Constructs the search view at position (X,Y) with size (W,H).
    SearchView(int X, int Y, int W, int H);
    ~SearchView();

    /// Returns the right‐hand content panel where plugins place their controls.
    Fl_Group* contentPanel() const;

    /// Clears all widgets from the content panel.
    void clearContent();

private:
    Fl_Scroll*                       leftScroll_;    // scrollable area for plugin checkboxes
    Fl_Group*                        contentPanel_;  // dynamic area for plugin UI
    std::vector<Fl_Check_Button*>    checkButtons_;  // one checkbox per plugin
};
