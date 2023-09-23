#include "AppDelegate.hpp"

IMPLEMENT_HOOK(bool, AppDelegate, applicationDidFinishLaunching) {
    if (gd::started) {
        CCDirector* director = CCDirector::sharedDirector();
        CCAnimateFrameCache* animateFrameCache = CCAnimateFrameCache::sharedAnimateFrameCache();

        director->popToRootScene();
        director->replaceScene(CCScene::create());
        CCContentManager::sharedManager()->clearCache();
        CCTextureCache::purgeSharedTextureCache();
        CCLabelBMFont::purgeCachedData();
        animateFrameCache->m_dict0->removeAllObjects();
        animateFrameCache->m_dict1->removeAllObjects();
        animateFrameCache->m_dict2->removeAllObjects();
        CCShaderCache::purgeSharedShaderCache();
        CCShaderCache::sharedShaderCache()->reloadDefaultShaders();
    } else {
        gd::started = true;
    }

    for (Patch& patch : PatchStorage::sharedState()->m_patches) {
        if (patch.m_enabled) {
            // Soft reset the patch.
            patch.m_enabled = false;
            patch.apply();
        }
    }

    return AppDelegate_applicationDidFinishLaunching(self);
}