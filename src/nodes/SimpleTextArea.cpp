#include "SimpleTextArea.hpp"

SimpleTextArea* SimpleTextArea::create(const std::string& text, const std::string& font, const float scale) {
    return SimpleTextArea::create(font, text, scale, CCDirector::sharedDirector()->getWinSize().width / 2, false);
}

SimpleTextArea* SimpleTextArea::create(const std::string& text, const std::string& font, const float scale, const float width) {
    return SimpleTextArea::create(font, text, scale, width, true);
}

SimpleTextArea* SimpleTextArea::create(const std::string& font, const std::string& text, const float scale, const float width, const bool artificialWidth) {
    SimpleTextArea* instance = new SimpleTextArea(font, text, scale, width, artificialWidth);

    if (instance && instance->init()) {
        instance->autorelease();

        return instance;
    } else {
        CC_SAFE_DELETE(instance);
        
        return nullptr;
    }
}

SimpleTextArea::SimpleTextArea(const std::string& font, const std::string& text, const float scale, const float width, const bool artificialWidth) {
    this->m_font = font;
    this->m_text = text;
    this->m_maxLines = 0;
    this->m_scale = scale;
    this->m_linePadding = 0;
    this->m_color = WHITE_4B;
    this->m_alignment = kCCTextAlignmentLeft;
    this->m_wrappingMode = WORD_WRAP;
    this->m_artificialWidth = artificialWidth;
    this->m_container = CCMenu::create();
    this->m_shouldUpdate = true;

    this->setAnchorPoint(CENTER);
    this->m_container->setPosition(ZERO_POINT);
    this->m_container->setAnchorPoint(TOP_LEFT);
    this->m_container->setContentSize({ width, 0 });

    this->addChild(this->m_container);
}

void SimpleTextArea::setFont(const std::string& font) {
    this->m_font = font;
    this->m_shouldUpdate = true;
}

std::string SimpleTextArea::getFont() {
    return this->m_font;
}

void SimpleTextArea::setColor(const ccColor4B& color) {
    this->m_color = color;
    this->m_shouldUpdate = true;
}

ccColor4B SimpleTextArea::getColor() {
    return this->m_color;
}

void SimpleTextArea::setAlignment(const CCTextAlignment alignment) {
    this->m_alignment = alignment;
    this->m_shouldUpdate = true;
}

CCTextAlignment SimpleTextArea::getAlignment() {
    return this->m_alignment;
}

void SimpleTextArea::setWrappingMode(const WrappingMode mode) {
    this->m_wrappingMode = mode;
    this->m_shouldUpdate = true;
}

WrappingMode SimpleTextArea::getWrappingMode() {
    return this->m_wrappingMode;
}

void SimpleTextArea::setText(const std::string& text) {
    this->m_text = text;
    this->m_shouldUpdate = true;
}

std::string SimpleTextArea::getText() {
    return this->m_text;
}

void SimpleTextArea::setMaxLines(const size_t maxLines) {
    this->m_maxLines = maxLines;
    this->m_shouldUpdate = true;
}

size_t SimpleTextArea::getMaxLines() {
    return this->m_maxLines;
}

void SimpleTextArea::setWidth(const float width) {
    this->m_artificialWidth = true;
    this->m_shouldUpdate = true;

    this->setContentSize({ width, this->getContentSize().height });
    this->m_container->setContentSize(this->getContentSize());
}

float SimpleTextArea::getWidth() {
    return this->m_container->getContentSize().width;
}

void SimpleTextArea::setScale(const float scale) {
    this->m_scale = scale;
    this->m_shouldUpdate = true;
}

float SimpleTextArea::getScale() {
    return this->m_scale;
}

void SimpleTextArea::setLinePadding(const float padding) {
    this->m_linePadding = padding;
    this->m_shouldUpdate = true;
}

float SimpleTextArea::getLinePadding() {
    return this->m_linePadding;
}

std::vector<CCLabelBMFont*> SimpleTextArea::getLines() {
    return this->m_lines;
}

float SimpleTextArea::getHeight() {
    return this->m_container->getContentSize().height;
}

float SimpleTextArea::getLineHeight() {
    return this->m_lineHeight;
}

CCLabelBMFont* SimpleTextArea::createLabel(const std::string& text, const float top) {
    CCLabelBMFont* label = CCLabelBMFont::create(text.c_str(), this->m_font.c_str());

    label->setScale(this->m_scale);
    label->setPosition({ 0, top });
    label->setColor({ this->m_color.r, this->m_color.g, this->m_color.b });
    label->setOpacity(this->m_color.a);

    return label;
}

float SimpleTextArea::calculateOffset(CCLabelBMFont* label) {
    return this->m_linePadding + label->getContentSize().height * this->m_scale;
}

