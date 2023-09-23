#pragma once

#include "../includes.hpp"

namespace cocos2d {
    struct CCAnimateFrameCache : public CCObject {
        CCDictionary* m_dict0;
        CCDictionary* m_dict1;
        CCDictionary* m_dict2;

        static CCAnimateFrameCache* sharedAnimateFrameCache() {
            return reinterpret_cast<CCAnimateFrameCache*(__thiscall*)()>(gd::base + 0x158F0)();
        }

        void addSpriteFramesWithFile(const char* file) {
            reinterpret_cast<void(__thiscall*)(CCAnimateFrameCache*, const char*)>(gd::base + 0x159B0)(this, file);
        }            
    };
}