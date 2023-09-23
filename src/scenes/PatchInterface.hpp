#pragma once

#include "Interface.hpp"
#include "../includes.hpp"
#include "../objects/Patch.hpp"

struct PatchInterface : public Interface {
    static PatchInterface* create(Patch* patch);
protected:
    virtual void render(CCLayer* layer) override;
private:
    Patch* m_patch;

    PatchInterface(Patch* patch);
};