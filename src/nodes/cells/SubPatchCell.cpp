#include "SubPatchCell.hpp"

SubPatchCell::SubPatchCell(const char* name, const CCSize& size) : TableViewCell(name, size.width, size.height) { }

void SubPatchCell::initWithIndex(const size_t index, SubPatch* patch) {
    this->patch = patch;
    CCLabelBMFont* label = CCLabelBMFont::create(patch->m_label.c_str(), "goldFont.fnt");

    if (index & 1) {
        this->m_backgroundLayer->setColor(LIGHT_CELL);
    } else {
        this->m_backgroundLayer->setColor(DARK_CELL);
    }

    label->setScale(0.7f);
    label->setPosition({ 10, this->m_height - 5 });
    label->setAnchorPoint(TOP_LEFT);

    this->m_mainLayer->addChild(label);

    if (this->init()) {
        this->m_backgroundLayer->setOpacity(0xFF);
    } else {
        this->m_mainLayer->setContentSize({ this->m_width, 0 });
        this->m_mainLayer->setVisible(false);
    }
}