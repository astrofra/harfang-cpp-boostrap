// Harfang - Copyright 2001-2017 Emmanuel Julien. All Rights Reserved.

#pragma once

#include "foundation/call.h"
#include "foundation/signal.h"
#include <atomic>
#include <functional>
#include <string>

namespace gs {
namespace gpu {

enum ResourceState { NotReady = 0, Ready, Failed };

/// Base resource
struct Resource : std::enable_shared_from_this<Resource> {
	explicit Resource(const char *name = "Resource") : name(name) {}
	Resource(const Resource &) = delete;
	virtual ~Resource() {}

	const std::string &GetName() const { return name; }

	virtual bool IsReadyOrFailed() const { return resource_state != NotReady; }
	virtual bool IsFailed() const { return resource_state == Failed; }

	void SetReady() const;
	void SetFailed() const;
	bool SetNotReady() const;

	/// Queue a call to be executed when a resource state changes.
	void QueueOnStateChange(std::function<void()> call);

private:
	mutable std::atomic<ResourceState> resource_state{NotReady};
	std::string name;
};

} // gpu
} // gs
