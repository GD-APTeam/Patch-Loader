#include "PatchesBrowser.hpp"

bool PatchesBrowser::isOpen = false;

void PatchesBrowser::scene() {
    if (!PatchesBrowser::isOpen) {
        PatchesBrowser* browser = new PatchesBrowser();

        if (browser && browser->init("Installed patches", 220)) {
            PlayLayer* playLayer = GameManager::sharedState()->getPlayLayer();
            PatchesBrowser::isOpen = true;

            browser->autorelease();
            browser->showLayer(false);

            if (playLayer) {
                playLayer->pauseGame(false);
                browser->setZOrder(1000);
            }

            CCDirector::sharedDirector()->getRunningScene()->addChild(browser);
        } else {
            CC_SAFE_DELETE(browser);
        }
    }
}

void PatchesBrowser::customSetup() {
    CCArray* patches = CCArray::create();

    for (Patch& patch : PatchStorage::sharedState()->m_patches) {
        patches->addObject(&patch);
    }

    this->m_listLayer->addChild(PatchesListView::create(patches, { 356, 220 }));
}

void PatchesBrowser::exitLayer(CCObject* sender) {
    PatchesBrowser::isOpen = false;

    GJDropDownLayer::exitLayer(sender);
}