#include "PatchVector.hpp"
#include "Patch.hpp"

bool PatchVector::isValid(json patches) {
    return PatchBase::isValid(patches) &&
        patches["patches"].is_array() &&
        patches["patches"].size();
}

PatchVector::PatchVector(json patches) {
    this->name = patches["name"].get<std::string>();
    this->description = patches.value<std::string>("description", "No description was provided.");
    this->restart = patches.value<bool>("restart", false);
    this->disabled = patches.value<bool>("disabled", false);
    this->patches = {};

    for (json patch : patches["patches"]) {
        if (PatchVector::isValid(patch)) {
            std::shared_ptr<PatchVector> patchVector = std::shared_ptr<PatchVector>(new PatchVector(patch));

            if (patchVector->patches.size()) {
                this->patches.push_back(patchVector);
            }
        } else if (Patch::isValid(patch)) {
            std::shared_ptr<Patch> patchObject = std::shared_ptr<Patch>(new Patch(patch));

            if (patchObject->bytes.size()) {
                this->patches.push_back(patchObject);
            }
        }
    }
}

void PatchVector::apply() {
    if (!this->disabled) {
        for (std::shared_ptr<PatchBase> patch : this->patches) {
            patch->apply();
        }
    }
}

void PatchVector::revert() {
    for (std::shared_ptr<PatchBase> patch : this->patches) {
        patch->revert();
    }
}