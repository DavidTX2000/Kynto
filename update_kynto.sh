#!/bin/bash
echo "[SYSTEM]: Organizando Kynto Engine..."
export LD_LIBRARY_PATH=$LD_LIBRARY_PATH:.

# Compila tudo usando o Makefile
make clean
make

# Adiciona ao Git
git add include/ Makefile src/ modules/ scripts/
git commit -m "Arch: Migrated to modular architecture with centralized headers"
git push origin main

echo "[SUCCESS]: Kynto Engine updated and modularized!"
