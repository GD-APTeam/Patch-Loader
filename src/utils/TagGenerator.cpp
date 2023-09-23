#include "TagGenerator.hpp"

const unsigned short TagGenerator::MOD_ID = TagGenerator::hashName(PROJECT_NAME);

unsigned short TagGenerator::hashName(const std::string& name) {
    size_t hash = 0;

    for (const char& c : name) {
        hash += c + (hash << 5) + (c << 7);
    }

    return (hash ^ (hash >> 16)) & 0xFFFF;
}

int TagGenerator::hashTag(const short tag) {
    return TagGenerator::MOD_ID | (tag << 16);
}