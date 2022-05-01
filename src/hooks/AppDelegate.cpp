#include "AppDelegate.hpp"
#include "../bindings/CCContentManager.hpp"
#include "../bindings/CCAnimateFrameCache.hpp"

bool __fastcall AppDelegate_applicationDidFinishLaunching_H(AppDelegate* self, void*) {
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

    for (std::shared_ptr<PatchBase> patch : gd::patches) {
        patch->apply();
    }

    return AppDelegate_applicationDidFinishLaunching(self);
}