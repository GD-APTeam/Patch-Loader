#include "AppDelegate.hpp"

bool __fastcall AppDelegate_applicationDidFinishLaunching_H(AppDelegate* self, void*) {
    for (Patch patch : gd::patches) {
        if (!patch.disabled) {
            patch.apply();
        }
    }

    return AppDelegate_applicationDidFinishLaunching(self);
}