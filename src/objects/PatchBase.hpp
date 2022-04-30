#pragma once

#include "../includes.hpp"

struct Patch;
struct PatchVector;

struct PatchBase {
    static std::vector<std::shared_ptr<PatchBase>> create(json patches);
    static bool isValid(json patch);

    std::string name;
    std::string description;
    bool restart;
    bool disabled;

    virtual void apply() = 0;
    virtual void revert() = 0;
};