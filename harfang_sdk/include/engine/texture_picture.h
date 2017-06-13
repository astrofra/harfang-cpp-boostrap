// Harfang - Copyright 2001-2017 Emmanuel Julien. All Rights Reserved.

#pragma once

#include "engine/picture.h"
#include "engine/renderer.h"

namespace gs {
namespace gpu {

/// Convert a texture format to a picture format.
Picture::Format TextureFormatToPictureFormat(Texture::Format format);
/// Convert a picture format to a texture format.
Texture::Format PictureFormatToTextureFormat(Picture::Format format);

} // gpu
} // gs
