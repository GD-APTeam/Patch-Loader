#pragma once

#include "../includes.hpp"

struct PatchObject : CCObject {
    static PatchObject* create(std::shared_ptr<PatchBase> patch);
    
    std::string getName();
    std::string getDescription();
    bool isDisabled();
protected:
    std::shared_ptr<PatchBase> patch;

    PatchObject(std::shared_ptr<PatchBase> patch);
};