#pragma once 

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