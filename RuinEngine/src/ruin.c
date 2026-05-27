#include "ruin.h"
#include "cvec.h"
#include "ri_platform/ri_platform.h"
#include "ri_renderer/ri_renderer.h"
#include "ruin__internal.h"
#include <SDL3/SDL_init.h>
#include <SDL3/SDL_scancode.h>
#include <SDL3/SDL_timer.h>
#include <SDL3/SDL_audio.h>
#include <corecrt.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

static RuinInternal engine = {0};


RBool ri_init(RuinInternal *engine) {
    
    ri__platform_init(&engine->platform);

    engine->entities.next_entity_id = 1;
    engine->entities.dense_entities = (cvec){0};

    engine->components = (RI_Components){0};
    engine->components.transforms.sparse_data      = malloc(RUIN_MAX_ENTITIES * sizeof(RTransform));
    engine->components.renderer_2ds.sparse_data    = malloc(RUIN_MAX_ENTITIES * sizeof(RSpriteRenderer));
    engine->components.renderer_3ds.sparse_data    = malloc(RUIN_MAX_ENTITIES * sizeof(RMeshRenderer));
    engine->components.sound_players.sparse_data   = malloc(RUIN_MAX_ENTITIES * sizeof(RSoundPlayer));
    engine->components.music_players.sparse_data   = malloc(RUIN_MAX_ENTITIES * sizeof(RMusicPlayer));
    engine->components.sound_listeners.sparse_data = malloc(RUIN_MAX_ENTITIES * sizeof(RSoundListener));
    engine->components.camera_2ds.sparse_data      = malloc(RUIN_MAX_ENTITIES * sizeof(RCamera2D));
    engine->components.camera_3ds.sparse_data      = malloc(RUIN_MAX_ENTITIES * sizeof(RCamera3D));


    ri_comp_transform_init(engine);

    return 1;
}

void ri_kill(RuinInternal *engine) {
    ri__renderer_kill(&engine->renderer);
    ri__platform_kill(&engine->platform);

    free(engine->components.transforms.sparse_data);
    free(engine->components.renderer_2ds.sparse_data);
    free(engine->components.renderer_3ds.sparse_data);
    free(engine->components.sound_players.sparse_data);
    free(engine->components.music_players.sparse_data);
    free(engine->components.sound_listeners.sparse_data);
    free(engine->components.camera_2ds.sparse_data);
    free(engine->components.camera_3ds.sparse_data);

    ri_comp_transform_kill(engine);
}


RBool ruinInit(void) {
    ri_init(&engine);

    return 1;
}

RBool ruinKill(void) {
    ri_kill(&engine);

    return 1;
}

RBool ruinWindowCreate(int32_t w, int32_t h, const char *title) {
    if (!ri_window_create(&engine.platform, w, h, title)) {
        return 0;
    }

    ri_renderer_init(&engine.renderer, &engine.platform);
    
    return 1;
}

RBool ruinWindowRunning() {
    return ri_window_running(&engine.platform);
}



void ruinFrameBegin() {
    ri_time_update(&engine.platform);
}

void ruinFrameEnd() {

    engine.platform.window.resized = 0;

    ri_comp_transform_update(&engine);
/*
    double remaining = engine.platform.time.target_delta - engine.platform.time.fixed_delta;
    uint64_t del = (uint64_t)(remaining * 100000000);

    if (remaining > 0) {
        SDL_DelayPrecise(del);
    }
*/

    if (engine.platform.window.resized) {

        if (engine.platform.window.width == 0 || engine.platform.window.height == 0) {
            printf("%d, %d\n", engine.platform.window.width, engine.platform.window.height);
            return;
        }
        ri_renderer_recreate_swapchain(&engine.renderer, &engine.platform);
        engine.platform.window.resized = 0;
        return;
    }

    if (engine.platform.window.width == 0 || engine.platform.window.height == 0) {
        return;
    }

    draw_frame(&engine.renderer, &engine.platform);

    engine.platform.window.resized = 0;

}


