#pragma once

#include "BasePatch.hpp"
#include "../includes.hpp"
#include "../utils/converters.hpp"

struct PatchRange : public BasePatch {
    static PatchRange get(const JSON& object);

    int m_start;
    int m_end;
    size_t m_size;
    int m_value;

    virtual operator JSON() override;

    PatchRange();
    virtual void apply() override;
    void apply(const int value);
    int percentageToRangeValue(const float percentage);
private:
    LPVOID m_address;

    PatchRange(const bool valid);
};