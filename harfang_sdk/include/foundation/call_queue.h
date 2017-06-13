// Harfang - Copyright 2001-2017 Emmanuel Julien. All Rights Reserved.

#pragma once

#include <vector>
#include <memory>

#include "foundation/call.h"

namespace gs {

/// Call queue
class call_queue {
	using queue_type = std::vector<std::unique_ptr<future_call_base>>;

public:
	template <typename R> inline std::future<R> queue_with_return_value(std::function<R()> f) {
		auto call = new future_call_with_return_value<R>(std::move(f));
		q[q_idx].emplace_back(call);
		return call->get_future();
	}

	template <typename R> inline void queue(std::function<R()> f) { q[q_idx].emplace_back(new future_call<R>(std::move(f))); }

	inline queue_type::size_type size() { return q[q_idx].size(); }

	void execute() {
		while (true) {
			q_idx = 1 - q_idx;

			auto &exec_calls = q[1 - q_idx];
			if (exec_calls.size() == 0)
				break;

			for (auto &call : exec_calls)
				(*call)();

			exec_calls.clear();
		}
	}

private:
	int q_idx = 0;
	queue_type q[2];
};

} // gs
