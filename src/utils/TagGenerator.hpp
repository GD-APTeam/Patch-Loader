#pragma once

#include "../includes.hpp"

struct TagGenerator {
    static const unsigned short MOD_ID;

    static int hashTag(const short tag);
private:
    static unsigned short hashName(const std::string& name);
};