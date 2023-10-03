#pragma once

#include "../../includes.hpp"
#include "../BetterTextArea.hpp" 
#include "../../objects/Patch.hpp"
#include "../../scenes/PatchInterface.hpp" 

struct PatchCell : public TableViewCell {
    static PatchCell* create(const char* name, const CCSize& size);

    void init(const size_t index, Patch* patch);
protected:
    Patch* m_patch;

    PatchCell(const char* name, const CCSize& size);
    void onEnable(CCObject* sender);
    void onInterface(CCObject*);
};