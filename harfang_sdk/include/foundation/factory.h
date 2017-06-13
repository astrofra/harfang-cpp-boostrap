// Harfang - Copyright 2001-2017 Emmanuel Julien. All Rights Reserved.

#pragma once

#include "foundation/assert.h"
#include <map>
#include <string>
#include <vector>

namespace gs {

template <class T> class Factory {
public:
	void Register(const char *name, void *(*factory)()) { factories[name] = factory; }

	T *Instantiate(const char *name) const {
		auto i = factories.find(name);
		return i != factories.end() ? reinterpret_cast<T *>((*i->second)()) : nullptr;
	}

	std::vector<std::string> GetNames() const {
		std::vector<std::string> names;
		for (auto &i : factories)
			names.push_back(i.first);
		return names;
	}

private:
	std::map<std::string, void *(*)()> factories;
};

} // gs
