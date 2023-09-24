#include "PatchInterface.hpp"

PatchInterface* PatchInterface::create(Patch* patch) {
    PatchInterface* interface = new PatchInterface();

    if (interface && interface->init(400, 280, patch)) {
        interface->autorelease();

        return interface;
    } else {
        CC_SAFE_DELETE(interface);

        return nullptr;
    }
}

bool PatchInterface::setup(Patch* patch) {
    this->m_patch = patch;
    this->setTitle(patch->m_name);

    return true;
}