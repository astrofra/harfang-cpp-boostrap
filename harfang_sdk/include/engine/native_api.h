// GS Framework - Copyright 2001-2015 Emmanuel Julien. All Rights Reserved.

#pragma once

#include "foundation/filesystem.h"

#if ANDROID
# include "android_native_api.h"
#endif // ANDROID

// published app API
#if HARFANG_PUBLISHED

// Return a driver able to access the application data files.
gs::io::sDriver NewAppDataDriver();

// Entry point for a published native app.
void PublishedMain();

#endif // HARFANG_PUBLISHED
