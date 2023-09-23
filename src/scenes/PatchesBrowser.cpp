#include "PatchesBrowser.hpp"

PatchesBrowser* PatchesBrowser::create() {
    PatchesBrowser* browser = new PatchesBrowser();

    if (browser && browser->init()) {
        browser->autorelease();

        return browser;
    } else {
        CC_SAFE_DELETE(browser);

        return nullptr;
    }
}

bool PatchesBrowser::init() {
    return GJDropDownLayer::init("Installed patches", 220);
}

void PatchesBrowser::customSetup() {
    CCArray* patches = CCArray::create();

    for (Patch& patch : PatchStorage::sharedState()->m_patches) {
        patches->addObject(&patch);
    }

    this->m_pListLayer->addChild(PatchesListView::create(patches, { 356, 220 }));
}