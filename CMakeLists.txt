cmake_minimum_required(VERSION 3.11)

project(YarlPP LANGUAGES CXX)

set(SDL2_DIR "C:/sdl2/sdl2/cmake")
set(SDL2_image_DIR "C:/sdl2/sdl2_image/cmake")

find_package(SDL2 REQUIRED)
find_package(SDL2_image REQUIRED)

add_executable(${PROJECT_NAME}
    yarl/main.cpp
    yarl/SDLWrapper.cpp
    yarl/SDLRenderer.cpp
    yarl/SDLSurface.cpp
    yarl/SDLTexture.cpp

    yarl/FPS.cpp
    yarl/Imp.cpp
    yarl/ImpRenderer.cpp
    yarl/Map.cpp
    yarl/MapRenderer.cpp
    yarl/PngLoader.cpp
    yarl/TextRenderer.cpp
)

target_link_libraries(${PROJECT_NAME} PUBLIC
    SDL2::SDL2
    SDL2::SDL2main
    SDL2_image::SDL2_image
)
