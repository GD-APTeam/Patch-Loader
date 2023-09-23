#include "Hook.hpp"

Hook::Hook(const hook_t hook) {
    gd::hooks.push_back(hook);
}