#pragma once

#include "BasePatch.hpp"
#include "PatchRange.hpp"
#include "../includes.hpp"

enum PatchType {
    BYTES,
    RANGE,
    CHECKBOX,
    COLOR,
};

struct SubPatch : public BasePatch {
    static SubPatch get(const json& object);
    static bool isValidBytes(const json& bytes);

    PatchType m_type;
    std::string m_label;
    std::uintptr_t m_address;
    bool m_cocos;
    std::vector<std::byte> m_bytes;
    PatchRange m_range;

    SubPatch(const bool valid);
    virtual void apply() override;
    virtual void revert() override;
    virtual json toJson() override;
private:
    LPVOID m_realAddress;
    std::vector<std::byte> m_original;
};