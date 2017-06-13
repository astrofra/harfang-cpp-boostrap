// Harfang - Copyright 2001-2017 Emmanuel Julien. All Rights Reserved.

#pragma once

#include <algorithm>
#include <functional>
#include <memory>
#include <mutex>
#include <vector>

namespace gs {

template <typename Signature> class Signal;

template <typename T> struct SignalControllerTraits {
	typedef std::function<void(T)> Type;

	template <typename Func, typename ... Args> static void Apply(const Type &controller, const Func &f, Args&&... args) {
		controller(f(args...));
	}
};

template <> struct SignalControllerTraits<void> {
	typedef std::function<void()> Type;

	template <typename Func, typename ... Args> static void Apply(const Type &controller, const Func &f, Args&&... args) {
		f(args...);
		controller();
	}
};

template <typename Result, typename... Args> class Signal<Result(Args...)> {
	using Listener = std::function<Result(Args...)>;

public:
	struct Connection {
		Connection(Listener *l_ = nullptr) : l(l_) {}
		Listener *l;
	};

	Connection Connect(Listener l) {
		std::lock_guard<std::mutex> guard(lock);
		auto c = std::make_shared<Listener>(std::move(l));
		listeners.push_back(c);
		return Connection(c.get());
	}

	void Disconnect(Connection cnx) {
		std::lock_guard<std::mutex> guard(lock);
		listeners.erase(std::remove_if(listeners.begin(), listeners.end(), [cnx](const std::shared_ptr<Listener> &c) { return c.get() == cnx.l; }), listeners.end());
	}

	void DisconnectAll() {
		std::lock_guard<std::mutex> guard(lock);
		listeners.clear();
	}

	void Emit(Args... args) const {
		lock.lock();
		auto local_connections = listeners; // allow changes while emitting
		lock.unlock();

		for (auto &connection : local_connections)
			(*connection)(args...);
	}

	void Emit(const typename SignalControllerTraits<Result>::Type &controller, Args... args) const {
		lock.lock();
		auto local_connections = listeners; // allow changes while emitting
		lock.unlock();

		for (auto &connection : local_connections)
			SignalControllerTraits<Result>::Apply(controller, *connection, args...);
	}

	int GetListenerCount() const { return listeners.size(); }
	const std::vector<std::shared_ptr<Listener>> &GetListeners() const { return listeners; }

private:
	mutable std::mutex lock;
	std::vector<std::shared_ptr<Listener>> listeners;
};

} // gs
