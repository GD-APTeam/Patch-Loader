#pragma once

#include "BasePatch.hpp"
#include "../includes.hpp"
#include "../utils/converters.hpp"

struct PatchRange : public BasePatch {
    static PatchRange get(const JSON& object);

    int m_start;
    int m_end;
    size_t m_size;

    virtual operator JSON() override;

    PatchRange();
    void apply(const LPVOID address, const int value);
    virtual void apply() override;
    virtual void revert() override;
private:
    PatchRange(const bool valid);
};