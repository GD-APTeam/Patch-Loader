#pragma once

#include "../includes.hpp"

struct BasePatch {
    bool m_isValid;

    virtual void apply() = 0;
    virtual void revert() = 0;
    virtual json toJson() = 0;
protected:
    BasePatch(const bool valid);
};