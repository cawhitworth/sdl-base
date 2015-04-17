# yarlpp
YARL++ - Yet Another RogueLike in C++11

Obviously, not finished. Written during down-tools week at work to help me better get my head round some of the new stuff in C++11. Move semantics FTW.

Should build on Windows and Linux.

Windows version is 32-bit only and expects to find SDL2-2.0.3 and SDL2_image-2.0.0 in ````C:\lib````. It builds in VS2013, I've not tried anything else.

Linux version requires Clang with C++1y support, libc++, lidsdl2 and libsdl2_image. See your friendly package manager for futher details.
