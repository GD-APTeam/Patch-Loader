#pragma once

#include "../includes.hpp"

struct MenuLayer_CB : public MenuLayer { 
    void onPatchesClicked(CCObject* sender);
};

inline bool (__thiscall* MenuLayer_init)(CCLayer* self);
bool __fastcall MenuLayer_init_H(CCLayer* self, void*);