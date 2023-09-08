cmake_minimum_required(VERSION 3.21)

project(YarlPP LANGUAGES CXX)

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

add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory
        "${PROJECT_SOURCE_DIR}/images"
        $<TARGET_FILE_DIR:YarlPP>/images
)

if(WIN32)
    add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy $<TARGET_RUNTIME_DLLS:YarlPP> $<TARGET_FILE_DIR:YarlPP>
        COMMAND_EXPAND_LISTS
    )
endif()