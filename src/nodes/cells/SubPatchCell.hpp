#pragma once

#include "../../includes.hpp"
#include "../../objects/SubPatch.hpp"

struct SubPatchCell : public TableViewCell {
    void initWithIndex(const size_t index, SubPatch* patch);
protected:
    SubPatch* patch;

    SubPatchCell(const char* name, const CCSize& size);
    virtual bool init() = 0;
};