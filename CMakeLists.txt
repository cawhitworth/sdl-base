cmake_minimum_required(VERSION 3.21)

project(sdl-base LANGUAGES CXX)

find_package(SDL2 REQUIRED)
find_package(SDL2_image REQUIRED)

add_executable(sdl-base
    src/main.cpp

    src/sdl/SDLWrapper.cpp
    src/sdl/SDLRenderer.cpp
    src/sdl/SDLSurface.cpp
    src/sdl/SDLTexture.cpp

    src/utils/FPS.cpp
    src/utils/PngLoader.cpp
    src/utils/TextRenderer.cpp
    
    src/yarl/Yarl.cpp
    src/yarl/Imp.cpp
    src/yarl/ImpRenderer.cpp
    src/yarl/Map.cpp
    src/yarl/MapRenderer.cpp
)

target_include_directories(sdl-base PRIVATE 
    src
    src/sdl
    src/utils
    src/yarl
    )

target_link_libraries(sdl-base PRIVATE
    SDL2::SDL2
    SDL2::SDL2main
    SDL2_image::SDL2_image
)

add_custom_command(TARGET sdl-base POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory
        "${PROJECT_SOURCE_DIR}/images"
        $<TARGET_FILE_DIR:sdl-base>/images
)

if(WIN32)
    add_custom_command(TARGET sdl-base POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy $<TARGET_RUNTIME_DLLS:sdl-base> $<TARGET_FILE_DIR:sdl-base>
        COMMAND_EXPAND_LISTS
    )
endif()