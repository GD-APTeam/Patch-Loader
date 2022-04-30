#include "PatchesBrowser.hpp"
#include "../lists/views/PatchesListView.hpp"
#include "../objects/PatchObject.hpp"

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
    return GJDropDownLayer::init("Installed patches", 220.0f);
}

void PatchesBrowser::customSetup() {
    CCArray* ccPatches = CCArray::create();

    for (std::shared_ptr<PatchBase> patch : gd::patches) {
        ccPatches->addObject(PatchObject::create(patch));
    }

    PatchesListView* view = PatchesListView::create(ccPatches, { 356.0f, 220.0f });
    this->m_pListLayer->addChild(view);
}