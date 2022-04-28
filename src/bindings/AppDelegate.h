#ifndef __APPDELEGATE_H__
#define __APPDELEGATE_H__

namespace gd {
    class AppDelegate {
        virtual bool applicationDidFinishLaunching() { return true; }
        virtual void applicationWillBecomeActive() { }
        virtual void applicationDidEnterBackground() { }
        virtual void applicationWillEnterForeground() { }
        virtual void applicationWillResignActive() { }
        virtual void trySaveGame() { }
    };
}
#endif