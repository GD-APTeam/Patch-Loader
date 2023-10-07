#pragma once

#define WIN32_LEAN_AND_MEAN
#include <Windows.h>
#undef snprintf
#undef interface

#include <nlohmann/json.hpp>
#include <Geode/Geode.hpp>

using namespace cocos2d;
using namespace cocos2d::extension;
using JSON = nlohmann::json;

#define FULL_OPACITY 0xFF

#define WHITE_4B { 0xFF, 0xFF, 0xFF, FULL_OPACITY }
#define BROWN_AREA_4B { 0x82, 0x40, 0x21, FULL_OPACITY }
#define LIST_AREA_4B { 0xBF, 0x72, 0x3E, FULL_OPACITY }
#define DISABLED_4B { 0xE0, 0xE0, 0xE0, FULL_OPACITY }

#define SPRITE_RECT CCRect(0, 0, 80, 80)

#define ZERO_POINT { 0, 0 }

#define TOP_LEFT { 0, 1 }
#define TOP_CENTER { 0.5f, 1 }
#define TOP_RIGHT { 1, 1 }

#define CENTER_LEFT { 0, 0.5f }
#define CENTER { 0.5f, 0.5f }
#define CENTER_RIGHT { 1, 0.5f }

#define BOTTOM_LEFT { 0, 0 }
#define BOTTOM_CENTER { 0.5f, 0 }
#define BOTTOM_RIGHT { 0, 1 }

namespace gd {
    inline bool started = false;
    inline std::uintptr_t base = reinterpret_cast<std::uintptr_t>(GetModuleHandleA(nullptr));
    inline std::uintptr_t cocosBase = reinterpret_cast<std::uintptr_t>(GetModuleHandleA("libcocos2d.dll"));
    inline HANDLE process = GetCurrentProcess();
}