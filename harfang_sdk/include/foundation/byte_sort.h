// Harfang - Copyright 2001-2017 Emmanuel Julien. All Rights Reserved.

#pragma once

#include <cstdint>
#include <vector>

namespace gs {

template <typename T, typename O> struct ByteSort {
	struct Entry {
		T v;
		O o;
	};

	/// ByteSort sort n entries using two arrays as swap, returns a pointer to the sorted array.
	static Entry *Sort(uint32_t count, Entry *__restrict a, Entry *__restrict b) {
		uint32_t radix[sizeof(T) * 256];

		// build radix histogram
		memset(radix, 0, 4 * sizeof(T) * 256); // 4K for 32 bit T
		const Entry *__restrict p_a = a;

		uint32_t *__restrict p_radix = radix;
		for (uint32_t i = 0; i < count; ++i) {
			const uint8_t *v = reinterpret_cast<const uint8_t *>(p_a + i);
			for (int r = 0; r < sizeof(T); ++r)
				++p_radix[v[r] + r * 256];
		}

		// perform sort
		for (size_t r = 0; r < sizeof(T); ++r) {
			uint32_t *__restrict p_radix = radix + r * 256;

			// convert count to index
			uint32_t t = 0;
			for (int i = 0; i < 256; ++i) {
				uint32_t v = p_radix[i];
				p_radix[i] = t;
				t += v;
			}

			// insert values
			const Entry *__restrict p_a = a;
			Entry *__restrict p_b = b;

			for (uint32_t i = 0; i < count; i++) {
				const Entry *e = p_a + i;
				const uint32_t p = p_radix[reinterpret_cast<const uint8_t *>(e)[r]]++;
				p_b[p] = *e;
			}

			Entry *tmp = b;
			b = a;
			a = tmp;
		}
		return a;
	}
};

typedef uint32_t bytesort_float;

static inline bytesort_float to_bytesort_float(float f) {
	auto p = reinterpret_cast<bytesort_float *>(&f);
	return (*p & 0x80000000) ? 0x7fffffff - (*p & 0x7fffffff) : 0x80000000 | *p;
}

static inline float from_bytesort_float(bytesort_float i) {
	auto p = reinterpret_cast<bytesort_float *>(&i);
	*p = (*p & 0x80000000) ? *p & 0x7fffffff : 0x80000000 | (0x7fffffff - *p);
	return *reinterpret_cast<float *>(p);
}

} // gs
