// IPlugin.h

#pragma once

#include <string>

/// Basic interface that every plugin must implement.
/// Plugins are discovered at runtime and provide
/// import/export/search UIs on demand.
class IPlugin {
public:
    virtual ~IPlugin() = default;

    /// Returns the unique name of this plugin.
    /// This name should match the section name in the config.
    virtual std::string name() const = 0;

    /// Called when the user activates this plugin in the Settings view.
    /// The plugin should populate its UI controls accordingly.
    virtual void activateSettingsUI() = 0;
    /// Called when the user activates this plugin in the Import view.
    /// The plugin should populate its UI controls accordingly.
    virtual void activateImportUI() = 0;

    /// Called when the user activates this plugin in the Export view.
    virtual void activateExportUI() = 0;

    /// Called when the user activates this plugin in the Search view.
    virtual void activateSearchUI() = 0;
};

/// Every plugin shared library must expose a C factory function:
/// 
/// extern "C" IPlugin* createPlugin();
///
/// The host will call createPlugin() to instantiate the plugin.
