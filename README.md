*Instructions for Windows
*EMSDK_HOME is the full path where EMSDK will be cloned
*BABYLON_JS_ASM_HOME_ is the full path where the code will be cloned


# Install emscripten :

```
git clone https://github.com/juj/emsdk %EMSDK_HOME%
cd emsdk
emsdk install latest
emsdk activate latest
```


# Build the code :

```
git https://github.com/innerground/Babylon.js.asm.git %BABYLON_JS_ASM_HOME%
cd %BABYLON_JS_ASM_HOME%
%EMSDK_HOME%\emsdk_env.bat
build.cmd
```




