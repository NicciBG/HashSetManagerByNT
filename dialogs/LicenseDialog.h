// LicenseDialog.h

#pragma once

#include <FL/Fl_Window.H>

/// Displays a modal “License” dialog for HashSetManagerByNT.
/// Loads and presents the contents of LICENSE.txt in a scrollable view.
class LicenseDialog {
public:
    /// Creates and shows the License window modally.
    /// Blocks until the user clicks OK.
    static void show();
};
