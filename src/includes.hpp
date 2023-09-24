#pragma once

#define WIN32_LEAN_AND_MEAN
#include <Windows.h>
#undef snprintf
#undef interface

#include "utils/json.hpp"

#include <Geode/Geode.hpp>

using namespace cocos2d;
using namespace cocos2d::extension;
using JSON = nlohmann::json;

namespace gd {
    inline std::uintptr_t base = reinterpret_cast<std::uintptr_t>(GetModuleHandleA(nullptr));
    inline std::uintptr_t cocosBase = reinterpret_cast<std::uintptr_t>(GetModuleHandleA("libcocos2d.dll"));
}