#include "PatchObject.hpp"

PatchObject* PatchObject::create(Patch patch) {
    PatchObject* object = new PatchObject(patch);

    if (object) {
        object->autorelease();

        return object;
    } else {
        CC_SAFE_DELETE(object);

        return nullptr;
    }
}

std::string PatchObject::getName() {
    return this->patch.name;
}

std::string PatchObject::getDescription() {
    return this->patch.description;
}

bool PatchObject::isDisabled() {
    return this->patch.disabled;
}

PatchObject::PatchObject(Patch patch): patch(patch) { }