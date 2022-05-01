#pragma once

// Shut up
#pragma warning( push )
#pragma warning( disable : 4251 )

#define WIN32_LEAN_AND_MEAN
#include <windows.h>
#include <MinHook.h>
#include <gd.h>
#include <cocos2d.h>
#undef snprintf
#include "utils/json.hpp"

using std::uintptr_t;
using namespace gd;
using namespace cocos2d;
using namespace nlohmann;

#include "objects/PatchBase.hpp"

#pragma warning( pop )

struct PatchBase;

namespace gd {
    inline uintptr_t cocosBase = reinterpret_cast<uintptr_t>(GetModuleHandleA("libcocos2d.dll"));
    inline std::vector<std::shared_ptr<PatchBase>> patches {};
    inline bool started = false;
}