#include "includes.h"

bool (__thiscall* AppDelegate_applicationDidFinishLaunching)(gd::AppDelegate* self);
bool __fastcall AppDelegate_applicationDidFinishLaunching_H(gd::AppDelegate* self, void*) {
    std::ifstream file("patches.json", std::ifstream::binary);

    if (file.good()) {        
        uintptr_t gdBase = reinterpret_cast<uintptr_t>(GetModuleHandleA(0));
        uintptr_t cocosBase = reinterpret_cast<uintptr_t>(GetModuleHandleA("libcocos2d.dll"));
        json patches;

        file >> patches;

        for (json& patch : patches) {
            if (patch["address"].is_number_unsigned() && patch["bytes"].is_array()) {
                uintptr_t baseAddress;

                if (patch["cocos"].is_boolean() && patch["cocos"].get<bool>()) {
                    baseAddress = cocosBase;
                } else {
                    baseAddress = gdBase;
                }

                WriteProcessMemory(
                    GetCurrentProcess(),
                    reinterpret_cast<LPVOID>(baseAddress + patch["address"].get<unsigned int>()),
                    patch["bytes"].get<std::vector<uint8_t>>().data(),
                    patch["bytes"].size(),
                    nullptr
                );
            }
        }
    }

    return AppDelegate_applicationDidFinishLaunching(self);
}

DWORD WINAPI thread_func(void* hModule) {
    MH_Initialize();
    MH_CreateHook(
        reinterpret_cast<void*>(reinterpret_cast<uintptr_t>(GetModuleHandleA(0)) + 0x3CBB0),
        AppDelegate_applicationDidFinishLaunching_H,
        reinterpret_cast<void**>(&AppDelegate_applicationDidFinishLaunching)
    );

    // enable all hooks you've created with minhook
    MH_EnableHook(MH_ALL_HOOKS);

    return 0;
}

BOOL APIENTRY DllMain(HMODULE handle, DWORD reason, LPVOID reserved) {
    if (reason == DLL_PROCESS_ATTACH) {
        CreateThread(0, 0x100, thread_func, handle, 0, 0);
    }

    return TRUE;
}