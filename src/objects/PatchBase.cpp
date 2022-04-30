#include "PatchBase.hpp"
#include "PatchVector.hpp"

std::vector<std::shared_ptr<PatchBase>> PatchBase::create(json patches) {
    // Incredibly hacky but I can't be bothered to do it properly.
    json placeholder;

    if (patches.is_array()) {
        placeholder["name"] = "";
        placeholder["patches"] = patches;

        return PatchVector(placeholder).patches;
    } else {
        return {};
    }
}

bool PatchBase::isValid(json patch) {
    return patch.is_object() &&
        patch["name"].is_string() &&
        (patch["description"].is_null() || patch["description"].is_string()) &&
        (patch["disabled"].is_null() || patch["disabled"].is_boolean()) &&
        (patch["restart"].is_null() || patch["restart"].is_boolean());
}