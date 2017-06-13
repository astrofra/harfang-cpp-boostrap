// Harfang - Copyright 2001-2017 Emmanuel Julien. All Rights Reserved.

#pragma once

#include <cstdint>
#include <chrono>
#include <string>

namespace gs {

typedef int64_t time_t;

inline float time_to_sec_f(time_t t) { return float(t) / 1000000000.f; }
inline float time_to_ms_f(time_t t) { return float(t) / 1000000.f; }
inline float time_to_us_f(time_t t) { return float(t) / 1000.f; }

inline int64_t time_to_day(time_t t) { return t / (1000000000LL * 60 * 60 * 24); }
inline int64_t time_to_hour(time_t t) { return t / (1000000000LL * 60 * 60); }
inline int64_t time_to_min(time_t t) { return t / (1000000000LL * 60); }
inline int64_t time_to_sec(time_t t) { return t / 1000000000; }
inline int64_t time_to_ms(time_t t) { return t / 1000000; }
inline int64_t time_to_us(time_t t) { return t / 1000; }
inline int64_t time_to_ns(time_t t) { return t; }

inline time_t time_from_sec_f(float sec) { return time_t(sec * 1000000000.f); }
inline time_t time_from_ms_f(float ms) { return time_t(ms * 1000000.f); }
inline time_t time_from_us_f(float us) { return time_t(us * 1000.f); }

inline time_t time_from_day(int64_t day) { return day * (1000000000LL * 60 * 60 * 24); }
inline time_t time_from_hour(int64_t hour) { return hour * (1000000000LL * 60 * 60); }
inline time_t time_from_min(int64_t min) { return min * (1000000000LL * 60); }
inline time_t time_from_sec(int64_t sec) { return sec * 1000000000; }
inline time_t time_from_ms(int64_t ms) { return ms * 1000000; }
inline time_t time_from_us(int64_t us) { return us * 1000; }
inline time_t time_from_ns(int64_t ns) { return ns; }

std::chrono::seconds time_to_chrono_sec(time_t t);
std::chrono::milliseconds time_to_chrono_ms(time_t t);
std::chrono::microseconds time_to_chrono_us(time_t t);
std::chrono::nanoseconds time_to_chrono_ns(time_t t);
std::chrono::nanoseconds time_to_chrono(time_t t);

time_t time_now();

std::string time_to_string(time_t t);

} // gs
