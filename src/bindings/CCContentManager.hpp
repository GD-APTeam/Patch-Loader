#pragma once

#include "../includes.hpp"

RT_ADD(
    class CC_DLL CCContentManager : public CCObject {
    public:
        static CCContentManager* sharedManager();

        CCContentManager();
        bool init();
        CCDictionary* addDict(const char* dict, bool unk);
        CCDictionary* addDictDS(const char* dict);
        void clearCache();
    };
);