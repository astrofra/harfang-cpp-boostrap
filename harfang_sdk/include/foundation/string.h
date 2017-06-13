// Harfang - Copyright 2001-2017 Emmanuel Julien. All Rights Reserved.

#pragma once

#include <string>
#include <vector>

namespace gs {

/*
 * Routine to see if a text string is matched by a wildcard pattern.
 * Returns TRUE if the text is matched, or FALSE if it is not matched
 * or if the pattern is invalid.
 *  *		matches zero or more characters
 *  ?		matches a single character
 *  [abc]	matches 'a', 'b' or 'c'
 *  \c		quotes character c
*/
bool match_wildcard(const char *text, const char *pattern);

} // gs

namespace std {

enum case_sensitivity { insensitive, sensitive };

inline char to_lower(char c) { return c >= 'A' && c <= 'Z' ? c - 'A' + 'a' : c; }

inline bool starts_with(const string &value, const string &prefix, case_sensitivity sensitivity = case_sensitivity::sensitive) {
	if (prefix.size() > value.size())
		return false;

	return sensitivity == case_sensitivity::sensitive
			   ? equal(prefix.begin(), prefix.end(), value.begin(), [](const char &a, const char &b) { return a == b; })
			   : equal(prefix.begin(), prefix.end(), value.begin(), [](const char &a, const char &b) { return to_lower(a) == to_lower(b); });
}

inline bool ends_with(const string &value, const string &suffix, case_sensitivity sensitivity = case_sensitivity::sensitive) {
	if (suffix.size() > value.size())
		return false;

	return sensitivity == case_sensitivity::sensitive
			   ? equal(suffix.rbegin(), suffix.rend(), value.rbegin(), [](const char &a, const char &b) { return a == b; })
			   : equal(suffix.rbegin(), suffix.rend(), value.rbegin(), [](const char &a, const char &b) { return to_lower(a) == to_lower(b); });
}

/// In-place replace all occurrences of 'what' by 'by'. Returns the number of occurrence replaced.
int replace_all(string &inplace_replace, const string &what, const string &by);
inline int replace_all(string &inplace_replace, const char *what, const char *by) { return replace_all(inplace_replace, string(what), string(by)); }

template <typename T> int replace_all(string &inplace_replace, const T &what, const T &by) {
	int count = 0;
	if (what.size() == by.size())
		for (size_t i = 0; i < what.size(); ++i)
			count += replace_all(inplace_replace, what[i], by[i]);
	return count;
}

/// Split string against a separator string.
vector<string> split(const string &value, const string &separator, const string &trim = "");

string lstrip(const string &str, const string &pattern = " ");
string rstrip(const string &str, const string &pattern = " ");

string trim(const string &str, const string &pattern = " ");
string reduce(const string &str, const string &fill = " ", const string &pattern = " ");

/// Join several strings with a separator string.
template <typename T> string join(T begin_it, T end_it, const string &separator) {
	auto count = std::distance(begin_it, end_it);

	if (!count)
		return string();
	if (count == 1)
		return *begin_it;

	--end_it;

	string out;
	for (auto i = begin_it; i != end_it; ++i)
		out = out + *i + separator;

	return out + *end_it;
}

bool contains(const string &in, const string &what);

string wstring_to_utf8(const wstring &str);
wstring utf8_to_wstring(const string &str);

string utf32_to_utf8(const u32string &str);
u32string utf8_to_utf32(const string &str);

void lower(string &inplace_lower_str, int start = 0, int end = 0);
string lowered(const string &inplace_lower_str, int start = 0, int end = 0);
void upper(string &inplace_upper_str, int start = 0, int end = 0);
string uppered(const string &inplace_upper_str, int start = 0, int end = 0);

/// Take a slice from a string. 'from < 0' starts 'from' characters from the right of the string. 'count < 0' returns all characters after 'from' minus 'count'.
string slice(const string &str, int from, int count = 0);

string left(const string &str, int count);
string right(const string &str, int count);

enum EOLConvention { EOLUnix, EOLWindows };

void normalize_eol(string &inplace_normalize, EOLConvention = EOLUnix);

string strip_prefix(const string &str, const string &prefix);
string strip_suffix(const string &str, const string &suffix);

} // std
