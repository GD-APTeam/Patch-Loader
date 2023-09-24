#pragma once

#include "../includes.hpp"

struct BasePatch {
    static HANDLE m_hProcess;

    bool m_isValid;

    virtual void apply() = 0;
    virtual void revert() = 0;
    virtual JSON toJson() = 0;
protected:
    BasePatch(const bool valid);
};