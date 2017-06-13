// Harfang - Copyright 2001-2017 Emmanuel Julien. All Rights Reserved.

#pragma once

#include <vector>
#include <string>

namespace gs {

struct WatchEvent {
	enum Type { FileAdded, FileRemoved, FileModified };

	Type type;
	std::string path;
};

struct DirectoryWatch {
	virtual ~DirectoryWatch() {}
	virtual void GetEvents(std::vector<WatchEvent> &out_events) = 0;
};

DirectoryWatch *WatchDirectoryForModification(const char *absolute_path_to_directory, bool recursive);

} // gs
