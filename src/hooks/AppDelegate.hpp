#pragma once

#include "../includes.hpp"
#include "../utils/Hook.hpp"
#include "../objects/PatchStorage.hpp"
#include "../bindings/AppDelegate.hpp"
#include "../bindings/CCContentManager.hpp"
#include "../bindings/CCAnimateFrameCache.hpp"

DEFINE_HOOK(bool, AppDelegate, applicationDidFinishLaunching);
GD_HOOK(0x3CBB0, AppDelegate, applicationDidFinishLaunching);