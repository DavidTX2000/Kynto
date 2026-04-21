#!/bin/bash
clear
echo -e "\033[1;34m[1/3] cleaning ...\033[0m"
rm -f kynto *.so

echo -e "\033[1;34m[2/3] Compiling ...\033[0m"
clang src/ckynto.c -o kynto -ldl -rdynamic -I./include -O3

echo -e "\033[1;34m[3/3] Compiling modules...\033[0m"
for f in modules/*.c; do
    mod_name=$(basename "$f" .c)
    echo "  -> Compiling $mod_name..."
    clang -shared -fPIC "$f" -o "$mod_name.so"
done

if [ -f "./kynto" ]; then
    echo -e "\033[1;32m\n[SUCCESS]: Kynto Engine it's read!\033[0m"
else
    echo -e "\033[1;31m\n[ERROR]: Error in Core Compilation .\033[0m"
fi
