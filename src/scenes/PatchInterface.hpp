#pragma once

#include "../includes.hpp"
#include "../objects/Patch.hpp"
#include "../nodes/SimpleTextArea.hpp"

struct PatchInterface : public geode::Popup<Patch*> {
    static PatchInterface* instance;

    static void scene(Patch* patch);

    virtual void onClose(CCObject* sender) override;
protected:
    virtual bool setup(Patch* patch) override;
private:
    Patch* m_patch;
};