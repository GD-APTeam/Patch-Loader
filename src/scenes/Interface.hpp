#pragma once

#include "../includes.hpp"

struct Interface : public FLAlertLayer {
protected:
    Interface(const CCSize size, const std::string sprite = "GJ_square01.png");
    bool init();
    void setTitle(const std::string& title, const std::string& font = "goldFont.fnt");
    virtual void render(CCLayer* layer) = 0;
private:
    const std::string m_sprite;
    const CCSize m_size;

    void onClose(CCObject* sender);
};