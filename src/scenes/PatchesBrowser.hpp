#pragma once

#include "../includes.hpp"
#include "../objects/PatchStorage.hpp"
#include "../lists/views/PatchesListView.hpp"

struct PatchesBrowser : public GJDropDownLayer {
    static PatchesBrowser* create();
protected:
    virtual bool init() override;
    virtual void customSetup() override;
};