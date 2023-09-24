#pragma once

#include "../includes.hpp"
#include "../objects/Patch.hpp"

struct PatchInterface : public geode::Popup<Patch*> {
    static PatchInterface* create(Patch* patch);
protected:
    virtual bool setup(Patch* patch) override;
private:
    Patch* m_patch;
};