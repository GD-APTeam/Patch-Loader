#pragma once

#include "../includes.hpp"
#include "SimpleTextArea.hpp"

struct SimpleTextContainer : public CCScale9Sprite {
    static SimpleTextContainer* create(const CCSize& size, const std::string& text, const ccColor4B& color = BROWN_AREA_4B, const std::string& font = "chatFont.fnt", const float scale = 1);

    SimpleTextArea* m_textArea;
private:
    bool init(const CCSize& size, const std::string& text, const ccColor4B& color, const std::string& font, const float scale);
};