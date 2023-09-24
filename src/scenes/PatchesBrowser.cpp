#include "PatchesBrowser.hpp"

void PatchesBrowser::popup() {
    PatchesBrowser* browser = new PatchesBrowser();

    if (browser && browser->init()) {
        browser->autorelease();
        browser->showLayer(false);

        CCDirector::sharedDirector()->getRunningScene()->addChild(browser);
    } else {
        CC_SAFE_DELETE(browser);
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

    this->m_listLayer->addChild(PatchesListView::create(patches, { 356, 220 }));
}