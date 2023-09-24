#include <geode.custom-keybinds/include/Keybinds.hpp>

#include "includes.hpp"
#include "scenes/PatchesBrowser.hpp"

$execute {
    using namespace keybinds;

    #ifdef SHOW_CONSOLE
        if (AllocConsole()) {
            freopen_s(reinterpret_cast<FILE**>(stdout), "CONOUT$", "w", stdout);
            freopen_s(reinterpret_cast<FILE**>(stdin), "CONIN$", "r", stdin);
        }
    #endif

    BindManager::get()->registerBindable({
        "open-menu"_spr,
        "Open menu",
        "Opens the Patch Loader menu with all installed patches to quickly toggle them.",
        { Keybind::create(KEY_M) },
        "Patch Loader"
    });

    new geode::EventListener([=](InvokeBindEvent* event) {
        if (event->isDown()) {
            PatchesBrowser::popup();
        }

        return geode::ListenerResult::Propagate;
    }, InvokeBindFilter(nullptr, "open-menu"_spr));
}