#pragma once

#include "../includes.hpp"

RT_ADD(
    class CC_DLL CCContentManager : public CCObject {
    public:
        static CCContentManager* sharedManager();

        CCContentManager();
        bool init();
        cocos2d::CCDictionary* addDict(const char* dict, bool unk);
        cocos2d::CCDictionary* addDictDS(const char* dict);
        void clearCache();
    };
);