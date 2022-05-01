#include "AppDelegate.hpp"
#include "../bindings/CCContentManager.hpp"

bool __fastcall AppDelegate_applicationDidFinishLaunching_H(AppDelegate* self, void*) {
    if (gd::started) {
        CCDirector* director = CCDirector::sharedDirector();
        CCScene* scene = CCScene::create();

        director->popToRootScene();
        director->replaceScene(scene);
        CCContentManager::sharedManager()->clearCache();
        CCTextureCache::purgeSharedTextureCache();
        CCLabelBMFont::purgeCachedData();
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