#pragma once

#include "../includes.hpp"

struct PatchObject : CCObject {
    static PatchObject* create(Patch patch);
    
    std::string getName();
    std::string getDescription();
    bool isDisabled();
protected:
    Patch patch;

    PatchObject(Patch patch);
};