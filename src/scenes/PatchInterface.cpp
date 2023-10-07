#include "PatchInterface.hpp"

PatchInterface* PatchInterface::instance = nullptr;

void PatchInterface::scene(Patch* patch) {
    PatchInterface* interface = new PatchInterface();

    if (interface && interface->init(400, 280, patch)) {
        CCDirector* director = CCDirector::sharedDirector();
        CCScene* runningScene = director->getRunningScene();
        PatchInterface::instance = interface;

        interface->autorelease();
        interface->setZOrder(runningScene->getHighestChildZ() + 1);
        interface->stopAllActions();
        interface->setOpacity(0);
        interface->runAction(CCFadeTo::create(0.5f, 125));
        interface->m_mainLayer->stopAllActions();
        interface->m_mainLayer->setPosition({ 0, director->getWinSize().height });
        interface->m_mainLayer->runAction(CCEaseSineOut::create(CCMoveTo::create(0.5f, { 0, 0 })));
        runningScene->addChild(interface);
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

void PatchInterface::onClose(CCObject*) {
    PatchInterface::instance = nullptr;

    this->stopAllActions();
    this->runAction(CCFadeTo::create(0.5f, 0));
    this->m_mainLayer->stopAllActions();
    this->m_mainLayer->runAction(CCSequence::create(
        CCEaseSineOut::create(CCMoveTo::create(0.5f, { 0, CCDirector::sharedDirector()->getWinSize().height })),
        CCCallFunc::create(this, callfunc_selector(PatchInterface::finishedClosing)),
        nullptr
    ));
}

void PatchInterface::finishedClosing() {
    geode::Popup<Patch*>::onClose(nullptr);
}