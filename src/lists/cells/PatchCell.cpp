#include "PatchCell.hpp"

PatchCell* PatchCell::create(const char* name, CCSize size) {
    PatchCell* cell = new PatchCell(name, size);

    if (cell) {
        return cell;
    } else {
        CC_SAFE_DELETE(cell);

        return nullptr;
    }
}

void PatchCell::updateBGColor() {
    if (this->index & 1) {
        this->m_pBGLayer->setColor(ccc3(0xC2, 0x72, 0x3E));
    } else {
        this->m_pBGLayer->setColor(ccc3(0xA1, 0x58, 0x2C));
    }

    this->m_pBGLayer->setOpacity(0xFF);
}

void PatchCell::loadFromMyData(PatchObject* patch) {
    CCMenu* menu = CCMenu::create();
    CCLabelBMFont* name = CCLabelBMFont::create(patch->getName().c_str(), "goldFont.fnt");

    name->setScale(0.7f);

    TextArea* description = TextArea::create(
        "chatFont.fnt", 
        false, 
        patch->getDescription(),
        1.0f,
        this->m_fWidth - 80.0f,
        20.0f,
        { 0.0f, 1.0f }
    );
    GameToolbox::createToggleButton(
        menu_selector(PatchCell::onClick), !patch->isDisabled(), 
        menu, this, this->m_pLayer, 1.0f, 1.0f, 
        160.0f, "", false, 0, nullptr, "", 
        { this->m_fWidth - 30.0f, this->m_fHeight / 2.0f }, { 0.0f, 0.0f }
    );

    name->setAnchorPoint({ 0.0f, 1.0f });
    name->setPosition(15.0f, this->m_fHeight - 12.0f);
    description->setAnchorPoint({ 0.0f, 1.0f });
    description->setPosition({ 15.0f, name->getContentSize().height + 25.0f });

    this->m_pBGLayer->setOpacity(0xFF);
    this->m_pLayer->addChild(name);
    this->m_pLayer->addChild(description);
    this->m_pLayer->addChild(menu);
    this->m_pLayer->setVisible(true);
}

PatchCell::PatchCell(const char* name, CCSize size) : TableViewCell(name, size.width, size.height) { }

void PatchCell::setIndex(unsigned int index) {
    this->index = index;
}

void PatchCell::onClick(CCObject* object) {
    if (gd::patches[this->index].disabled = reinterpret_cast<CCMenuItemToggler*>(object)->isToggled()) {
        gd::patches[this->index].revert();
    } else {
        gd::patches[this->index].apply();
    }
}