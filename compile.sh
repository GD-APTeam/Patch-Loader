if [ ! -d "build" ]; then
    mkdir build;
    cmake -G "Visual Studio 16 2019" -B build -DCMAKE_BUILD_TYPE=Release -T host=x86 -A win32;
fi

cmake --build build --config Release --target ALL_BUILD;