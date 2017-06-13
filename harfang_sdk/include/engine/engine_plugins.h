// Harfang - Copyright 2001-2017 Emmanuel Julien. All Rights Reserved.

#pragma once

namespace gs {
namespace core {

static const int plugin_host_version = 1;

/// Load engine plugins.
bool LoadPlugins(const char *dir = nullptr, const char *cfg = nullptr);
/// Unload engine plugins.
void UnloadPlugins();

/// To be called from the plugin at load time.
void PluginSetupHost(void *host);

} // core
} // gs
