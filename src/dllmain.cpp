#include "includes.hpp"

DWORD WINAPI thread_func(const LPVOID hModule) {
    MH_Initialize();

    for (const hook_t& hook : gd::hooks) {
        MH_CreateHook(
            reinterpret_cast<LPVOID>((std::get<0>(hook) ? gd::cocosBase : gd::base) + std::get<1>(hook)), 
            std::get<2>(hook), 
            std::get<3>(hook)
        );
    }

    MH_EnableHook(MH_ALL_HOOKS);

    return 0;
}

BOOL APIENTRY DllMain(const HMODULE handle, const DWORD reason, const LPVOID reserved) {
    #ifdef SHOW_CONSOLE
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