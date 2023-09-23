#include "MenuLayer.hpp"

IMPLEMENT_HOOK(bool, MenuLayer, init) {
    const bool initResult = MenuLayer_init(self);
    
    if (initResult) {
        CCMenu* menu = CCMenu::create();
        CCDirector* director = CCDirector::sharedDirector();
        CCSprite* sprite = CCSprite::createWithSpriteFrameName("GJ_starBtn_001.png");

        sprite->setScale(0.7f);
        menu->addChild(CCMenuItemSpriteExtra::create(sprite, self, menu_selector(MenuLayer_CB::onPatchesClicked)));
        menu->setPosition({ director->getScreenRight() - 18, director->getScreenTop() - 18 });
        self->addChild(menu);

        return true;
    } else {
        return initResult;
    }

}

void MenuLayer_CB::onPatchesClicked(CCObject* sender) {
    PatchesBrowser* browser = PatchesBrowser::create();

    CCDirector::sharedDirector()->getRunningScene()->addChild(browser);
    browser->showLayer(false);
}