#pragma once

#include "../includes.hpp"
#include "PatchBase.hpp"

struct Patch;
struct PatchBase;

struct PatchVector : public PatchBase {
    static bool isValid(json patch);

    std::vector<std::shared_ptr<PatchBase>> patches;

    PatchVector(json patches);
    void apply() override;
    void revert() override;
};