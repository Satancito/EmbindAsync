# **Emscripten - Embind Async**
Call C++ function that use await operator from Javascript

Steps to configure

## **1. Emsdk location**
Create a environment variable named as **EMSCRIPTEN_DIR** with the location of emsdk folder.   
Example on my pc, get enviroment variable value.

```
PS> Write-Host $env:EMSCRIPTEN_DIR
I:\WebAssembly\emsdk
PS>
```

## **2. Install PowerShell Core**
You can install PowerShell Core on **Windows**, **Linux**, **MacOS**

## **3. Run Compile.ps1**

```PS> ./Compile.ps1```

Compile.ps1 compiles all sources into a **EmbindAsync.js** that must be added in main page **index.html**

## **4. Run in your browser**
```PS> ./Run.ps1```   


# **References**
[Embind](https://emscripten.org/docs/porting/connecting_cpp_and_javascript/embind.html)

[Passing a C++ function to a javascript function in emscripten](https://stackoverflow.com/a/41656079/3158594)

[Damien Buhl - daminetreg - js::bind](https://github.com/daminetreg/js-bind)

[Satancito - InsaneCpp](https://github.com/Satancito/InsaneCpp)

[Emscripten - Asyncify returning values](https://emscripten.org/docs/porting/asyncify.html#returning-values)

[Powershell Core](https://github.com/PowerShell/PowerShell)
