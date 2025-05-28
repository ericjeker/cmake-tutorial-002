if (-not (Test-Path -Path "build")) {
    mkdir build
}

cmake -S . -B .\build\ -G "Ninja" -DCMAKE_C_COMPILER=gcc -DCMAKE_CXX_COMPILER=G++;

ninja -C .\build\;