RBool ruinKeyDown(RKey k) {
    return ( engine.platform.input.keys_now[k]) &&
           (!engine.platform.input.keys_was[k]);
}
RBool ruinKeyHold(RKey k) {
    return engine.platform.input.keys_now[k];
}
RBool ruinKeyUp(RKey k) {
    return ( engine.platform.input.keys_was[k]) &&
           (!engine.platform.input.keys_now[k]);
}

RBool ruinMouseDown(RMouseButton b) {
    return ( engine.platform.input.mouse_now[b - 1]) &&
           (!engine.platform.input.mouse_was[b - 1]);
}
RBool ruinMouseHold(RMouseButton b) {
    return engine.platform.input.mouse_now[b - 1];
}
RBool ruinMouseUp(RMouseButton b) {
    return ( engine.platform.input.mouse_was[b - 1]) &&
           (!engine.platform.input.mouse_now[b - 1]);
}

float ruinMouseScroll() {
    return engine.platform.input.mouse_scroll;
}


uint8_t ruinTimeFPS() {
    return engine.platform.time.fps;
}
float ruinTimeDelta() {
    return engine.platform.time.delta;
}
float ruinTimeDeltaFixed() {
    return engine.platform.time.fixed_delta;
}
float ruinTimeElapsed() {
    return engine.platform.time.elapsed;
}
float ruinTimeElapsedFixed() {
    return engine.platform.time.fixed_elapsed;
}
void ruinTimeSetSpeed(float s) {
    engine.platform.time.speed = s;
}
void ruinTimeSetTargetFPS(uint8_t t) {
    if (t == 0) {
        engine.platform.time.target_delta = 0;
        return;
    }

    engine.platform.time.target_delta = 1.0 / (float)t;
}

REntityID ruinEntityCreate() {
    cvec_push(engine.entities.dense_entities, engine.entities.next_entity_id, REntityID);
    engine.entities.next_entity_id += 1;

    return engine.entities.next_entity_id - 1;
}

void ruinEntityKill(REntityID e) {
    cvec_remove(engine.entities.dense_entities, e, REntityID);
}

RBool ruinEntityValid(REntityID e) {
    REntityID id = RUIN_INVALID_ID;
    cvec_index(engine.entities.dense_entities, e, REntityID, id);

    return id;
}


RTransform ruinDefaultTransform() {
    return (RTransform){
        .position = {0},
        .rotation = {0},
        .scale    = { 1.0f, 1.0f, 1.0f },
        .parent   = 0,
        .dirty    = 0
    };
}

void ruinEntityTransformAdd(REntityID e, RTransform t) {
   ((RTransform*)engine.components.transforms.sparse_data)[e] = t;
   cvec_push(engine.components.transforms.dense_indices, e, REntityID);
}
void ruinEntityTransformKill(REntityID e) {
    cvec_remove_at(engine.components.transforms.dense_indices, e, REntityID);
}
RTransform *ruinEntityTransformGet(REntityID e) {
#ifdef RUIN_ENABLE_DEBUG
    REntityID id = (REntityID)-1;
    cvec_index(engine.entities.dense_entities, e, REntityID, id);

    if (id == (REntityID)-1) {
        RUIN_DEBUG("Failed to get RTansform of Entity #%d", e);
        return NULL;
    }
#endif
    
    return &(void_t(engine.components.transforms.sparse_data, RTransform)[e]);
}
RVec3 ruinEntityTransformGetWorldPosition(REntityID e) {
    vec3 *v = &(engine.component_internals.transform_internal.sparse_world_positions[e]);

    RUIN_DEBUG("addr: %p", v);

    return (RVec3){
        .x = (*v)[0],
        .y = (*v)[1],
        .z = (*v)[2]
    };
}
RVec3 ruinEntityTransformGetWorldRotation(REntityID e) {
    vec3 *v = &(engine.component_internals.transform_internal.sparse_world_rotations[e]);

    return (RVec3){
        .x = (*v)[0],
        .y = (*v)[1],
        .z = (*v)[2]
    };
}
RVec3 ruinEntityTransformGetWorldScale(REntityID e) {
    vec3 *v = &(engine.component_internals.transform_internal.sparse_world_scales[e]);

    return (RVec3){
        .x = (*v)[0],
        .y = (*v)[1],
        .z = (*v)[2]
    };
}








