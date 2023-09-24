#include "PatchCell.hpp"

PatchCell* PatchCell::create(const char* name, const CCSize& size) {
    return new PatchCell(name, size);
}

PatchCell::PatchCell(const char* name, const CCSize& size) : TableViewCell(name, size.width, size.height) { }

void PatchCell::init(const size_t index, Patch* patch) {
    CCMenu* interfaceMenu = CCMenu::create();
    CCMenuItemSpriteExtra* interface = CCMenuItemSpriteExtra::create(
        CCSprite::createWithSpriteFrameName("GJ_infoIcon_001.png"),
        this,
        menu_selector(PatchCell::onInterface)
    );
    BetterTextArea<false>* description = BetterTextArea<false>::create("chatFont.fnt", patch->m_description, 1, this->m_width - 80);
    CCLabelBMFont* name = CCLabelBMFont::create(patch->m_name.c_str(), "goldFont.fnt");
    CCMenu* toggleMenu = CCMenu::create();
    this->m_patch = patch;

    if (index & 1) {
        this->m_backgroundLayer->setColor(ccc3(0xC2, 0x72, 0x3E));
    } else {
        this->m_backgroundLayer->setColor(ccc3(0xA1, 0x58, 0x2C));
    }

    GameToolbox::createToggleButton("", menu_selector(PatchCell::onEnable), patch->m_enabled, toggleMenu, {
        this->m_width - 30,
        this->m_height - 48
    }, this, this->m_mainLayer, 1, 1, 160, { 0, 0 }, "", false, 0, nullptr);

    // GameToolbox::createToggleButton(menu_selector(PatchCell::onEnable), patch->m_enabled, toggleMenu, this, this->m_mainLayer, 1, 1, 160, "", false, 0, nullptr, "", {
    //     this->m_width - 30,
    //     this->m_height - 48
    // }, { 0, 0 });

    name->setScale(0.7f);
    name->setAnchorPoint({ 0, 1 });
    name->setPosition({ 15, this->m_height - 10 });
    interface->setSizeMult(1.5f);
    interfaceMenu->setScale(0.7f);
    interfaceMenu->setAnchorPoint({ 0, 0 });
    interfaceMenu->setPosition({ 27 + name->getContentSize().width * 0.7f, this->m_height - 21 });
    description->setMaxLines(2);
    description->setPosition({ 15, name->getPositionY() - name->getContentSize().height + 5 });
    interfaceMenu->addChild(interface);

    this->m_backgroundLayer->setOpacity(0xFF);
    this->m_mainLayer->addChild(name);
    this->m_mainLayer->addChild(description);
    this->m_mainLayer->addChild(interfaceMenu);
    this->m_mainLayer->addChild(toggleMenu);
    this->m_mainLayer->setVisible(true);

    // Slider* slider = Slider::create(this->m_pLayer, menu_selector(PatchCell::onSlider), 1.0f);
    // slider->setBarVisibility(true);
    // Why is the anchor for sliders hardcoded and the size set to about 1000???
    // slider->setPosition({ 15.0f + slider->m_fUnknown / 2, 20.0f });
    // slider->setValue(0);
    // slider->updateBar();
    // this->m_pLayer->addChild(slider);
}

void PatchCell::onEnable(CCObject* sender) {
    if (reinterpret_cast<CCMenuItemToggler*>(sender)->isToggled()) {
        this->m_patch->revert();
    } else {
        this->m_patch->apply();
    }

    if (this->m_patch->m_restart) {
        FLAlertLayer::create(
            this,
            "Reload required",
            "To apply <cy>" + this->m_patch->m_name + "</c> You need to reload the game. " "Would you like to reload the game now?",
            "Later",
            "Reload",
            340
        )->show();
        // FLAlertLayer::create(
        //     this,
        //     "Reload required",
        //     "Later",
        //     "Reload",
        //     340,
        //     "To apply <cy>" + this->m_patch->m_name + "</c> You need to reload the game. "
        //     "Would you like to reload the game now?"
        // )->show();
    }
}

void PatchCell::onInterface(CCObject* sender) {
    PatchInterface::create(this->m_patch)->show();
}

void PatchCell::FLAlert_Clicked(FLAlertLayer* alert, const bool button2) {
    if (button2) {
        CCApplication::sharedApplication()->applicationDidFinishLaunching();
    }
}