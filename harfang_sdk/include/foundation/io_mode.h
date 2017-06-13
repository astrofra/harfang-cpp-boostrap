// Harfang - Copyright 2001-2017 Emmanuel Julien. All Rights Reserved.

#pragma once

namespace gs {
namespace io {

enum Mode { ModeRead = 0, ModeWrite };

namespace DriverCaps {
	typedef int Type;
	static const Type IsCaseSensitive = 0x01, CanRead = 0x02, CanWrite = 0x04, CanSeek = 0x08, CanDelete = 0x10, CanMkDir = 0x20;
}

} // io
} // gs
