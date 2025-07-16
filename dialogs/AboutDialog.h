// AboutDialog.h

#pragma once

#include <FL/Fl_Window.H>

/// Displays a modal “About” dialog for HashSetManagerByNT.
/// Shows program icon, name, version, author and an OK button.
class AboutDialog {
public:
    /// Creates and shows the About window modally.
    /// Blocks until the user clicks OK.
    static void show();
};
