#pragma once

#include "../../includes.hpp"
#include "../SimpleTextArea.hpp" 
#include "../../objects/Patch.hpp"
#include "../../scenes/PatchInterface.hpp" 

struct PatchCell : public StatsCell {
    static PatchCell* create(const char* name, const CCSize& size);

    bool init(const size_t index, Patch* patch);
protected:
    Patch* m_patch;

    PatchCell(const char* name, const CCSize& size);
    void onEnable(CCObject* sender);
    void onInterface(CCObject*);
};