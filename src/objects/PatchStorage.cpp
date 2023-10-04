#include "PatchStorage.hpp"

std::string PatchStorage::m_fileName = "patches.json";
size_t PatchStorage::m_indent = 2;

PatchStorage* PatchStorage::sharedState() {
    static PatchStorage* sharedState = new PatchStorage();

    return sharedState;
}

PatchStorage::PatchStorage() {
    std::ifstream file(PatchStorage::m_fileName, std::ifstream::binary);

    if (file.good()) {
        JSON patches;

        file >> patches;

        if (patches.is_array()) {
            for (const JSON& patch : patches) {
                Patch patchObject = Patch::get(patch);

                if (patchObject.m_isValid) {
                    this->m_patches.push_back(patchObject);
                }
            }
        }
    }
}

size_t PatchStorage::size() {
    return this->m_patches.size();
}

Patch& PatchStorage::get(const size_t index) {
    return this->m_patches[index];
}

void PatchStorage::addPatch(Patch patch) {
    this->m_patches.push_back(patch);
}

void PatchStorage::removePatch(const size_t index) {
    if (index < this->m_patches.size()) {
        this->m_patches.erase(this->m_patches.begin() + index);
    }
}

void PatchStorage::replacePatch(const size_t index, Patch patch) {
    if (index < this->m_patches.size()) {
        this->m_patches[index] = patch;
    }
}

void PatchStorage::save() {
    std::ofstream file(PatchStorage::m_fileName);
    JSON storage = JSON::array();

    for (Patch& patch : this->m_patches) {
        storage.push_back(patch);
    }

    file << storage.dump(PatchStorage::m_indent);
    file.close();
}