// Harfang - Copyright 2001-2017 Emmanuel Julien. All Rights Reserved.

#pragma once

#include <string>

namespace gs {

struct Version {
	enum Element { Major, Minor, Patch, Count };

	Version() {
		for (int i = 0; i < Count; ++i)
			number[i] = 0;
	}

	Version(int major, int minor = 0, int patch = 0) {
		number[0] = major;
		number[1] = minor;
		number[2] = patch;
	}

	bool operator==(const Version &v) const {
		for (int i = 0; i < Count; ++i)
			if (number[i] != v.number[i])
				return false;
		return true;
	}

	bool operator!=(const Version &v) const { return !(*this == v); }

	bool operator<(const Version &v) const {
		for (int i = 0; i < Count; ++i) {
			if (number[i] < v.number[i])
				return true;
			if (number[i] > v.number[i])
				return false;
		}
		return false;
	}

	bool operator>(const Version &v) const {
		for (int i = 0; i < Count; ++i) {
			if (number[i] > v.number[i])
				return true;
			if (number[i] < v.number[i])
				return false;
		}
		return false;
	}

	bool operator<=(const Version &v) const {
		for (int i = 0; i < Count; ++i) {
			if (number[i] < v.number[i])
				return true;
			if (number[i] > v.number[i])
				return false;
		}
		return true;
	}

	bool operator>=(const Version &v) const {
		for (int i = 0; i < Count; ++i) {
			if (number[i] > v.number[i])
				return true;
			if (number[i] < v.number[i])
				return false;
		}
		return true;
	}

	int number[Count];
};

/// Decode a version string to a version structure.
bool decode_version(const std::string &version_string, Version &version_out);
/// Encode a version structure to a string.
std::string encode_version(const Version &version);

} // gs

namespace std { string to_string(const gs::Version &version); }
