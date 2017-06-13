// Harfang - Copyright 2001-2017 Emmanuel Julien. All Rights Reserved.

// Support for std::list reflection

#pragma once

#include <list>
#include "foundation/reflection.h"

namespace gs {

template <typename T> class StdListReadInterface : public ContainerReadInterface {
public:
	StdListReadInterface(const Type *wrapped_type, const void *o) : ContainerReadInterface(wrapped_type) { p_list = reinterpret_cast<const std::list<T> *>(o); }

	uint GetSize() const override { return p_list->size(); }

	TypeValue Get(uint idx) const override {
		auto i = p_list->begin();
		std::advance(i, idx);
		return TypeValue(wrapped_type, &(*i));
	}

	const void *GetAddress(uint idx) const override {
		auto i = p_list->begin();
		std::advance(i, idx);
		return &(*i);
	}

private:
	const std::list<T> *p_list;
};

template <typename T> class StdListWriteInterface : public ContainerWriteInterface {
public:
	StdListWriteInterface(const Type *wrapped_type, void *o) : ContainerWriteInterface(wrapped_type) { p_list = reinterpret_cast<std::list<T> *>(o); }

	bool Reserve(uint n) override {
		for (uint i = 0; i < n; ++i)
			p_list->push_back(T());
		return true;
	}

	void Set(uint idx, const TypeValue &v) override {
		auto i = p_list->begin();
		std::advance(i, idx);
		*i = v.Cast<T>();
	}

	void *GetAddress(uint idx) const override {
		auto i = p_list->begin();
		std::advance(i, idx);
		return &(*i);
	}

private:
	std::list<T> *p_list;
};

template <typename T> struct StdListInterfaceFactory : ContainerInterfaceFactory {
	StdListInterfaceFactory(const Type *wrapped_type) : ContainerInterfaceFactory(wrapped_type) {}
	ContainerReadInterface *MakeReadInterface(const void *o) const override { return new StdListReadInterface<T>(wrapped_type, o); }
	ContainerWriteInterface *MakeWriteInterface(void *o) const override { return new StdListWriteInterface<T>(wrapped_type, o); }
};

} // gs
