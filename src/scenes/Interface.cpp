#include "Interface.hpp"

Interface::Interface(const CCSize size, const std::string sprite): m_sprite(sprite), m_size(size) { }

bool Interface::init() {
    if (this->initWithColor({ 0, 0, 0, 75 })) {
        CCScale9Sprite* background = CCScale9Sprite::create(this->m_sprite.c_str(), { 0, 0, 80, 80 });
        CCDirector* director = CCDirector::sharedDirector();
        const CCSize& winSize = director->getWinSize();
        CCMenuItemSpriteExtra* close = CCMenuItemSpriteExtra::create(
            CCSprite::createWithSpriteFrameName("GJ_closeBtn_001.png"),
            this,
            menu_selector(Interface::onClose)
        );
        this->m_pLayer = CCLayer::create();
        this->m_pButtonMenu = CCMenu::create();

        director->getTouchDispatcher()->incrementForcePrio(2);
        background->setContentSize(this->m_size);
        background->setPosition({ winSize.width / 2, winSize.height / 2 });
        close->setSizeMult(1.5f);
        this->m_pButtonMenu->setPosition({ (winSize.width - this->m_size.width) / 2 + 10, (winSize.height + this->m_size.height) / 2 - 10 });
        this->m_pButtonMenu->setZOrder(10);

        this->m_pLayer->addChild(this->m_pButtonMenu);
        this->m_pLayer->addChild(background);
        this->m_pButtonMenu->addChild(close);
        this->addChild(this->m_pLayer);
        this->render(this->m_pLayer);
        this->setKeypadEnabled(true);
        this->setTouchEnabled(true);

        return true;
    } else {
        return false;
    }
}

void Interface::setTitle(const std::string& title, const std::string& font) {
    const CCSize& winSize = CCDirector::sharedDirector()->getWinSize();
    const int tag = TagGenerator::hashTag(Tag::INTERFACE_TITLE);
    CCNode* node = this->m_pLayer->getChildByTag(tag);
    CCLabelBMFont* titleNode = dynamic_cast<CCLabelBMFont*>(node);

    if (node) {
        if (titleNode) {
            titleNode->setFntFile(font.c_str());
            titleNode->setString(title.c_str());
        } else {
            node->removeFromParentAndCleanup(true);
            titleNode = CCLabelBMFont::create(title.c_str(), font.c_str());
        }
    } else {
        titleNode = CCLabelBMFont::create(title.c_str(), font.c_str());
    }

    titleNode->setPosition({ winSize.width / 2, winSize.height / 2 + this->m_size.height / 2 - 15 });
    titleNode->setScale(0.9f);
    titleNode->setTag(tag);
    this->m_pLayer->addChild(titleNode);
}

void Interface::onClose(CCObject* sender) {
    this->keyBackClicked();
}