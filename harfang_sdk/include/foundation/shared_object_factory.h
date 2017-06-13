// Harfang - Copyright 2001-2017 Emmanuel Julien. All Rights Reserved.

#pragma once

#include "foundation/assert.h"
#include <functional>
#include <map>
#include <memory>
#include <string>
#include <vector>

namespace gs {

template <class T> class SharedObjectFactory {
public:
	void Register(const char *name, std::function<void *()> alloc, std::function<void (void *)> free) {
		auto &a_f = factories[name];
		a_f.alloc = std::move(alloc);
		a_f.free = std::move(free);
	}

	void Unregister(const char *name) {
		factories.erase(name);
	}

	std::shared_ptr<T> Instantiate() const {
		__ASSERT_MSG__(factories.size() > 0, "No factory available to instantiate type");
		return std::shared_ptr<T>(reinterpret_cast<T*>(factories.begin()->second.alloc()), factories.begin()->second.free);
	}

	std::shared_ptr<T> Instantiate(const char *name) const {
		auto i = factories.find(name);
		if (i == factories.end())
			return nullptr;
		auto &a_f = i->second;
		return std::shared_ptr<T>(reinterpret_cast<T*>(a_f.alloc()), a_f.free);
	}

	std::vector<std::string> GetNames() const {
		std::vector<std::string> names;
		for (auto &i : factories)
			names.push_back(i.first);
		return names;
	}

private:
	struct alloc_free {
		std::function<void *()> alloc;
		std::function<void (void *)> free;
	};

	std::map<std::string, alloc_free> factories;
};

} // gs
