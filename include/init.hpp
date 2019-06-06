#pragma once

#ifdef _WIN32
    #include <windows.h>
#endif
#define _USE_MATH_DEFINES
#include <cmath>
#include <SDL2/SDL.h>
#include <glad/glad.h>
#include <stdlib.h>
#include <stdio.h>

#include "constants.hpp"

namespace imac {
SDL_Window* init() {
    /* Init SDL */
    if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO | SDL_INIT_TIMER) != 0) {
        printf("[SDL2] Unable to initialize SDL: %s", SDL_GetError());
        return nullptr;
    }

    /* Init OpenGL */
    SDL_GL_LoadLibrary(NULL);
    SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 16);
    SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
    SDL_SetHint(SDL_HINT_RENDER_DRIVER, "opengl");
    SDL_GL_SetSwapInterval(1);

    /* Create Window */
    SDL_Window* window = SDL_CreateWindow(
        "Imac tower defense",
        SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
        WINDOW_WIDTH, WINDOW_HEIGHT,
        SDL_WINDOW_OPENGL);
    if (window == nullptr) {
        printf("[SDL2] Window is null: %s", SDL_GetError());
        return nullptr;
    }

    /* Create OpenGl context */
    SDL_GLContext context = SDL_GL_CreateContext(window);
    if (context == nullptr) {
        printf("[SDL2] OpenGL context is null: %s", SDL_GetError());
        return nullptr;
    }

    /* Init Glad once the OpenGL context is valid */
    if (!gladLoadGLLoader(SDL_GL_GetProcAddress)) {
        printf("[Glad] Glad not init");
        return nullptr;
    }
    
    return window;
}
}
