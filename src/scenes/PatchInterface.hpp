#pragma once

#include "../includes.hpp"
#include "../objects/Patch.hpp"
#include "../utils/converters.hpp"
#include "../nodes/SimpleTextContainer.hpp"
#include "../nodes/views/SubPatchesListView.hpp"

struct PatchInterface : public geode::Popup<Patch*> {
    static PatchInterface* instance;

    static void scene(Patch* patch);

    virtual void onClose(CCObject* sender) override;
protected:
    virtual bool setup(Patch* patch) override;
private:
    Patch* m_patch;

    void finishedClosing();
};