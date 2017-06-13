// Harfang - Copyright 2001-2017 Emmanuel Julien. All Rights Reserved.

#pragma once

namespace gs {
namespace gpu {

enum Caps {
	/*!
	@name Hardware caps.
	@{
*/
	MaxTextureSize,
	MaxTextureUnit,

	CanBlitRBO,
	TextureTopLeftOrigin,

	MaxAnisotropy,
	/*!
	@}
	@name Performance hints
	@{
*/
	CheapLights
	/// @}
};

enum NPOTSupport {
	NPOTNone = 0,
	NPOTLimited, // NPOT support with no mip-map and wrap as clamp to edge only.
	NPOTFull
};

} // gpu
} // gs
