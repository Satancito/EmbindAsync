& "$Env:EMSCRIPTEN_DIR/upstream\emscripten/em++.bat" `
main.cpp `
-I ./ `
-o EmbindAsync.js `
-std=c++17 `
--bind `
-s WASM=1 `
-s DISABLE_EXCEPTION_CATCHING=0 `
-s USE_WEBGPU=1 `
-s SINGLE_FILE=1 `
-s ASYNCIFY=1 `
-s VERBOSE=0 `
-O2 `
-s EXPORT_NAME=`'CreateModuleInstance`' `
-s MODULARIZE=1 `
-s EXPORTED_FUNCTIONS=[`'_main`'] `
--extern-post-js "ExternPost.js" `

