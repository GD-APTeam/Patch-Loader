#include "PatchesListView.hpp"

PatchesListView* PatchesListView::create(CCArray* data, const CCSize& size) {
    PatchesListView* view = new PatchesListView();

    if (view && view->init(data, BoomListType::Default, size.width, size.height)) {
        view->autorelease();
        
        return view;
    } else {
        CC_SAFE_DELETE(view);

        return nullptr;
    }
}

void PatchesListView::setupList() {
    const size_t count = this->m_entries->count();

    this->m_itemSeparation = 90;

    if (count) {
        this->m_tableView->reloadData();

        if (count == 1) {
            this->m_tableView->moveToTopWithOffset(this->m_itemSeparation);
        } else {
            this->m_tableView->moveToTop();
        }
    }
}

TableViewCell* PatchesListView::getListCell(const char* name) {
    return PatchCell::create(name, { this->m_width , this->m_itemSeparation });
}

void PatchesListView::loadCell(TableViewCell* cell, const int index) {
    reinterpret_cast<PatchCell*>(cell)->init(index, reinterpret_cast<Patch*>(this->m_entries->objectAtIndex(index)));
}