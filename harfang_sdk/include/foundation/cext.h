#pragma once

#include <string>
#include <memory>
#include <algorithm>

template <typename T> inline bool asbool(const T &v) { return v ? true : false; }

#define forever while(true)
#define unused(ARG)

#define __ERR__(err_exp, ret_exp) { (err_exp); return (ret_exp); }
#define __ERRRAW__(err_exp) { (err_exp); return; }

/// Set 'variable' value if it does not compare equal to 'value', return true if 'variable' was modified.
template <typename T> inline bool set_if_not_equal(T &variable, const T &value) {
	bool r = variable != value;
	if (r)
		variable = value;
	return r;
}

/// Set 'variable' value if it does not compare equal to 'value', return true if 'variable' was modified.
template <typename T> inline bool set_if_not_equal(T &variable, const T &&value) {
	bool r = variable != value;
	if (r)
		variable = std::move(value);
	return r;
}

/// Bind shared_ptr<T> to functions expecting T&, const T&, T* or const T*.
template <typename T> struct shared_ref_ {
	shared_ref_(const std::shared_ptr<T> &r_) : r(r_) {}
	shared_ref_(std::shared_ptr<T> &&r_) : r(std::move(r_.r)) {}

	operator T &() const { return *r; }
	operator T *() const { return r.get(); }

	std::shared_ptr<T> r;
};

template <typename T> shared_ref_<T> shared_ref(const std::shared_ptr<T> &p) { return shared_ref_<T>(p); }
template <typename T> shared_ref_<T> shared_ref(const std::shared_ptr<T> &&p) { return shared_ref_<T>(p); }

template <typename T, typename D> shared_ref_<T> shared_ref_cast(const std::shared_ptr<D> &p) { return shared_ref<T>(std::static_pointer_cast<D>(p)); }

/// Bind std::string to functions expecting const char *.
struct bind_string {
	explicit bind_string(const char *s_) : str(s_) {}
	explicit bind_string(const std::string &s_) : str(s_) {}
	explicit bind_string(const std::string &&s_) : str(std::move(s_)) {}

	operator const char *() const { return str.c_str(); }

	std::string str;
};

// plain raw memory block
template <typename T> struct memory_block {
	memory_block() : data(nullptr), size(0) {}
	memory_block(const T *data_, size_t size_) : data(new char[size_]), size(size_) { memcpy(data, data_, size_); }
	~memory_block() { delete [] data; }

	operator const T *() const { return reinterpret_cast<T *>(data); }

	T *get_data() const { return reinterpret_cast<T *>(data); }
	size_t get_size() const { return size; }

private:
	char *data;
	size_t size;
};

template <typename C, typename V> bool find_erase(C &c, const V &v) {
	auto i = std::find(c.begin(), c.end(), v);
	if (i == c.end())
		return false;
	c.erase(i);
	return true;
}

template <typename C, typename V> bool contains(const C &c, const V &v) { return std::find(c.begin(), c.end(), v) != c.end(); }

// until C++17 and std::enable_shared_from_this::weak_from_this()
template <typename T> std::weak_ptr<T> weak_from_this(std::enable_shared_from_this<T> *s) { return std::weak_ptr<T>(s->shared_from_this()); }
template <typename T> std::weak_ptr<const T> weak_from_this(const std::enable_shared_from_this<T> *s) { return std::weak_ptr<const T>(s->shared_from_this()); }

/*
namespace std {
template<typename T, typename... Args> std::unique_ptr<T> make_unique(Args&&... args) { return std::unique_ptr<T>(new T(std::forward<Args>(args)...)); }
}
*/

// from https://channel9.msdn.com/Events/GoingNative/2013/Cpp-Seasoning
template <typename I> auto slide(I f, I l, I p) -> std::pair<I, I> { // I model RandomAccessIterator
	if (p < f)
		return {p, std::rotate(p, f, l)};
	if (l < p)
		return {std::rotate(f, l, p), p};
	return {f, l};
}
