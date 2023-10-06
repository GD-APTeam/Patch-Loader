#pragma once

#include "SubPatchCell.hpp"
#include "../../includes.hpp"
#include "../SimpleTextArea.hpp" 
#include "../../objects/SubPatch.hpp"
#include "../../scenes/PatchInterface.hpp" 

struct SubPatchBytesCell : public SubPatchCell {
    static SubPatchBytesCell* create(const char* name, const CCSize& size);
private:
    SubPatchBytesCell(const char* name, const CCSize& size);
    virtual bool init() override;
};