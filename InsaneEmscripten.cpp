#include <InsaneEmscripten.h>

emscripten::val Insane::Emscripten::Promise::Resolve(const emscripten::val & value)
{
    USING_EMSCRIPTEN;
    return val::global()[u8"Promise"].call<val>(u8"resolve", value);
}

emscripten::val Insane::Emscripten::Promise::Reject(const emscripten::val & value)
{
    USING_EMSCRIPTEN;
    return val::global()[u8"Promise"].call<val>(u8"reject", value);
}

emscripten::val Insane::Emscripten::Js::Bind(const emscripten::val &fx)
{
    USING_EMSCRIPTEN;
    return fx["opcall"].call<val>("bind", fx);
}