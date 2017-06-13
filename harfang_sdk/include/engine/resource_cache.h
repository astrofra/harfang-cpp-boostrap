// Harfang - Copyright 2001-2017 Emmanuel Julien. All Rights Reserved.

#pragma once

#include <algorithm>
#include <functional>
#include <memory>
#include <mutex>
#include <vector>

namespace gs {

template <typename T> class TCache {
	typedef std::shared_ptr<T> sT;
	typedef std::vector<sT> sTList;

public:
	/// Purge resource cache, remove resources with no external reference.
	typename sTList::size_type Purge() {
		std::lock_guard<std::mutex> guard(access);
		auto before = cache.size();
		cache.erase(std::remove_if(cache.begin(), cache.end(), [](const sT &s) { return s.use_count() == 1; }), cache.end());
		return before - cache.size();
	}

	/// Clear resource cache, unconditionally remove all resources.
	void Clear() {
		std::lock_guard<std::mutex> guard(access);
		cache.clear();
	}

	/// Test cache for the presence of a resource.
	sT Has(const char *name) const {
		std::lock_guard<std::mutex> guard(access);
		auto i = std::find_if(cache.begin(), cache.end(), [name](const sT &t) { return t->GetName() == name; });
		return i != cache.end() ? *i : nullptr;
	}

	/// Test cache for the presence of a resource, create it if missing.
	sT HasOrMake(const char *name, bool &had, std::function<sT(const char *)> make) {
		had = true;

		std::lock_guard<std::mutex> guard(access);
		auto i = std::find_if(cache.begin(), cache.end(), [name](const sT &t) { return t->GetName() == name; });
		if (i != cache.end())
			return *i;

		had = false;
		cache.emplace_back(make(name));
		return cache.back();
	}

	/// Add a resource to the cache.
	void Add(sT t) {
		std::lock_guard<std::mutex> guard(access);
		cache.emplace_back(std::move(t));
	}

	/// Return the cache content.
	const sTList &GetContent() const { return cache; }

private:
	mutable std::mutex access;
	sTList cache;
};

} // gs
