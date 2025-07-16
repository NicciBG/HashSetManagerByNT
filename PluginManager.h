// PluginManager.h

#pragma once

#include "IPlugin.h"
#include <vector>
#include <memory>
#include <string>

class PluginManager {
public:
    // Constructor / destructor
    PluginManager();
    ~PluginManager();

    // Scan the given directory for .dll / .so plugins and load them.
    // Default folder is "plugins" next to the executable.
    void loadPlugins(const std::string& folder = "plugins");

    // Return the list of loaded plugins.
    const std::vector<std::shared_ptr<IPlugin>>& plugins() const {
        return _plugins;
    }

    // Find a plugin by its unique name (returns nullptr if not found).
    std::shared_ptr<IPlugin> findPlugin(const std::string& name) const;

private:
    // Holds ownership of each plugin instance
    std::vector<std::shared_ptr<IPlugin>> _plugins;
};
