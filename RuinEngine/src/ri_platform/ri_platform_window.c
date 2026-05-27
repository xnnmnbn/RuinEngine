#include "ri_platform.h"
#include <SDL3/SDL_error.h>
#include <SDL3/SDL_gpu.h>
#include <SDL3/SDL_oldnames.h>
#include <SDL3/SDL_video.h>
#include <stdint.h>
#include <stdio.h>


uint8_t ri_window_init() {
    if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_EVENTS) == 0) {
        printf("Failed to init SDL3 window.\n");
        return 0;
    }

    return 1;
}

uint8_t ri_window_create(RI_Platform *p, int32_t w, int32_t h, const char *title) {    
    p->window.window = SDL_CreateWindow(title, w, h, SDL_WINDOW_VULKAN | SDL_WINDOW_RESIZABLE);

    //printf("%p\n", p->window.window);

    if (!p->window.window) {
        printf("Failed to create window.\n");
        printf("%s\n", SDL_GetError());
        return 0;
    }
    
    p->window.title = title;
    p->window.width = w;
    p->window.height = h;
    p->window.running = 1;

    printf("Window created.\n");

    return 1;
}

uint8_t ri_window_running(RI_Platform *p) {
    p->input.mouse_x      = 0.0;
    p->input.mouse_y      = 0.0;
    p->input.mouse_dx     = 0.0;
    p->input.mouse_dy     = 0.0;
    p->input.mouse_scroll = 0.0;
    
    SDL_Event event;

    while (SDL_PollEvent(&event)) {
        switch (event.type) {
            case SDL_EVENT_QUIT:
                p->window.running = 0;
                break;

            case SDL_EVENT_MOUSE_WHEEL:
                p->input.mouse_scroll = event.wheel.y;
                break;

            case SDL_EVENT_WINDOW_RESIZED:
                printf("RESIZED\n");
                p->window.resized = 1;
                SDL_GetWindowSize(p->window.window, &p->window.width, &p->window.height);
        }
    }

    const bool *keys = SDL_GetKeyboardState(NULL);
    SDL_MouseButtonFlags flags = SDL_GetMouseState(&p->input.mouse_x, &p->input.mouse_y);

    for (size_t i = 0; i< SDL_SCANCODE_COUNT; i++) {
        p->input.keys_was[i] = p->input.keys_now[i];
        p->input.keys_now[i] = keys[i];
    }

    for (size_t i = 0; i < 5; i++) {
        p->input.mouse_was[i] = p->input.mouse_now[i];
        p->input.mouse_now[i] = (uint8_t)((flags >> i) & 1);
    }

    

    return p->window.running;
}


void  ri_window_kill(RI_Platform *p) {
    SDL_DestroyWindow(p->window.window);
}

