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

// since everything in cocos2d starts with CC, there is no chance
// for any collision, so it's safe to do this (it also makes using cocos a lot nicer imo)
using namespace nlohmann;

#endif