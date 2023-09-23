#include "PatchInterface.hpp"

PatchInterface* PatchInterface::create(Patch* patch) {
    PatchInterface* interface = new PatchInterface(patch);

    if (interface && interface->init()) {
        interface->autorelease();

        return interface;
    } else {
        CC_SAFE_DELETE(interface);

        return nullptr;
    }
}

PatchInterface::PatchInterface(Patch* patch): Interface({ 400, 280 }) {
    this->m_patch = patch;
}

void PatchInterface::render(CCLayer* layer) {
    Interface::setTitle(this->m_patch->m_name);    
}