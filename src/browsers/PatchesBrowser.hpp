#pragma once

#include "../includes.hpp"

struct PatchesBrowser : public GJDropDownLayer {
    static PatchesBrowser* create();
protected:
    bool init();
    void customSetup() override;
};