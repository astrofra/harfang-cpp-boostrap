// Harfang - Copyright 2001-2017 Emmanuel Julien. All Rights Reserved.

#pragma once

#include <mutex>
#include <string>
#include <cstdio>

namespace gs {

struct log_file {
	log_file(const char *path_, bool do_timestamp_ = true);
	~log_file();

	void log(const char *msg, bool close = false);

private:
	std::mutex lock;

	FILE *f = nullptr;
	std::string path;

	bool do_timestamp : 1;
	bool initial_write : 1;
};

} // gs
