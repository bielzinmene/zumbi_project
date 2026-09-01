#if !defined(_WIN32) && !defined(__linux__)
#error "Unknown compiler"
#endif

// base
#ifdef INCLUDE_SDL
    #include <SDL2/SDL.h>
    #undef INCLUDE_SDL
#endif

// image
#ifdef INCLUDE_SDL_IMAGE
    #include <SDL2/SDL_image.h>
    #undef INCLUDE_SDL_IMAGE
#endif

// mixer
#ifdef INCLUDE_SDL_MIXER
    #include <SDL2/SDL_mixer.h>
    #undef INCLUDE_SDL_MIXER
#endif

// TTF
#ifdef INCLUDE_SDL_TTF
    #include <SDL2/SDL_ttf.h>
    #undef INCLUDE_SDL_TTF
#endif