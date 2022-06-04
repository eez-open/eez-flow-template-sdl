#include <eez/gui/gui.h>
#include <eez/gui/thread.h>

#ifdef __EMSCRIPTEN__
void startEmscripten();
#endif

uint32_t DISPLAY_WIDTH = 480;
uint32_t DISPLAY_HEIGHT = 272;

void init() {
    eez::initAssetsMemory();
    eez::gui::loadMainAssets(eez::gui::assets, sizeof(eez::gui::assets));
    DISPLAY_WIDTH = eez::gui::g_mainAssets->settings->displayWidth;
    DISPLAY_HEIGHT = eez::gui::g_mainAssets->settings->displayHeight;
    eez::initOtherMemory();
    eez::initAllocHeap(eez::ALLOC_BUFFER, eez::ALLOC_BUFFER_SIZE);

    eez::gui::display::turnOn();
    eez::gui::startThread();
}

int main() {
#ifdef __EMSCRIPTEN__
    startEmscripten();
#else
    init();

    while (!eez::g_shutdown) {
        osDelay(1);
    }
#endif
}

#ifdef __EMSCRIPTEN__
#include <stdio.h>
#include <emscripten.h>

extern void eez_system_tick();

static int g_initialized = false;

// clang-format off
void mountFileSystem() {
    EM_ASM(
        FS.mkdir("/eez-flow-template-sdl");
        FS.mount(IDBFS, {}, "/eez-flow-template-sdl");

        //Module.print("start file sync..");

        //flag to check when data are synchronized
        Module.syncdone = 0;

        FS.syncfs(true, function(err) {
            assert(!err);
            //Module.print("end file sync..");
            Module.syncdone = 1;
        });
    , 0);
}
// clang-format on

EM_PORT_API(void) mainLoop() {
    if (emscripten_run_script_int("Module.syncdone") == 1) {
        if (!g_initialized) {
            g_initialized = true;
            init();
        } else {
            eez_system_tick();

            // clang-format off
            EM_ASM(
                if (Module.syncdone) {
                    //Module.print("Start File sync..");
                    Module.syncdone = 0;

                    FS.syncfs(false, function(err) {
                        assert(!err);
                        //Module.print("End File sync..");
                        Module.syncdone = 1;
                    });
                }
            , 0);
            // clang-format on
        }
    }
}

void startEmscripten() {
    mountFileSystem();
}
#endif