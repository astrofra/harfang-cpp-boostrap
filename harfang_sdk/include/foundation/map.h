// Harfang - Copyright 2001-2017 Emmanuel Julien. All Rights Reserved.

#pragma once

#include <map>

template <typename K, typename V, typename M> const V &MapGetWithDefault(const M &map, const K &key, const V &dflt) {
	auto i = map.find(key);
	return i != map.end() ? i->second : dflt;
}
