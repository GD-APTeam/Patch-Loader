#pragma once

#include "../includes.hpp"

using hook_float_t = void*;

#define _CONCAT_LITERAL(a, b) a##b
#define CONCAT_LITERAL(a, b) _CONCAT_LITERAL(a, b)

#define GD_HOOK(address, class, method) HOOK(false, address, class, method)
#define COCOS_HOOK(address, class, method) HOOK(true, address, class, method)
#define HOOK(cocos, address, class, method) static Hook CONCAT_LITERAL(class##_##method, __LINE__)({ \
    cocos, \
    address, \
    reinterpret_cast<LPVOID>(&class##_##method##_H), \
    reinterpret_cast<LPVOID*>(&class##_##method) \
})
#define DEFINE_HOOK(type, class, method, ...) \
    _DEFINE_TRAMPOLINE(type, thiscall, class##_##method, class* self, __VA_ARGS__) \
    _DEFINE_DETOUR(type, class##_##method, class* self, void* edx, __VA_ARGS__)
#define IMPLEMENT_HOOK(type, class, method, ...) _DEFINE_DETOUR(type, class##_##method, class* self, void* edx, __VA_ARGS__)
#define DEFINE_STATIC_HOOK(type, class, method, ...) \
    _DEFINE_TRAMPOLINE(type, fastcall, class##_##method, __VA_ARGS__) \
    _DEFINE_DETOUR(type, class##_##method, __VA_ARGS__)
#define IMPLEMENT_STATIC_HOOK(type, class, method, ...) _DEFINE_DETOUR(type, class##_##method, __VA_ARGS__)
#define DEFINE_FLOATING_HOOK(type, class, method, ...) \
    _DEFINE_TRAMPOLINE(type, thiscall, class##_##method, class* self) \
    _DEFINE_DETOUR(type, class##_##method, class* self, void* edx, __VA_ARGS__)
#define DEFINE_STATIC_FLOATING_HOOK(type, class, method, ...) \
    _DEFINE_TRAMPOLINE(type, fastcall, class##_##method) \
    _DEFINE_DETOUR(type, class##_##method, __VA_ARGS__)
#define _DEFINE_TRAMPOLINE(type, convention, method, ...) type (__##convention* method)(__VA_ARGS__);
#define _DEFINE_DETOUR(type, method, ...) type __fastcall method##_H(__VA_ARGS__)
#define EXTRACT_FLOAT(variable, paramIndex) \
    float variable; \
    __asm movss variable, xmm##paramIndex
#define REINSERT_FLOAT(variable, paramIndex) __asm movss xmm##paramIndex, variable

struct Hook {
    Hook(const hook_t hook);
};