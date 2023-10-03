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
    const CCSize& winSize = CCDirector::sharedDirector()->getWinSize();
    const CCSize& size = this->m_bgSprite->getContentSize();
    SimpleTextArea* description = SimpleTextArea::create("chatFont.fnt", patch->m_description, 1, size.width - 60);
    CCScale9Sprite* descriptionBg = CCScale9Sprite::create("square02b_001.png", CCRect(0, 0, 80, 80));

    this->m_patch = patch;
    this->setTitle(patch->m_name);

    descriptionBg->setAnchorPoint({ 0.5, 1 });
    descriptionBg->setContentSize({ size.width - 40, description->getContentSize().height + 20 });
    descriptionBg->setColor({ 0x82, 0x40, 0x21 });
    descriptionBg->setPosition({ winSize.width / 2, this->m_title->getPositionY() - this->m_title->getContentSize().height / 2 - 5 });
    description->setMaxLines(2);
    description->setAlignment(kCCTextAlignmentCenter);
    description->setAnchorPoint({ 0, 0 });
    description->setPosition({ 10, 10 });

    descriptionBg->addChild(description);
    this->m_mainLayer->addChild(descriptionBg);

    return true;
}

void PatchInterface::onClose(CCObject* sender) {
    PatchInterface::instance = nullptr;

    geode::Popup<Patch*>::onClose(sender);
}