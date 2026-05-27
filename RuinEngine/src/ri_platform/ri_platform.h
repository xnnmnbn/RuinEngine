#ifndef RI_PLATFORM_H
#define RI_PLATFORM_H

#include <SDL3/SDL_video.h>
#ifdef __cplusplus
extern "C" {
#endif

#include <stdint.h>
#include <SDL3/SDL.h>


typedef struct RI_Window {
    SDL_Window *window;
    int32_t     width;
    int32_t     height;
    const char *title;
    uint8_t     running;
    uint8_t     resized;
} RI_Window;

typedef struct RI_Time {
    float    delta;
    float    fixed_delta;
    float    elapsed;
    float    fixed_elapsed;
    float    speed;
    float    target_delta;
    uint8_t  fps;
    uint64_t freq;
    uint64_t now;
    uint64_t was;
} RI_Time;

typedef struct RI_Input {
    uint8_t *keys_now;
    uint8_t *keys_was;
    uint8_t *mouse_now;
    uint8_t *mouse_was;
    float    mouse_x;
    float    mouse_y;
    float    mouse_dx;
    float    mouse_dy;
    float    mouse_scroll;
} RI_Input;

typedef struct RI_Platform {
    RI_Window window;
    RI_Time   time;
    RI_Input  input;
} RI_Platform;


uint8_t ri_window_init();
uint8_t ri_window_create(RI_Platform *p, int32_t w, int32_t h, const char *title);
uint8_t ri_window_running(RI_Platform *p);
void    ri_window_kill(RI_Platform *p);

void ri_input_init(RI_Platform *p);
void ri_input_update(RI_Platform *p);
void ri_input_kill(RI_Platform *p);

void ri_time_init(RI_Platform *p);
void ri_time_update(RI_Platform *p);

void ri__platform_init(RI_Platform *p);
void ri__platform_kill(RI_Platform *p);

#ifdef __cplusplus
}
#endif

#endif
