# yarlpp
YARL++ - Yet Another RogueLike in C++11

Obviously, not even nearly finished.

![Screenshot](https://raw.githubusercontent.com/cawhitworth/yarlpp/master/images/screenshot.png)

Written during down-tools week at work to help me better get my head round some
of the new stuff in C++11: essentially, I've written move-semantic friendly
wrappers around the SDL functions, which means that most of the actual "game"
code is pointer-free - there are no `new` or `delete` calls in the code.

Builds with CMake; needs SDL2 and SDL_image - if building on Windows, update the relevant paths in CMakePresets.json