#include <Geode/modify/MenuLayer.hpp>

#include "../includes.hpp"
#include "../scenes/PatchesBrowser.hpp"

class $modify(MenuLayerExtra, MenuLayer) {

    bool init() {
        if (MenuLayer::init()) {
            CCMenu* menu = CCMenu::create();
            CCDirector* director = CCDirector::sharedDirector();
            CCSprite* sprite = CCSprite::createWithSpriteFrameName("GJ_starBtn_001.png");

            sprite->setScale(0.7f);
            menu->addChild(CCMenuItemSpriteExtra::create(sprite, this, menu_selector(MenuLayerExtra::onPatchesClicked)));
            menu->setPosition({ director->getScreenRight() - 18, director->getScreenTop() - 18 });
            this->addChild(menu);

            return true;
        } else {
            return false;
        }
    }

    void onPatchesClicked(CCObject*) {
        PatchesBrowser* browser = PatchesBrowser::create();

        CCDirector::sharedDirector()->getRunningScene()->addChild(browser);
        browser->showLayer(false);
    }
};