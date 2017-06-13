// Harfang - Copyright 2001-2017 Emmanuel Julien. All Rights Reserved.

#pragma once

#include <mutex>
#include <thread>
#include <vector>
#include "foundation/time.h"
#include "foundation/types.h"
#include "foundation/global_object.h"

namespace gs {

struct ProfilerFrame {
	uint frame;

	struct Section {
		Section() = default;
		Section(const Section &) = default;
		Section(Section &&s) : thread_id(s.thread_id), start(s.start), end(s.end), details(std::move(s.details)) {}

		std::thread::id thread_id;
		time_t start = 0, end = 0;
		std::string details;
	};

	struct Task {
		std::string name;
		time_t duration;
		std::vector<uint> section_indexes;
	};

	std::vector<Section> sections;
	std::vector<Task> tasks;

	time_t start, end;
};

class Profiler {
public:
	struct Section {
		std::thread::id thread_id;
		time_t start = 0, end = 0;
		std::string details;
	};

	struct Task {
		std::string name;
		std::vector<uint> section_indexes;
	};

	typedef uint SectionIndex;

	void EndFrame();

	uint GetFrame() const { return frame; }
	const ProfilerFrame &GetLastFrameProfile() const { return last_frame_profile; }

	/// Begin a performance section.
	SectionIndex BeginSection(const std::string &name, const char *section_details = "");
	/// End a performance section.
	void EndSection(SectionIndex section_index);

	const Task &GetTask(uint idx) const { return tasks[idx]; }

	void Lock();
	void Unlock();

private:
	std::mutex lock;

	uint GetTaskBucket(const std::string &name) const;
	uint GetTaskInBucket(uint bucket_index, const std::string &name);

	std::vector<uint> task_bucket[256];

	std::vector<Task> tasks;
	std::vector<Section> sections;

	void CaptureFrame(ProfilerFrame &frame);

	uint frame = 0;
	ProfilerFrame last_frame_profile;
};

class ProfilerPerfSection {
public:
	ProfilerPerfSection(const char *task_name, const char *section_details = "");
	~ProfilerPerfSection();

	void EndSection();

private:
	bool open;
	Profiler::SectionIndex section_index;
};

extern global_object<Profiler> g_profiler;

} // gs
