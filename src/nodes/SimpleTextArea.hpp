#pragma once

#include "../includes.hpp"

struct SimpleTextArea : public CCNode {
    CCMenu* m_container;
    std::string m_font;
    std::string m_text;
    std::vector<CCLabelBMFont*> m_lines;
    ccColor4B m_color;
    CCTextAlignment m_alignment;
    size_t m_maxLines;
    float m_scale;
    float m_lineHeight;
    float m_linePadding;
    bool m_artificialWidth;
public:
    static SimpleTextArea* create(const std::string& text, const std::string& font = "chatFont.fnt", const float scale = 1);
    static SimpleTextArea* create(const std::string& text, const std::string& font, const float scale, const float width);

    void setFont(const std::string& font);
    std::string getFont();
    void setColor(const ccColor4B& color);
    ccColor4B getColor();
    void setAlignment(const CCTextAlignment alignment);
    CCTextAlignment getAlignment();
    void setText(const std::string& text);
    std::string getText();
    void setMaxLines(const size_t maxLines);
    size_t getMaxLines();
    void setWidth(const float width);
    float getWidth();
    void setScale(const float scale);
    float getScale();
    void setLinePadding(const float padding);
    float getLinePadding();
    std::vector<CCLabelBMFont*> getLines();
    float getHeight();
    float getLineHeight();
private:
    static SimpleTextArea* create(const std::string& font, const std::string& text, const float scale, const float width, const bool artificialWidth);

    SimpleTextArea(const std::string& font, const std::string& text, const float scale, const float width, const bool artificialWidth);
    CCLabelBMFont* createLabel(const std::string& text, const float top);
    CCLabelBMFont* moveOverflow(CCLabelBMFont* line, const char c, const float top);
    float calculateOffset(CCLabelBMFont* label);
    void updateLines();
    void updateContents();
};