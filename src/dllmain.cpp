#include <fstream>

#include "includes.hpp"
#include "hooks/AppDelegate.hpp"
#include "hooks/MenuLayer.hpp"

DWORD WINAPI thread_func(void* hModule) {
    // Caching patches
    std::ifstream file("patches.json", std::ifstream::binary);

    if (file.good()) {
        json patchesRaw;

        file >> patchesRaw;

        gd::patches = PatchBase::create(patchesRaw);
    }

    MH_Initialize();

    // AppDelegate
    MH_CreateHook(
        reinterpret_cast<void*>(gd::base + 0x3CBB0),
        reinterpret_cast<void*>(&AppDelegate_applicationDidFinishLaunching_H),
        reinterpret_cast<void**>(&AppDelegate_applicationDidFinishLaunching)
    );

    // MenuLayer
    MH_CreateHook(
        reinterpret_cast<void*>(gd::base + 0x1907b0),
        reinterpret_cast<void*>(&MenuLayer_init_H),
        reinterpret_cast<void**>(&MenuLayer_init)
    );

    MH_EnableHook(MH_ALL_HOOKS);

    return 0;
}

BOOL APIENTRY DllMain(HMODULE handle, DWORD reason, LPVOID reserved) {
    #if CMAKE_BUILD_TYPE == RelWithDebInfo
        if (AllocConsole()) {
            freopen_s(reinterpret_cast<FILE**>(stdout), "CONOUT$", "w", stdout);
            freopen_s(reinterpret_cast<FILE**>(stdin), "CONIN$", "r", stdin);
        }
    #endif
    
    if (reason == DLL_PROCESS_ATTACH) {
        CreateThread(0, 0x100, thread_func, handle, 0, 0);
    }

    return TRUE;
}