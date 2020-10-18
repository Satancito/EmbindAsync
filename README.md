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
You can install PowerShell Core on Windows, Linux, MacOS

## **3. Run Compile.ps1**

```PS> ./Compile.ps1```

Compile.ps1 compiles all sources into a **EmbindExtensions.js** that must be added in main page **index.html**

## **4. Run in your browser**
```PS> ./Run.ps1```