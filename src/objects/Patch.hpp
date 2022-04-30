#pragma once

#include "../includes.hpp"
#include "../utils/json.hpp"

using namespace nlohmann;

struct Patch {
    static bool isValid(json patch);

    std::string name;
    std::string description;
    LPVOID address;
    std::vector<std::byte> bytes;
    std::vector<std::byte> original;
    bool cocos;
    bool disabled;

    Patch(json patch);
    void apply();
    void revert();
};