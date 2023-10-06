#pragma once

#include "../../includes.hpp"
#include "../../objects/SubPatch.hpp"
#include "../cells/SubPatchBytesCell.hpp"

struct SubPatchesListView : public CustomListView {
    static SubPatchesListView* create(CCArray* data, const CCSize& size);
protected:
    virtual void setupList() override;
    virtual TableViewCell* getListCell(const char* key) override;
    virtual void loadCell(TableViewCell* cell, const int index) override;
private:
    size_t m_renderIndex;
};