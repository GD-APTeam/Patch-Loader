#pragma once

#include <fstream>

#include "Patch.hpp"
#include "../includes.hpp"

struct PatchStorage {
    static PatchStorage* sharedState();
    static std::string m_fileName;
    static size_t m_indent;

    std::vector<Patch> m_patches;

    size_t size();
    Patch& get(const size_t index);
    void addPatch(Patch patch);
    void removePatch(const size_t index);
    void replacePatch(const size_t index, Patch patch);
private:
    PatchStorage();
    void save();
};