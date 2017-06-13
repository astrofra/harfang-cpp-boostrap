// Harfang - Copyright 2001-2017 Emmanuel Julien. All Rights Reserved.

#pragma once

#include "foundation/global_object.h"
#include "foundation/log_tail.h"
#include "foundation/signal.h"
#include "foundation/format.h" // this should be the only place format is included in a header
#include "foundation/timer.h"
#include <mutex>
#include <vector>

namespace gs {

struct log_entry {
	log_entry(const std::string &m, const std::string &p, const std::string &d) : msg(m), prefix(p), details(d) {}
	std::string msg, prefix, details;
};

namespace LogLevel {
using mask_type = unsigned int;
static const mask_type Message = 0x1, Warning = 0x2, Error = 0x4, Debug = 0x8, All = 0xff;
}

typedef std::vector<log_entry> log_queue;

class log_system {
public:
	log_system();

	/// Immediate log output.
	void (*immediate_log_output)(const std::string &msg, const std::string &prefix, const std::string &details, LogLevel::mask_type output_mask, bool output_details);

	/// This signal is periodically triggered from the timer thread with new log entries.
	Signal<void(const log_queue &)> on_log_signal;

	/// Return the log tail object.
	const log_tail &get_tail() const { return tail; }

	void output(const std::string &msg, const std::string &prefix, const std::string &details);
	void flush();

	void shutdown();

private:
	void process_log_queue();

	std::mutex queue_mutex;
	log_queue queue;

	std::mutex tail_mutex;
	log_tail tail;

	friend void SetDefaultLogOutputLevelMask(LogLevel::mask_type);
	LogLevel::mask_type default_log_output_level_mask = LogLevel::Warning | LogLevel::Error;

	friend void SetDefaultLogOutputIsDetailed(bool);
	bool default_log_output_is_detailed = false;

	timer_thread::handle timer_handle = timer_thread::null_handle;
};

extern global_object<log_system> g_log;

/// Set the default log level mask.
void SetDefaultLogOutputLevelMask(LogLevel::mask_type mask);
/// Enable default log detailed output.
void SetDefaultLogOutputIsDetailed(bool is_detailed);

/// Immediately flush queued log output.
void FlushLog();

void log(const char *msg, const char *prefix = "", const char *details = "");
void warn(const char *msg, const char *details = "");
void error(const char *msg, const char *details = "");
void debug(const char *msg, const char *details = "");

} // gs
