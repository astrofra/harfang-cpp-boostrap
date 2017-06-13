// GS Framework - Copyright 2001-2015 Emmanuel Julien. All Rights Reserved.

#pragma once

#include <jni.h>

// Find a class through the activity class loader object.
jclass FindJavaClass(JNIEnv *env, const char *name);
