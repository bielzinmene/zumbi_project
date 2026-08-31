#ifndef SDL_INCLUDE_H
#define SDL_INCLUDE_H

#define SDL_MAIN_HANDLED

#if defined(_WIN32) || defined(_WIN64)
    #include <SDL2/SDL.h>
    #include <SDL2/SDL_image.h>
    #include <SDL2/SDL_mixer.h>
#elif defined(__APPLE__)
    #include <SDL.h>
    #include <SDL_image.h>
    #include <SDL_mixer.h>
#else
    #include <SDL2/SDL.h>
    #include <SDL2/SDL_image.h>
    #include <SDL2/SDL_mixer.h>
#endif

#endif // sdl_include_h