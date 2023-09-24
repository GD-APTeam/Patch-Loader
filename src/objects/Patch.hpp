#pragma once

#include "SubPatch.hpp"
#include "BasePatch.hpp"
#include "../includes.hpp"

struct Patch : public CCObject, public BasePatch {
    static Patch get(const JSON& object);

    std::string m_name;
    std::string m_description;
    std::vector<SubPatch> m_patches;
    bool m_restart;
    bool m_enabled;

    virtual void apply() override;
    virtual void revert() override;
    virtual JSON toJson() override;
private:
    Patch(const bool valid);
};