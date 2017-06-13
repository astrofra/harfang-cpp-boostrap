// Harfang - Copyright 2001-2017 Emmanuel Julien. All Rights Reserved.

#pragma once

#include "foundation/types.h"

namespace gs {
namespace random {

#ifndef RAND_MAX
#define RAND_MAX 0x7fff
#endif

/// Set the starting seed of the random number generator.
void Seed(uint s);
/// Return an integer random number in the range [0;r] (default [0;RAND_MAX].
uint Rand(uint r = RAND_MAX);
/// Return a float random value in the range [0;r] (default [0;1]).
float FRand(float r = 1.f);
/// Return a float random value in the range [lo, hi] (default [-1, 1]).
float FRRand(float lo = -1, float hi = 1);

} // random
} // gs
