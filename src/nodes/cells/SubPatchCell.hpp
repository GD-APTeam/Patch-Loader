#pragma once

#include "../../includes.hpp"
#include "../../objects/SubPatch.hpp"

struct SubPatchCell : public StatsCell {
    bool initWithPatch(const size_t index, SubPatch* patch);
protected:
    SubPatch* m_patch;
    CCLabelBMFont* m_label;
    CCMenu* m_content;

    SubPatchCell(const char* name, const CCSize& size);
    virtual bool init() = 0;
};