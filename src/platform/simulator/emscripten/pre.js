Module = {};

Module.onRuntimeInitialized = function() {
    postMessage(0);
}

Module.print = function (args) {
    console.log(args);
}

const WIDTH = 480;
const HEIGHT = 272;

onmessage = function (e) {
    if (e.data.wheel.deltaY != 0 || e.data.wheel.clicked != 0) {
        Module._onMouseWheelEvent(e.data.wheel.deltaY, e.data.wheel.clicked);
    }
    
    for (let i = 0; i < e.data.pointerEvents.length; i++) {
        const pointerEvent = e.data.pointerEvents[i];
        Module._onPointerEvent(pointerEvent.x, pointerEvent.y, pointerEvent.pressed);
    }

    Module._mainLoop();

    var buf_addr = Module._getSyncedBuffer();
    if (buf_addr != 0) {
        var uint8ClampedArray = new Uint8ClampedArray(Module.HEAPU8.subarray(buf_addr, buf_addr + WIDTH * HEIGHT * 4));
        postMessage({
            screen: uint8ClampedArray
        });
    } else {
        postMessage(0);
    }
}
