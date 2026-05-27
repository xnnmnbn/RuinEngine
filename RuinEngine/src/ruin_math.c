#include "ruin.h"
#include "math.h"


RVec2 ruinVec2(float x, float y) {
    return (RVec2){
        .x = x,
        .y = y
    };
}
RVec3 ruinVec3(float x, float y, float z) {
    return (RVec3){
        .x = x,
        .y = y,
        .z = z
    };
}
RVec4 ruinVec4(float x, float y, float z, float w) {
    return (RVec4){
        .x = x,
        .y = y,
        .z = z,
        .w = w
    };
}


RVec2 ruinVec2Sum(const RVec2 *a, const RVec2 *b) {
    return (RVec2){
        .x = a->x + b->x,
        .y = a->y + b->y
    };
}
RVec2 ruinVec2Sub(const RVec2 *a, const RVec2 *b) {
    return (RVec2){
        .x = a->x - b->x,
        .y = a->y - b->y
    };
}
RVec2 ruinVec2Mul(const RVec2 *a, float f) {
    return (RVec2){
        .x = a->x * f,
        .y = a->y * f
    };
}
RVec2 ruinVec2Div(const RVec2 *a, float f) {
    return (RVec2){
        .x = a->x / f,
        .y = a->y / f
    };
}

float ruinVec2Mag(const RVec2 *v) {
    return sqrtf(v->x * v->x + v->y * v->y);
}
RVec2 ruinVec2Nor(const RVec2 *v) {
    const float m = ruinVec2Mag(v);

    return (RVec2){
        .x = (float)v->x / m,
        .y = (float)v->y / m
    };
}

RVec3 ruinVec3Sum(const RVec3 *a, const RVec3 *b) {
    return (RVec3){
        .x = a->x + b->x,
        .y = a->y + b->y,
        .z = a->z + b->z
    };
}
RVec3 ruinVec3Sub(const RVec3 *a, const RVec3 *b) {
    return (RVec3){
        .x = a->x - b->x,
        .y = a->y - b->y,
        .z = a->z - b->z
    };
}
RVec3 ruinVec3Mul(const RVec3 *a, float f) {
    return (RVec3){
        .x = a->x * f,
        .y = a->y * f,
        .z = a->z * f
    };
}
RVec3 ruinVec3Div(const RVec3 *a, float f) {
    return (RVec3){
        .x = a->x / f,
        .y = a->y / f,
        .z = a->z / f
    };
}

float ruinVec3Mag(const RVec3 *v) {
    return sqrtf(v->x * v->x + v->y * v->y + v->z * v->z);
}
RVec3 ruinVec3Nor(const RVec3 *v) {
    const float m = ruinVec3Mag(v);
    return (RVec3){
        .x = v->x / m,
        .y = v->y / m,
        .z = v->z / m
    };
}

RVec4 ruinVec4Sum(const RVec4 *a, const RVec4 *b) {
    return (RVec4){
        .x = a->x + b->x,
        .y = a->y + b->y,
        .z = a->z + b->z,
        .w = a->w + b->w
    };
}
RVec4 ruinVec4Sub(const RVec4 *a, const RVec4 *b) {
    return (RVec4){
        .x = a->x - b->x,
        .y = a->y - b->y,
        .z = a->z - b->z,
        .w = a->w - b->w
    };
}
RVec4 ruinVec4Mul(const RVec4 *a, float f) {
    return (RVec4){
        .x = a->x * f,
        .y = a->y * f,
        .z = a->z * f,
        .w = a->w * f
    };
}
RVec4 ruinVec4Div(const RVec4 *a, float f) {
    return (RVec4){
        .x = a->x / f,
        .y = a->y / f,
        .z = a->z / f,
        .w = a->w / f
    };
}

float ruinVec4Mag(const RVec4 *v) {
    return sqrtf(v->x * v->x + v->y * v->y + v->z * v->w);
}
RVec4 ruinVec4Nor(const RVec4 *v) {
    const float m = ruinVec4Mag(v);
    return (RVec4){
        .x = v->x / m,
        .y = v->y / m,
        .z = v->z / m,
        .w = v->w / m
    };
}
