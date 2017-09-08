cmake_minimum_required(VERSION 3.8)
project(ColdViewer)

set(CMAKE_CXX_STANDARD 11)

set(SOURCE_FILES src/main.cpp)

set(SDL2_INCLUDE_DIR /usr/include/SDL2)
set(SDL2_LIBRARY /usr/lib/x86_64-linux-gnu/libSDL2.so)
set(SDL2_LIBRARY_ttf /usr/lib/x86_64-linux-gnu/libSDL2_ttf.so)
set(SDL2_LIBRARY_image /usr/lib/x86_64-linux-gnu/libSDL2_image.so)
include_directories(src/hdr)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ..)

add_executable(ColdViewer.bin
        src/texture.cpp
        src/main.cpp
        src/hdr/texture.h
        )

target_link_libraries(ColdViewer.bin
        ${SDL2_LIBRARY}
        ${SDL2_LIBRARY_image}
        ${SDL2_LIBRARY_ttf}
        m)