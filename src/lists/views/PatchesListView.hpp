#pragma once

#include "../cells/PatchCell.hpp"
#include "../../includes.hpp"
#include "../../objects/PatchObject.hpp"

struct PatchCell;

struct PatchesListView : public CustomListView {
    static PatchesListView* create(CCArray* data, CCSize size);
protected:
    void setupList() override;
    TableViewCell* getListCell(const char* key) override;
    void loadCell(TableViewCell* cell, unsigned int index) override;
};