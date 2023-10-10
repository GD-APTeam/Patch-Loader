#include "Patch.hpp"

Patch Patch::get(const JSON& object) {
    const JSON& patches = object["patches"];
    Patch patch(true);

    if (patches.is_array() && patches.size() && object["name"].is_string()) {
        const std::string name = object["name"].get<std::string>();
        const std::string description = object.value("description", "No description was provided.");

        if (name.size() <= 30 && description.size() <= 85) {
            for (const JSON& subPatch : patches) {
                const SubPatch subPatchObject = SubPatch::get(subPatch);

                if (subPatchObject.m_isValid) {
                    patch.m_patches.push_back(subPatchObject);
                } else {
                    return Patch(false);
                }
            }

            patch.m_name = name;
            patch.m_description = description;
            patch.m_restart = object.value("restart", false);
            patch.m_enabled = object.value("enabled", false);

            return patch;
        }
    }

    return Patch(false);
}

Patch::operator JSON() {
    return {
        { "name", this->m_name },
        { "description", this->m_description },
        { "restart", this->m_restart },
        { "enabled", this->m_enabled },
        { "patches", std::vector<JSON>(this->m_patches.begin(), this->m_patches.end()) }
    };
}

Patch::Patch(const bool valid) : BasePatch(valid) {
    this->retain();
}

void Patch::apply() {
    if (!this->m_enabled) {
        for (SubPatch& patch : this->m_patches) {
            patch.apply();
        }

        this->m_enabled = true;
    }
}

void Patch::revert() {
    if (this->m_enabled) {
        for (SubPatch& patch : this->m_patches) {
            patch.revert();
        }

        this->m_enabled = false;
    }
}