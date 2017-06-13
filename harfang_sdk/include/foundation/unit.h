// Harfang - Copyright 2001-2017 Emmanuel Julien. All Rights Reserved.

#pragma once

#include <iomanip>
#include <sstream>
#include <string>

namespace gs {
namespace units {

template <typename T> T Deg(T v) { return v / T(180) * T(3.1415926535); }
template <typename T> T Rad(T v) { return v; }

template <typename T> T DegreeToRadian(T v) { return v / T(180) * T(3.1415926535); }
template <typename T> T RadianToDegree(T v) { return v / T(3.1415926535) * T(180); }

template <typename T> T Sec(T v) { return v; }
template <typename T> T Csec(T v) { return v * T(0.01); }
template <typename T> T Ms(T v) { return v * T(0.001); }

template <typename T> T Tick(T v) { return v * T(0.001); }

template <typename T> T Kg(T v) { return v; }
template <typename T> T G(T v) { return v * T(0.001); }

template <typename T> T Km(T v) { return v * T(1000); }
template <typename T> T Mtr(T v) { return v; }
template <typename T> T Cm(T v) { return v * T(0.01); }
template <typename T> T Mm(T v) { return v * T(0.001); }
template <typename T> T Inch(T v) { return v * T(0.0254); }

size_t KB(const size_t size);
size_t MB(const size_t size);

template <typename T> std::string FormatMemorySize(T v_) {
	std::ostringstream str;
	auto v = float(v_);

	if (v < 0) {
		str << "-";
		v = -v;
	}

	if (v < 1024.f)
		str << v << "B";
	else if (v < 1024.f * 1024.f)
		str << std::setfill('0') << std::setprecision(1) << v / 1024.f << "KB";
	else
		str << std::setfill('0') << std::setprecision(1) << v / (1024.f * 1024.f) << "MB";

	return str.str();
}

template <typename T> std::string FormatCount(T v_) {
	std::ostringstream str;
	auto v = float(v_);

	if (v < 0) {
		str << "-";
		v = -v;
	}

	if (v < 1000.f)
		str << v;
	if (v < 1000000.f)
		str << std::setfill('0') << std::setprecision(1) << v / 1000.f << "K";
	else
		str << std::setfill('0') << std::setprecision(1) << v / 1000000.f << "M";

	return str.str();
}

} // units
} // gs
