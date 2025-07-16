// DonateDialog.h

#pragma once

#include <FL/Fl_Window.H>

/// Displays a modal “Donate” dialog for HashSetManagerByNT.
/// Provides information or links for supporting the project.
class DonateDialog {
public:
    /// Creates and shows the Donate window modally.
    /// Blocks until the user closes it.
    static void show();
};
