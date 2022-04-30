#pragma once

#include "../views/PatchesListView.hpp"
#include "../../includes.hpp"
#include "../../objects/PatchObject.hpp"

struct PatchesListView;

struct PatchCell : public TableViewCell {
    static PatchCell* create(const char* name, CCSize size);

    void updateBGColor();
    void setIndex(unsigned int index);
    void loadFromMyData(PatchObject* object);
protected:
    unsigned int index;

    PatchCell(const char* name, CCSize size);
    void onClick(CCObject* sender);
};