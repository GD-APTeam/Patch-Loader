#pragma once

#include "../../includes.hpp"
#include "../../objects/Patch.hpp"
#include "../../scenes/PatchInterface.hpp" 
#include "../../objects/BetterTextArea.hpp" 

struct PatchCell : public TableViewCell, public FLAlertLayerProtocol {
    static PatchCell* create(const char* name, const CCSize& size);

    void init(const size_t index, Patch* patch);
protected:
    Patch* m_patch;

    PatchCell(const char* name, const CCSize& size);
    void onEnable(CCObject* sender);
    void onInterface(CCObject* sender);
    virtual void FLAlert_Clicked(FLAlertLayer* alert, const bool button2) override;
};