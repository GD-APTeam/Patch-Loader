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

struct SubPatch : public CCObject, public BasePatch {
    static SubPatch get(const JSON& object);
    static bool isValidBytes(const JSON& bytes);

    PatchType m_type;
    std::string m_label;
    std::uintptr_t m_address;
    bool m_cocos;
    std::vector<std::byte> m_bytes;
    PatchRange m_range;

    virtual operator JSON() override;

    virtual void apply() override;
    virtual void revert() override;
private:
    LPVOID m_realAddress;
    std::vector<std::byte> m_original;

    SubPatch(const bool valid);
};