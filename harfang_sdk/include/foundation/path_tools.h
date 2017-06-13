// Harfang - Copyright 2001-2017 Emmanuel Julien. All Rights Reserved.

#pragma once

#include <string>

namespace gs {
namespace io {

bool IsPathAbsolute(const char *path);

std::string BeautifyPath(std::string path, bool with_space = true);

std::string FactorizePath(const std::string &path);
std::string CleanPath(std::string path);

std::string CutFilePath(const std::string &path);
std::string CutFileName(const std::string &path);
std::string CutFileExtension(const std::string &path);

std::string GetFilePath(const char *path);
std::string GetFileName(const char *path);
std::string GetFileExtension(const std::string &path);

bool PathStartsWith(const std::string &path, const char *with);
std::string PathStripPrefix(const char *path, const char *prefix);
std::string PathStripSuffix(const char *path, const char *suffix);

std::string SwapFileExtension(const std::string &path, const char *ext);

std::string GetCurrentWorkingDirectory();
bool SetCurrentWorkingDirectory(const std::string &path);

} // io
} // gs
