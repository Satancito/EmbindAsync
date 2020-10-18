#include <InsaneEmscripten.h>
#include <string>
/* EXAMPLE ASYNC FUNCTION*/
//     Taken from https://emscripten.org/docs/porting/asyncify.html#returning-values
//     const text = UTF8ToString(str);
//     const encoder = new TextEncoder();//1
//     const data = encoder.encode(text);//2
//     out("ask for digest for " + text); //3
//     const digestValue = await window.crypto.subtle.digest("SHA-256", data); //4
//     out("got digest of length " + digestValue.byteLength); //5
//     var base64 = btoa(String.fromCharCode.apply(null, new Uint8Array(digestValue)));//6
//     return base64;//7

/* Get undefined immediately in Js, if is called from JS. While the function process continues running.  
    If it called from CPP runs normally.
*/
emscripten::val GetBase64Sha256Normal(const String &text)
{
    USING_EMSCRIPTEN;
    USING_INSANE_EMSCRIPTEN;

    val encoder = val::global()[u8"TextEncoder"].new_();                                                                                                                            //1
    val data = encoder.call<val>(u8"encode", val(text));                                                                                                                            //2
    Console::Log(u8"ask for digest for "s, text);                                                                                                                                   //3
    val digestValue = val::global()[u8"crypto"][u8"subtle"].call<val>(u8"digest", val(u8"SHA-256"), data).await();                                                                  //4
    Console::Log(u8"got digest of length "s, digestValue[u8"byteLength"]);                                                                                                          //5
    val base64 = val::global().call<val>(u8"btoa", val::global()[u8"String"][u8"fromCharCode"].call<val>(u8"apply", val::null(), val::global()[u8"Uint8Array"].new_(digestValue))); //6
    return base64;                                                                                                                                                                  //7
}

/* Returns a promise. Value can be unwrapped using await from Js. 
    EMSCRIPTEN_VAL_FUNCTOR_TYPE(arity) represents a js callback.
    EMSCRIPTEN_VAL_FUNCTOR_TYPE(1) = In C++ std::function<val(val)> / In Js function(value) / In Js using lambda (value)=> 
    where 1 represents the arity, the arity is the number of paramaters of function.
    Example EMSCRIPTEN_VAL_FUNCTOR_TYPE(5) = In C++ std::function<val(val, val, val, val, val)> / In Js function (value1, value2, value3, value4, value5)
*/

emscripten::val GetBase64Sha256Async(const String &text)
{
    USING_EMSCRIPTEN;
    USING_INSANE_EMSCRIPTEN;

    EMSCRIPTEN_VAL_FUNCTOR_TYPE(1)
    callback = [](val digestValue) -> val {
        Console::Log(u8"got digest of length "s, digestValue[u8"byteLength"]);                                                                                                          //5
        val base64 = val::global().call<val>(u8"btoa", val::global()[u8"String"][u8"fromCharCode"].call<val>(u8"apply", val::null(), val::global()[u8"Uint8Array"].new_(digestValue))); //6
        return base64;                                                                                                                                                                  //7
    };

    val encoder = val::global()[u8"TextEncoder"].new_();                                                                                //1
    val data = encoder.call<val>(u8"encode", val(text));                                                                                //2
    Console::Log(u8"ask for digest for "s, text);                                                                                       //3
    return val::global()[u8"crypto"][u8"subtle"].call<val>(u8"digest", val(u8"SHA-256"), data).call<val>(u8"then", Js::Bind(callback)); //4
}

int main()
{
    USING_EMSCRIPTEN;
    USING_INSANE_EMSCRIPTEN;
    Console::Log("Module instance created."s);
}

EMSCRIPTEN_BINDINGS(exports)
{
    USING_EMSCRIPTEN;
    /*

    class_<std::function<void(emscripten::val)>>("VoidValFunctor")
    .constructor<>()
    .function("opcall", &std::function<void(emscripten::val)>::operator());
    Class with opcall function, here std::function call operator from C++ is bound to function opcall() in JS.

   EMSCRIPTEN_EXPORT_ALL_VAL_FUNCTORS(arity)
   EMSCRIPTEN_EXPORT_ALL_VAL_FUNCTORS(3) Generates 3 clases with every class with a respective functor call operator bound to opcall.
   
   class_<std::function<emscripten::val(emscripten::val)>>("VoidValFunctor1")
    .constructor<>()
    .function("opcall", &std::function<emscripten::val(emscripten::val)>::operator());

   class_<std::function<emscripten::val(emscripten::val, emscripten::val)>>("VoidValFunctor2")
    .constructor<>()
    .function("opcall", &std::function<emscripten::val(emscripten::val, emscripten::val)>::operator());

   class_<std::function<emscripten::val(emscripten::val, emscripten::val, emscripten::val)>>("VoidValFunctor3")
    .constructor<>()
    .function("opcall", &std::function<emscripten::val(emscripten::val, emscripten::val, emscripten::val)>::operator());
   */
    EMSCRIPTEN_EXPORT_ALL_VAL_FUNCTORS(5);

    function<val>(u8"GetBase64Sha256Normal", &GetBase64Sha256Normal);
    function<val>(u8"GetBase64Sha256Async", &GetBase64Sha256Async);
}