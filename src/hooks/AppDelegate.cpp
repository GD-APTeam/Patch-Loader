#include <Geode/modify/AppDelegate.hpp>

#include "../includes.hpp"
#include "../objects/Patch.hpp"
#include "../objects/PatchStorage.hpp"

static bool started = false;

class $modify(AppDelegate) {

    bool applicationDidFinishLaunching() {
        if (started) {
            CCDirector* director = CCDirector::sharedDirector();
            CCAnimateFrameCache* animateFrameCache = CCAnimateFrameCache::sharedSpriteFrameCache();

            director->popToRootScene();
            director->replaceScene(CCScene::create());
            CCContentManager::sharedManager()->clearCache();
            CCTextureCache::purgeSharedTextureCache();
            CCLabelBMFont::purgeCachedData();
            animateFrameCache->m_unknown1->removeAllObjects();
            animateFrameCache->m_unknown2->removeAllObjects();
            animateFrameCache->m_unknown3->removeAllObjects();
            CCShaderCache::purgeSharedShaderCache();
            CCShaderCache::sharedShaderCache()->reloadDefaultShaders();
        } else {
            started = true;
        }

        for (Patch& patch : PatchStorage::sharedState()->m_patches) {
            if (patch.m_enabled) {
                // Soft reset the patch.
                patch.m_enabled = false;
                patch.apply();
            }
        }

        return AppDelegate::applicationDidFinishLaunching();
    }
};