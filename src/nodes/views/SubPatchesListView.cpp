#include "SubPatchesListView.hpp"

SubPatchesListView* SubPatchesListView::create(CCArray* data, const CCSize& size) {
    SubPatchesListView* view = new SubPatchesListView();

    if (view && view->init(data, BoomListType::Default, size.width, size.height)) {
        return view;
    } else {
        CC_SAFE_DELETE(view);

        return nullptr;
    }
}

void SubPatchesListView::setupList() {
    const size_t count = this->m_entries->count();

    this->m_itemSeparation = 55;

    if (count) {
        this->m_tableView->reloadData();

        if (count == 1) {
            this->m_tableView->moveToTopWithOffset(this->m_itemSeparation);
        } else {
            this->m_tableView->moveToTop();
        }
    }
}

TableViewCell* SubPatchesListView::getListCell(const char* key) {
    switch (reinterpret_cast<SubPatch*>(this->m_entries->objectAtIndex(this->m_renderIndex++))->m_type) {
        case PatchType::BYTES: {
            return SubPatchBytesCell::create(key, { this->m_width , this->m_itemSeparation });
        }
        case PatchType::RANGE: {
            return nullptr;
        }
        case PatchType::CHECKBOX: {
            return nullptr;
        }
        case PatchType::COLOR: {
            return nullptr;
        }
        default: {
            return nullptr;
        }
    }
}

void SubPatchesListView::loadCell(TableViewCell* cell, const int index) {
    if (reinterpret_cast<SubPatchBytesCell*>(cell)->initWithPatch(index, reinterpret_cast<SubPatch*>(this->m_entries->objectAtIndex(index)))) {
        cell->autorelease();
    } else {
        cell->release();
    }
}