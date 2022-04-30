#pragma once

#include "../includes.hpp"
#include "PatchBase.hpp"

struct PatchVector;
struct PatchBase;

struct Patch : public PatchBase {
    static bool isValid(json patch);

    LPVOID address;
    std::vector<std::byte> bytes;
    std::vector<std::byte> original;
    bool cocos;

    Patch(json patch);
    void apply() override;
    void revert() override;
};