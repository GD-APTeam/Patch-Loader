#include "SubPatchRangeCell.hpp"

SubPatchRangeCell* SubPatchRangeCell::create(const char* name, const CCSize& size) {
    return new SubPatchRangeCell(name, size);
}

SubPatchRangeCell::SubPatchRangeCell(const char* name, const CCSize& size) : SubPatchCell(name, size) { }

bool SubPatchRangeCell::init() {
    if (this->m_patch->m_range.m_isValid) {
        Slider* slider = Slider::create(this, menu_selector(SubPatchRangeCell::onSlider), 0.75f);

        slider->setPosition({ slider->m_width / 2 * 0.8f, slider->m_height });
        slider->setValue(0);
        slider->updateBar();

        this->m_content->addChild(slider);

        return true;
    } else {
        return false;
    }
}

void SubPatchRangeCell::onSlider(CCObject* sender) {
    const int value = this->m_patch->m_range.percentageToRangeValue(reinterpret_cast<SliderThumb*>(sender)->getValue());

    if (this->m_patch->m_range.m_value != value) {
        this->m_patch->m_range.apply(value);
    }
}
