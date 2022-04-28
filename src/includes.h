#ifndef __INCLUDES_H
#define __INCLUDES_H

#define WIN32_LEAN_AND_MEAN
#include <windows.h>

#include "bindings/AppDelegate.h"
#undef snprintf
#include "utils/json.hpp"
#include <MinHook.h>
#include <fstream>

using std::uintptr_t;
using namespace nlohmann;

#endif