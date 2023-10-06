#include "PatchesBrowser.hpp"

PatchesBrowser* PatchesBrowser::instance = nullptr;

void PatchesBrowser::scene() {
    if (PatchesBrowser::instance) {
        PatchesBrowser::instance->exitLayer(nullptr);

        if (PatchInterface::instance) {
            PatchInterface::instance->onClose(nullptr);
        }
    } else {
        PatchesBrowser* browser = new PatchesBrowser();

        if (browser && browser->init("Installed patches", 220)) {
            PlayLayer* playLayer = GameManager::sharedState()->getPlayLayer();
            PatchesBrowser::instance = browser;

            browser->autorelease();
            browser->showLayer(false);

            if (playLayer) {
                playLayer->pauseGame(false);
                browser->setZOrder(INT32_MAX);
            }

            CCDirector::sharedDirector()->getRunningScene()->addChild(browser);
        } else {
            CC_SAFE_DELETE(browser);
        }
    }
}

void PatchesBrowser::customSetup() {
    this->m_listLayer->addChild(PatchesListView::create(converters::toCCArray(PatchStorage::sharedState()->m_patches), { 356, 220 }));
}

void PatchesBrowser::exitLayer(CCObject* sender) {
    PatchesBrowser::instance = nullptr;

    GJDropDownLayer::exitLayer(sender);
}