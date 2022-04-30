#include "PatchesListView.hpp"

PatchesListView* PatchesListView::create(CCArray* data, CCSize size) {
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
    unsigned int count = this->m_pEntries->count();

    this->m_fItemSeparation = 90.0f;

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

void PatchesListView::loadCell(TableViewCell* cell, unsigned int index) {
    PatchObject* patch = reinterpret_cast<PatchObject*>(this->m_pEntries->objectAtIndex(index));

    reinterpret_cast<PatchCell*>(cell)->setIndex(index);
    reinterpret_cast<PatchCell*>(cell)->loadFromMyData(patch);
    reinterpret_cast<PatchCell*>(cell)->updateBGColor();

}