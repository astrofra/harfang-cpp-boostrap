// Harfang - Copyright 2001-2017 Emmanuel Julien. All Rights Reserved.

#pragma once

namespace gs {

template <typename T, int Size> class StaticArrayReadInterface : public ContainerReadInterface {
public:
	StaticArrayReadInterface(const Type *wrapped_type, const void *o) : ContainerReadInterface(wrapped_type) { p_array = reinterpret_cast<const T *>(o); }

	uint GetSize() const override { return Size; }
	TypeValue Get(uint i) const override { return MakeTypeValue<T>(wrapped_type, p_array[i]); }
	const void *GetAddress(uint i) const override { return &p_array[i]; }

private:
	const T *p_array;
};

template <typename T, int Size> class StaticArrayWriteInterface : public ContainerWriteInterface {
public:
	StaticArrayWriteInterface(const Type *wrapped_type, void *o) : ContainerWriteInterface(wrapped_type) { p_array = reinterpret_cast<T *>(o); }

	bool Reserve(uint n) override { return n == Size; }
	void Set(uint i, const TypeValue &v) override { p_array[i] = v.Cast<T>(); }
	void *GetAddress(uint i) const override { return &p_array[i]; }

private:
	T *p_array;
};

template <typename T, int Size> struct StaticArrayInterfaceFactory : public ContainerInterfaceFactory {
	StaticArrayInterfaceFactory(const Type *wrapped_type) : ContainerInterfaceFactory(wrapped_type) {}
	ContainerReadInterface *MakeReadInterface(const void *o) const override { return new StaticArrayReadInterface<T, Size>(wrapped_type, o); }
	ContainerWriteInterface *MakeWriteInterface(void *o) const override { return new StaticArrayWriteInterface<T, Size>(wrapped_type, o); }
};

} // gs
