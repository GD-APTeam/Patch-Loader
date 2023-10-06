#include "PatchInterface.hpp"

PatchInterface* PatchInterface::instance = nullptr;

void PatchInterface::scene(Patch* patch) {
    PatchInterface* interface = new PatchInterface();

    if (interface && interface->init(400, 280, patch)) {
        PatchInterface::instance = interface;

        interface->autorelease();
        interface->show();
    } else {
        CC_SAFE_DELETE(interface);
    }
}

bool PatchInterface::setup(Patch* patch) {
    this->m_patch = patch;
    const CCSize& winSize = CCDirector::sharedDirector()->getWinSize();
    const CCSize& size = this->m_bgSprite->getContentSize();
    SimpleTextContainer* description = SimpleTextContainer::create({ size.width - 40, 55 }, patch->m_description);
    GJCommentListLayer* subPatchesContainer = GJCommentListLayer::create(SubPatchesListView::create(converters::toCCArray(patch->m_patches), {
        size.width - 60,
        160
    }), "patches", LIST_AREA_4B, size.width - 60, 160, false);

    this->setTitle(patch->m_name);

    description->setAnchorPoint(TOP_CENTER);
    description->setPosition({ winSize.width / 2, this->m_title->getPositionY() - this->m_title->getContentSize().height / 2 - 5 });
    description->m_textArea->setAlignment(kCCTextAlignmentCenter);
    subPatchesContainer->setAnchorPoint(BOTTOM_LEFT);
    subPatchesContainer->setPosition({ winSize.width / 2 - subPatchesContainer->getContentSize().width / 2, 35 });

    this->m_mainLayer->addChild(subPatchesContainer);
    this->m_mainLayer->addChild(description);

    return true;
}

void PatchInterface::onClose(CCObject* sender) {
    PatchInterface::instance = nullptr;

    geode::Popup<Patch*>::onClose(sender);
}