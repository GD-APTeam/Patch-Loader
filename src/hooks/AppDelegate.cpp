#include "AppDelegate.hpp"

bool __fastcall AppDelegate_applicationDidFinishLaunching_H(AppDelegate* self, void*) {
    for (std::shared_ptr<PatchBase> patch : gd::patches) {
        patch->apply();
    }

    return AppDelegate_applicationDidFinishLaunching(self);
}