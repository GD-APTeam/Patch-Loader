#pragma once

#include "SubPatchCell.hpp"
#include "../../includes.hpp"

struct SubPatchRangeCell : public SubPatchCell {
    static SubPatchRangeCell* create(const char* name, const CCSize& size);
private:
    SubPatchRangeCell(const char* name, const CCSize& size);
    virtual bool init() override;
    void onSlider(CCObject* sender);
};