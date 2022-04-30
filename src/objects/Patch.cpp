#include "Patch.hpp"

bool Patch::isValid(json patch) {
    return patch.is_object() &&
        patch["name"].is_string() &&
        patch["address"].is_number_unsigned() &&
        patch["bytes"].is_array() &&
        patch["bytes"][0].is_number_unsigned() &&
        patch["bytes"][0] < 0x100 &&
        (patch["description"].is_null() || patch["description"].is_string()) &&
        (patch["cocos"].is_null() || patch["cocos"].is_boolean()) &&
        (patch["disabled"].is_null() || patch["disabled"].is_boolean());
}

Patch::Patch(json patch) {
    this->name = patch["name"].get<std::string>();
    this->description = patch.value<std::string>("description", "No description was provided.");
    this->bytes = patch["bytes"].get<std::vector<std::byte>>();
    this->cocos = patch.value<bool>("cocos", false);
    this->disabled = patch.value<bool>("disabled", false);
    this->original = std::vector<std::byte>(this->bytes.size());
    unsigned int address = patch["address"].get<uint32_t>();

    if (this->cocos) {
        this->address = reinterpret_cast<LPVOID>(gd::cocosBase + address);
    } else {
        this->address = reinterpret_cast<LPVOID>(gd::base + address);
    }

    ReadProcessMemory(
        GetCurrentProcess(),
        this->address,
        this->original.data(),
        this->original.size(),
        nullptr
    );
}

void Patch::apply() {
    WriteProcessMemory(
        GetCurrentProcess(),
        this->address,
        this->bytes.data(),
        this->bytes.size(),
        nullptr
    );
}

void Patch::revert() {
    WriteProcessMemory(
        GetCurrentProcess(),
        this->address,
        this->original.data(),
        this->original.size(),
        nullptr
    );
}