#include "PatchesListView.hpp"

PatchesListView* PatchesListView::create(CCArray* data, const CCSize& size) {
    PatchesListView* view = new PatchesListView();

    if (view && view->init(data, BoomListType::kBoomListTypeDefault, size.width, size.height)) {
        view->autorelease();
        
        return view;
    } else {
        CC_SAFE_DELETE(view);

        return nullptr;
    }
}

void PatchesListView::setupList() {
    const size_t count = this->m_pEntries->count();

    this->m_fItemSeparation = 90;

    if (count) {
        this->m_pTableView->reloadData();

        if (count == 1) {
            this->m_pTableView->moveToTopWithOffset(this->m_fItemSeparation);
        } else {
            this->m_pTableView->moveToTop();
        }
    }
}

TableViewCell* PatchesListView::getListCell(const char* name) {
    return PatchCell::create(name, { this->m_fWidth , this->m_fItemSeparation });
}

void PatchesListView::loadCell(TableViewCell* cell, const size_t index) {
    reinterpret_cast<PatchCell*>(cell)->init(index, reinterpret_cast<Patch*>(this->m_pEntries->objectAtIndex(index)));
}