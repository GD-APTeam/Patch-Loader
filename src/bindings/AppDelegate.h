#ifndef __APPDELEGATE_H__
#define __APPDELEGATE_H__

#include <windows.h>

uintptr_t base = reinterpret_cast<uintptr_t>(GetModuleHandleA(0));

namespace gd {
    class AppDelegate {
    public:
        virtual bool applicationDidFinishLaunching() {
            return reinterpret_cast<bool(__thiscall*)(AppDelegate*)>(base + 0x3CBB0)(this);
        }
        virtual void applicationWillBecomeActive() {
            return reinterpret_cast<void(__thiscall*)(AppDelegate*)>(base + 0x3CE90)(this);
        }
        virtual void applicationDidEnterBackground() {
            return reinterpret_cast<void(__thiscall*)(AppDelegate*)>(base + 0x3CF40)(this);
        }
        virtual void applicationWillEnterForeground() {
            return reinterpret_cast<void(__thiscall*)(AppDelegate*)>(base + 0x3D130)(this);
        }
        virtual void applicationWillResignActive() {
            return reinterpret_cast<void(__thiscall*)(AppDelegate*)>(base + 0x3D3E0)(this);
        }
        virtual void trySaveGame() {
            return reinterpret_cast<void(__thiscall*)(AppDelegate*)>(base + 0x3D5E0)(this);
        }
    };
}
#endif