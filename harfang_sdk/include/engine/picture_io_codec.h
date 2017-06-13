// Harfang - Copyright 2001-2017 Emmanuel Julien. All Rights Reserved.

#pragma once

#include "foundation/io_handle.h"
#include <memory>

namespace gs {

class Picture;

namespace PictureCodecCaps {
	typedef int Type;

	static const int CanRead = 0x01, ///< Codec can read data.
		CanWrite = 0x02,			 ///< Codec can write data.
		WriteRaw = 0x04,			 ///< Codec supports raw output.
		WriteLossy = 0x08,			 ///< Codec supports lossy compression.
		WriteLossless = 0x10,		 ///< Codec supports lossless compression.
		AlphaChannel = 0x20,		 ///< Codec supports alpha channel.
		RealData = 0x40;			 ///< Codec supports real data.
}

/// Picture I/O codec
struct IPictureCodec {
	virtual bool Load(io::Handle &handle, Picture &picture) = 0;
	virtual bool Save(io::Handle &handle, const Picture &picture, const char *parm = nullptr) { return false; }

	virtual const char *GetName() const = 0;

	virtual PictureCodecCaps::Type GetCaps() const = 0;
	virtual const char *GetSupportedExt() const = 0;
};

typedef std::unique_ptr<IPictureCodec> uIPictureCodec;

} // gs
