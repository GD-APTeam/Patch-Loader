#pragma once

#define WIN32_LEAN_AND_MEAN
#include <windows.h>
#include <MinHook.h>
#include <gd.h>
#include <cocos2d.h>
#undef snprintf
#include "json.hpp"

using namespace gd;
using namespace cocos2d;
using namespace cocos2d::extension;
using namespace nlohmann;
using hook_t = std::tuple<bool, std::uintptr_t, LPVOID, LPVOID*>;

namespace gd {
    inline std::uintptr_t cocosBase = reinterpret_cast<std::uintptr_t>(GetModuleHandleA("libcocos2d.dll"));
    inline std::vector<hook_t> hooks {};
    inline bool started = false;
}