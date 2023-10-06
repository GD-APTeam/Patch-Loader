#include "PatchCell.hpp"

PatchCell* PatchCell::create(const char* name, const CCSize& size) {
    return new PatchCell(name, size);
}

PatchCell::PatchCell(const char* name, const CCSize& size) : TableViewCell(name, size.width, size.height) { }

void PatchCell::init(const size_t index, Patch* patch) {
    CCMenu* topRow = CCMenu::create();
    CCMenuItemSpriteExtra* interface = CCMenuItemSpriteExtra::create(
        CCSprite::createWithSpriteFrameName("GJ_infoIcon_001.png"),
        this,
        menu_selector(PatchCell::onInterface)
    );
    SimpleTextArea* description = SimpleTextArea::create(patch->m_description);
    CCLabelBMFont* nameNode = CCLabelBMFont::create(patch->m_name.c_str(), "goldFont.fnt");
    CCMenu* toggleMenu = CCMenu::create();
    CCMenuItemToggler* toggle = GameToolbox::createToggleButton("", menu_selector(PatchCell::onEnable), patch->m_enabled, toggleMenu, BOTTOM_LEFT, this, nullptr, 1, 1, 160, BOTTOM_LEFT, "", false, 0, nullptr);
    const CCSize& nameSize = nameNode->getContentSize();
    const CCSize& interfaceSize = interface->getContentSize();
    const CCSize& toggleSize = toggle->getContentSize();
    this->m_patch = patch;

    if (index & 1) {
        this->m_backgroundLayer->setColor(LIGHT_CELL);
    } else {
        this->m_backgroundLayer->setColor(DARK_CELL);
    }

    nameNode->setPosition(BOTTOM_LEFT);
    nameNode->setAnchorPoint(BOTTOM_LEFT);
    interface->setPosition({ nameSize.width + interfaceSize.width / 2 + 5, interface->getContentSize().height / 2 });
    topRow->setScale(0.7f);
    topRow->setAnchorPoint(TOP_LEFT);
    topRow->setPosition({ 15, this->m_height - 8 });
    topRow->setContentSize({ this->m_width - 80, nameSize.height });
    topRow->setLayout(RowLayout::create());
    topRow->addChild(nameNode);
    topRow->addChild(interface);
    description->setMaxLines(2);
    description->setWidth(this->m_width - 80);
    description->setPosition({ 15, this->m_height - nameSize.height - 5 });
    description->setAnchorPoint(TOP_LEFT);
    toggle->setPosition(toggleSize / 2);
    toggleMenu->setPosition(CCSize({ this->m_width - toggleSize.width / 2 - 5, this->m_height / 2 }) - toggleSize / 2);
    toggleMenu->setContentSize(toggleSize);
    this->m_mainLayer->setContentSize({ this->m_width, this->m_height });

    this->m_backgroundLayer->setOpacity(0xFF);
    this->m_mainLayer->addChild(topRow);
    this->m_mainLayer->addChild(description);
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
        geode::createQuickPopup(
            "Reload required",
            "To apply <cy>" + this->m_patch->m_name + "</c> You need to reload the game. Would you like to reload the game now?",
            "Later",
            "Reload",
            340,
            [](FLAlertLayer*, const bool button2) {
                if (button2) {
                    CCApplication::sharedApplication()->applicationDidFinishLaunching();
                }
            }
        );
    }
}

void PatchCell::onInterface(CCObject*) {
    PatchInterface::scene(this->m_patch);
}