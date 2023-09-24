#pragma once

#include "../includes.hpp"
#include "../objects/PatchStorage.hpp"
#include "../lists/views/PatchesListView.hpp"

struct PatchesBrowser : public GJDropDownLayer {
    static bool isOpen;

    static void scene();
protected:
    virtual void customSetup() override;
    virtual void exitLayer(CCObject* sender) override;
};