#pragma once

#include "../includes.hpp"

namespace gd {
    struct AppDelegate {
        virtual bool applicationDidFinishLaunching() { return true; }
        virtual void applicationWillBecomeActive() { }
        virtual void applicationDidEnterBackground() { }
        virtual void applicationWillEnterForeground() { }
        virtual void applicationWillResignActive() { }
        virtual void trySaveGame() { }
    };
}

inline bool (__thiscall* AppDelegate_applicationDidFinishLaunching)(AppDelegate* self);
bool __fastcall AppDelegate_applicationDidFinishLaunching_H(AppDelegate* self, void*);