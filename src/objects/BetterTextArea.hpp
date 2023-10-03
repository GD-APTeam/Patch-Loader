#pragma once

#include "../includes.hpp"

template<bool TTF>
using CCLabel = std::conditional_t<TTF, CCLabelTTF, CCLabelBMFont>;

template<bool TTF>
struct BetterTextArea : public CCNode {

    static BetterTextArea* create(const std::string& font, const std::string& text, const float scale = 1) {
        return BetterTextArea::create<TTF>(font, text, scale, 500, false);
    }

    static BetterTextArea* create(const std::string& font, const std::string& text, const float scale, const float width) {
        return BetterTextArea::create<TTF>(font, text, scale, width, true);
    }

    void setFont(const std::string& font) {
        this->m_font = font;

        this->updateContents();
    }

    void setAlignment(const CCTextAlignment alignment) {
        this->m_alignment = alignment;

        this->updateContents();
    }

    CCTextAlignment getAlignment() {
        return this->m_alignment;
    }

    std::string getFont() {
        return this->m_font;
    }

    void setText(const std::string& text) {
        this->m_text = text;

        this->updateContents();
    }

    std::string getText() {
        return this->m_text;
    }

    std::vector<CCLabel<TTF>*> getLines() {
        return this->m_lines;
    }

    void setMaxLines(const size_t maxLines) {
        this->m_maxLines = maxLines;

        this->updateContents();
    }

    size_t getMaxLines() {
        return this->m_maxLines;
    }

    void setWidth(const float width) {
        this->m_artificialWidth = true;

        this->setContentSize({ width, this->getContentSize().height });
        this->m_container->setContentSize(this->getContentSize());
    }

    float getWidth() {
        return this->m_container->getContentSize().width;
    }

    float getHeight() {
        return this->m_container->getContentSize().height;
    }

    void setScale(const float scale) {
        this->m_scale = scale;

        this->updateContents();
    }

    float getScale() {
        return this->m_scale;
    }

    float getLineHeight() {
        return this->m_lineHeight;
    }

    void setLinePadding(const float padding) {
        this->m_linePadding = padding;

        this->updateContents();
    }

    float getLinePadding() {
        return this->m_linePadding;
    }

private:
    template<bool TTF>
    static BetterTextArea* create(const std::string& font, const std::string& text, const float scale, const float width, const bool artificialWidth) {
        BetterTextArea* instance = new BetterTextArea<TTF>(font, text, scale, width, artificialWidth);

        if (instance && instance->init()) {
            instance->autorelease();

            return instance;
        } else {
            CC_SAFE_DELETE(instance);
            
            return nullptr;
        }
    }

    CCMenu* m_container;
    std::string m_font;
    std::string m_text;
    std::vector<CCLabel<TTF>*> m_lines;
    CCTextAlignment m_alignment;
    size_t m_maxLines;
    float m_scale;
    float m_lineHeight;
    float m_linePadding;
    bool m_artificialWidth;

    BetterTextArea(const std::string& font, const std::string& text, const float scale, const float width, const bool artificialWidth) {
        this->m_font = font;
        this->m_text = text;
        this->m_maxLines = 0;
        this->m_scale = scale;
        this->m_linePadding = 0;
        this->m_artificialWidth = artificialWidth;
        this->m_container = CCMenu::create();

        this->setAnchorPoint({ 0.5f, 0.5f });
        this->m_container->setPosition({ 0, 0 });
        this->m_container->setAnchorPoint({ 0, 1 });
        this->m_container->setContentSize({ width, 0 });

        this->addChild(this->m_container);
        this->updateContents();
    }

    CCLabel<TTF>* createLabel(const std::string& text, const float top) {
        CCLabel<TTF>* label;

        if constexpr (TTF) {
            label = CCLabelTTF::create(text, this->m_font, this->m_scale);
        } else {
            label = CCLabelBMFont::create(text.c_str(), this->m_font.c_str());

            label->setScale(this->m_scale);
        }

        label->setAnchorPoint({ 0, 0 });
        label->setPosition({ 0, top });

        return label;
    }

    float calculateOffset(CCLabel<TTF>* label) {
        return this->m_linePadding + label->getContentSize().height * this->m_scale;
    }

    void updateLines() {
        float top = 0;
        CCLabel<TTF>* line = this->createLabel("", top);
        this->m_lines = { line };

        for (const char c : this->m_text) {
            if (this->m_maxLines && this->m_lines.size() > this->m_maxLines) {
                CCLabel<TTF>* last = this->m_lines.at(this->m_maxLines - 1);
                const std::string text = last->getString();

                this->m_lines.pop_back();
                last->setString(text.substr(0, text.size() - 3).append("...").c_str());

                break;
            } else if (c == '\n') {
                line = this->createLabel("", top -= this->calculateOffset(line));

                this->m_lines.push_back(line);
            } else if (this->m_artificialWidth && line->getContentSize().width >= this->getWidth()) {
                line = this->moveOverflow(line, c, top -= this->calculateOffset(line));
            } else {
                const std::string text = line->getString();

                line->setString((text + c).c_str());
            }
        }
    }

    CCLabel<TTF>* moveOverflow(CCLabel<TTF>* line, const char c, const float top) {
        const std::string text = line->getString();
        const char back = text.back();
        const bool lastIsSpace = back == ' ';
        CCLabel<TTF>* newLine = this->createLabel(std::string(!lastIsSpace, back).append(std::string(c != ' ', c)), top);

        if (!lastIsSpace) {
            if (text[text.size() - 2] == ' ') {
                line->setString(text.substr(0, text.size() - 1).c_str());
            } else {
                line->setString((text.substr(0, text.size() - 1) + '-').c_str());
            }
        }

        this->m_lines.push_back(newLine);

        return newLine;
    }

    void updateContents() {
        this->updateLines();
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

        height -= this->m_lineHeight;

        for (CCLabel<TTF>* line : this->m_lines) {
            const float y = height + line->getPositionY();

            switch (this->m_alignment) {
                case kCCTextAlignmentLeft: {
                    line->setAnchorPoint({ 0, 0 });
                    line->setPosition({ 0, y });
                } break;
                case kCCTextAlignmentCenter: {
                    line->setAnchorPoint({ 0.5f, 0 });
                    line->setPosition({ width / 2, y });
                } break;
                case kCCTextAlignmentRight: {
                    line->setAnchorPoint({ 1, 0 });
                    line->setPosition({ width, y });
                } break;
            }

            this->m_container->addChild(line);
        }
    }
};