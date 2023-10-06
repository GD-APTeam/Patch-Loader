#include "SimpleTextContainer.hpp"

SimpleTextContainer* SimpleTextContainer::create(const CCSize& size, const std::string& text, const ccColor4B& color, const std::string& font, const float scale) {
    SimpleTextContainer* container = new SimpleTextContainer();

    if (container && container->init(size, text, color, font, scale)) {
        container->autorelease();

        return container;
    } else {
        CC_SAFE_DELETE(container);

        return nullptr;
    }
}

bool SimpleTextContainer::init(const CCSize& size, const std::string& text, const ccColor4B& color, const std::string& font, const float scale) {
    if (CCScale9Sprite::initWithFile("square02b_001.png", SPRITE_RECT)) {
        this->m_textArea = SimpleTextArea::create(text, font, scale, size.width - 20);

        this->setContentSize(size);
        this->setColor({ color.r, color.g, color.b });
        this->setOpacity(color.a);
        this->m_textArea->setAnchorPoint(CENTER);
        this->m_textArea->setPosition(size / 2);
        this->m_textArea->setMaxLines((size.height - 20) / this->m_textArea->getLineHeight());

        this->addChild(this->m_textArea);

        return true;
    } else {
        return false;
    }
}