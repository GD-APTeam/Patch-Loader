#pragma once

#include "../../includes.hpp"
#include "../cells/PatchCell.hpp"
#include "../../objects/Patch.hpp"

struct PatchesListView : public CustomListView {
    static PatchesListView* create(CCArray* data, const CCSize& size);
protected:
    virtual void setupList() override;
    virtual TableViewCell* getListCell(const char* key) override;
    virtual void loadCell(TableViewCell* cell, const size_t index) override;
private:
    size_t m_renderIndex;
};