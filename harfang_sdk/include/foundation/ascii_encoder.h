// Harfang - Copyright 2001-2017 Emmanuel Julien. All Rights Reserved.

#pragma once

#include "foundation/types.h"
#include <cstddef>

namespace gs {

/*!
    @short	Perform UUEncoding.

    @param	source		Input binary stream.
    @param	len			Input binary stream length.
    @param	uuenc		Output buffer.
    @param	max			Output buffer length.
    @return				The number of bytes written to the output buffer.

    @note	If yenc is nullptr the function can be used to check the size
            of the encoded stream prior to allocating an output buffer.
*/
uint UUEncode(const void *source, size_t len, void *uuenc = nullptr, size_t max = 0);

/*!
    @short	Perform UUDecoding.

    @param	source		UUEncoded byte stream.
    @param	len			UUEncoded byte stream length.
    @param	bin			Output buffer.
    @param	max			Output buffer length.
    @return				The number of bytes written to the output buffer.

    @note	If bin is nullptr the function can be used to check the size
            of the decoded stream prior to allocating an output buffer.
*/
uint UUDecode(const void *source, size_t len, void *bin = nullptr, size_t max = 0);
/*!
    @short	Perform yEncoding.

    @param	source		Input binary stream.
    @param	len			Input binary stream length.
    @param	yenc		Output buffer.
    @param	max			Output buffer length.
    @param	line_len	Number of character to output before a line-feed character is sent.
    @return				The number of bytes written to the output buffer.

    @note	If yenc is nullptr the function can be used to check the size
            of the encoded stream prior to allocating an output buffer.
*/
uint yEncode(const void *source, size_t len, void *yenc = nullptr, size_t max = 0, uint line_len = 64);

/*!
    @short	Perform yDecoding.

    @param	source		yEncoded byte stream.
    @param	len			yEncoded byte stream length.
    @param	bin			Output buffer.
    @param	max			Output buffer length.
    @return				The number of bytes written to the output buffer.

    @note	If bin is nullptr the function can be used to check the size
            of the decoded stream prior to allocating an output buffer.
*/
uint yDecode(const void *source, size_t len, void *bin = nullptr, size_t max = 0);

} // gs
