// PluginManager.cpp

#include "PluginManager.h"
#include "IPlugin.h"

#include <filesystem>

#ifdef _WIN32
  #include <windows.h>
#else
  #include <dlfcn.h>
#endif

PluginManager::PluginManager() = default;

PluginManager::~PluginManager() = default;

void PluginManager::loadPlugins(const std::string& folder) {
    namespace fs = std::filesystem;

    // Ensure the plugins directory exists
    if (!fs::exists(folder) || !fs::is_directory(folder)) {
        return;
    }

    // Iterate over all files in the folder
    for (auto& entry : fs::directory_iterator(folder)) {
        auto path = entry.path();
        if (!fs::is_regular_file(path)) {
            continue;
        }

#ifdef _WIN32
        // Only load .dll files on Windows
        if (path.extension() != ".dll") {
            continue;
        }

        HMODULE lib = LoadLibraryA(path.string().c_str());
        if (!lib) {
            continue;
        }

        using CreateFunc = IPlugin* (*)();
        auto create = reinterpret_cast<CreateFunc>(
            GetProcAddress(lib, "createPlugin")
        );

        if (create) {
            _plugins.emplace_back(std::shared_ptr<IPlugin>(create()));
        }
#else
        // Only load .so files on Unix-like systems
        if (path.extension() != ".so") {
            continue;
        }

        void* lib = dlopen(path.c_str(), RTLD_NOW);
        if (!lib) {
            continue;
        }

        using CreateFunc = IPlugin* (*)();
        auto create = reinterpret_cast<CreateFunc>(
            dlsym(lib, "createPlugin")
        );

        if (create) {
            _plugins.emplace_back(std::shared_ptr<IPlugin>(create()));
        }
#endif
    }
}

std::shared_ptr<IPlugin> PluginManager::findPlugin(const std::string& name) const {
    for (auto& plugin : _plugins) {
        if (plugin->name() == name) {
            return plugin;
        }
    }
    return nullptr;
}
