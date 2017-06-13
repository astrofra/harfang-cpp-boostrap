// Harfang - Copyright 2001-2017 Emmanuel Julien. All Rights Reserved.

#pragma once

#include "foundation/cext.h"
#include "foundation/io_driver.h"
#include "foundation/base_handle.h"
#include <mutex>

namespace gs {
namespace io {

class Handle : public BaseHandle {
public:
	Handle() = delete;
	Handle(sDriver driver_) : driver(driver_) {}

	size_t GetSize() override;

	size_t Rewind() override;
	bool IsEOF() override;

	size_t Tell() override;
	size_t Seek(ptrdiff_t offset, SeekRef ref = SeekCurrent) override;

	size_t Read(void *out_data, size_t size) override;
	size_t Write(const void *in_data, size_t size) override;

	template <class T> bool Write(const T &v) { return BaseHandle::Write<T>(v); }
	template <class T> T Read() { return BaseHandle::Read<T>(); }

	void lock() { lock_.lock(); }
	void unlock() { lock_.unlock(); }

	sDriver GetDriver() const { return driver; }

protected:
	std::recursive_mutex lock_;
	sDriver driver;
};

} // io
} // gs
