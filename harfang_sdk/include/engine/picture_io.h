// Harfang - Copyright 2001-2017 Emmanuel Julien. All Rights Reserved.

#pragma once

#include "engine/picture_io_codec.h"
#include "foundation/global_object.h"
#include <string>
#include <vector>

namespace gs {

/// Picture I/O class
class PictureIO {
public:
	/// Load a picture.
	bool Load(Picture &, const char *path, const char *codec_name = nullptr);
	/// Save a picture through a specific codec.
	bool Save(const Picture &, const char *path, const char *codec_name, const char *parameters = nullptr);

	/// Return a list of the available picture codecs.
	const std::vector<uIPictureCodec> &GetCodecList() const { return codecs; }
	/// Return a codec from its name.
	IPictureCodec *Codec(const char *codec_name);

	/// Register an I/O codec inside the manager.
	bool RegisterCodec(IPictureCodec *codec, bool verbose = false);
	/// Delete all registered codec.
	void DeleteCodecs() { codecs.clear(); }

	/// Return a comma separated list of supported extensions.
	std::string GetSupportedExt() const;

private:
	std::vector<uIPictureCodec> codecs;
};

extern global_object<PictureIO> g_picture_io;

} // gs
