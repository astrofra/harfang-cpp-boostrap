// GS Framework - Copyright 2001-2015 Emmanuel Julien. All Rights Reserved.

#pragma once

#include "platform/window_system.h"

struct ANativeWindow;

namespace gs {

struct AndroidWindow : Window {
    ANativeWindow *handle = nullptr;
};

} // gs
