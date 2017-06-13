// Harfang - Copyright 2001-2017 Emmanuel Julien. All Rights Reserved.

#pragma once

#include "foundation/call_queue_mt.h"

namespace gs {
namespace main_thread {

/// Initialize main thread related informations.
void init();

/// Return true if the calling thread is the main thread.
bool is();

/*!
	@short Return the main thread call queue.

	This queue is periodically consumed by the main thread from future::wait().

	This is required for OSX to be able to perform UI calls from the main thread
	while still preserving a sane multi-threaded API.
*/
extern call_queue_mt *call_queue;

/// Queue a call to be executed on the main thread.
void queue(future_call<void> *call);

/// Queue a call to be executed on the main thread.
template <typename R> std::future<R> queue(future_call<R> *call) {
	auto r = call->get_future();

	if (is())
		call->execute();
	else
		call_queue->queue(call);

	return r;
}

/// Yield execution if caller is the main thread.
void yield_if_main();

} // main_thread
} // gs
