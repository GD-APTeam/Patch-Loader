#pragma once

#include "../includes.hpp"
#include "../utils/Hook.hpp"
#include "../scenes/PatchesBrowser.hpp"

struct MenuLayer_CB : public MenuLayer { 
    void onPatchesClicked(CCObject* sender);
};

DEFINE_HOOK(bool, MenuLayer, init);
GD_HOOK(0x1907B0, MenuLayer, init);