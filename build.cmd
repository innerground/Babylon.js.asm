call emcc -s EXPORT_NAME="'BABYLON.ASM'" bablylon.math.c -s WASM=1 -o bablylon.math.html 
call emrun --no_browser --port 8080 .