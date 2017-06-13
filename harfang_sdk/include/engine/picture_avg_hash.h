// Harfang - Copyright 2001-2017 Emmanuel Julien. All Rights Reserved.

#include <cstdint>

#include "foundation/types.h"

namespace gs {

class Picture;

struct PictureAvgHash {
	/// Return true if the number of differences between two hashes is below threshold.
	bool IsEquivalent(const PictureAvgHash &h, int threshold = 0) const;

	uint32_t v[2];
};

/// Return a picture average hash. Such a hash can be used to perform perceptual comparison.
PictureAvgHash ComputePictureAvgHash(const Picture &);

} // gs
