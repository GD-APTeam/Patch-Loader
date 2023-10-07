#include "SubPatchCell.hpp"

SubPatchCell::SubPatchCell(const char* name, const CCSize& size) : StatsCell(name, size.width, size.height) { }

bool SubPatchCell::initWithPatch(const size_t index, SubPatch* patch) {
    this->m_patch = patch;
    this->m_label = CCLabelBMFont::create(patch->m_label.c_str(), "goldFont.fnt");
    this->m_content = CCMenu::create();

    this->m_label->setScale(0.7f);
    this->m_label->setPosition({ 10, this->m_height - 5 });
    this->m_label->setAnchorPoint(TOP_LEFT);
    this->m_content->setPosition({ 10, 5 });
    this->m_content->setContentSize({ this->m_width - 20, this->m_height - this->m_label->getContentSize().height - 5 });
    this->m_content->setAnchorPoint(TOP_LEFT);

    this->m_mainLayer->addChild(this->m_label);
    this->m_mainLayer->addChild(this->m_content);
    this->m_backgroundLayer->setOpacity(FULL_OPACITY);
    this->updateBGColor(index);

    return this->init();
}