void SimpleTextArea::charIteration(const std::function<CCLabelBMFont*(CCLabelBMFont* line, const char c, const float top)>& overflowHandling) {
    float top = 0;
    CCLabelBMFont* line = this->createLabel("", top);
    this->m_lines = { line };

    for (const char c : this->m_text) {
        if (this->m_maxLines && this->m_lines.size() > this->m_maxLines) {
            CCLabelBMFont* last = this->m_lines.at(this->m_maxLines - 1);
            const std::string text = last->getString();

            this->m_lines.pop_back();
            last->setString(text.substr(0, text.size() - 3).append("...").c_str());

            break;
        } else if (c == '\n') {
            this->m_lines.push_back(line = this->createLabel("", top -= this->calculateOffset(line)));
        } else if (this->m_artificialWidth && line->getContentSize().width * this->m_scale >= this->getWidth()) {
            this->m_lines.push_back(line = overflowHandling(line, c, top -= this->calculateOffset(line)));
        } else {
            line->setString((std::string(line->getString()) + c).c_str());
        }
    }
}

void SimpleTextArea::updateLinesNoWrap() {
    std::stringstream stream(this->m_text);
    std::string part;
    float top = 0;

    while (std::getline(stream, part)) {
        if (this->m_maxLines && this->m_lines.size() >= this->m_maxLines) {
            CCLabelBMFont* last = this->m_lines.at(this->m_maxLines - 1);
            const std::string text = last->getString();

            last->setString(text.substr(0, text.size() - 3).append("...").c_str());

            break;
        } else {
            CCLabelBMFont* line = this->createLabel(part, 0);

            top -= this->calculateOffset(line);

            this->m_lines.push_back(line);
        }
    }
}

void SimpleTextArea::updateLinesWordWrap() {
    this->charIteration([this](CCLabelBMFont* line, const char c, const float top) {
        static std::string delimiters(" `~!@#$%^&*()-_=+[{}];:'\",<.>/?\\|");

        if (delimiters.find(c) == std::string_view::npos) {
            const std::string text = line->getString();
            const size_t position = text.find_last_of(delimiters) + 1;

            line->setString(text.substr(0, position).c_str());

            return this->createLabel(text.substr(position) + c, top);
        } else {
            return this->createLabel(std::string(c, c != ' '), top);
        }
    });
}

void SimpleTextArea::updateLinesCutoffWrap() {
    this->charIteration([this](CCLabelBMFont* line, const char c, const float top) {
        const std::string text = line->getString();
        const char back = text.back();
        const bool lastIsSpace = back == ' ';
        CCLabelBMFont* newLine = this->createLabel(std::string(!lastIsSpace, back).append(std::string(c != ' ', c)), top);

        if (!lastIsSpace) {
            if (text[text.size() - 2] == ' ') {
                line->setString(text.substr(0, text.size() - 1).c_str());
            } else {
                line->setString((text.substr(0, text.size() - 1) + '-').c_str());
            }
        }

        return newLine;
    });
}

void SimpleTextArea::updateContainer() {
    switch (this->m_wrappingMode) {
        case NO_WRAP: {
            this->updateLinesNoWrap();
        } break;
        case WORD_WRAP: {
            this->updateLinesWordWrap();
        } break;
        case CUTOFF_WRAP: {
            this->updateLinesCutoffWrap();
        } break;
    }
    
    const size_t lineCount = this->m_lines.size();
    const float width = this->getWidth();

    if (lineCount > 0) {
        this->m_lineHeight = this->m_lines.back()->getContentSize().height * this->m_scale;
    } else {
        this->m_lineHeight = 0;
    }

    float height = this->m_lineHeight * lineCount + this->m_linePadding * (lineCount - 1);

    this->setContentSize({ width, height });
    this->m_container->setContentSize(this->getContentSize());
    this->m_container->removeAllChildren();

    for (CCLabelBMFont* line : this->m_lines) {
        const float y = height + line->getPositionY();

        switch (this->m_alignment) {
            case kCCTextAlignmentLeft: {
                line->setAnchorPoint(TOP_LEFT);
                line->setPosition({ 0, y });
            } break;
            case kCCTextAlignmentCenter: {
                line->setAnchorPoint(TOP_CENTER);
                line->setPosition({ width / 2, y });
            } break;
            case kCCTextAlignmentRight: {
                line->setAnchorPoint(TOP_RIGHT);
                line->setPosition({ width, y });
            } break;
        }

        this->m_container->addChild(line);
    }
}

void SimpleTextArea::draw() {
    CCNode::draw();

    if (this->m_shouldUpdate) {
        this->updateContainer();

        this->m_shouldUpdate = false;
    }
}