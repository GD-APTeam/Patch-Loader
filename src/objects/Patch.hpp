#pragma once

#include "../includes.hpp"
#include "PatchBase.hpp"

struct PatchVector;
struct PatchBase;

struct Patch : public PatchBase {
    static bool isValid(json patch);
    
    std::vector<std::byte> bytes;

    Patch(json patch);
    void apply() override;
    void revert() override;
protected:
    LPVOID address;
    std::vector<std::byte> original;
    bool cocos;
};