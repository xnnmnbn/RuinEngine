#ifndef RUIN_ENGINE_H
#define RUIN_ENGINE_H

#ifdef __cplusplus
extern "C" {
#endif

#include <stdint.h>
#include <stddef.h>

typedef uint8_t RBool;

#define RUIN_TRUE 1
#define RUIN_FALSE 0

// #define RUIN_ENABLE_DEBUG

#define RUIN_DEBUG(fmt, ...) printf("[ruin] " fmt "\n", ##__VA_ARGS__)

#define RUIN_INVALID_ID          0
#define RUIN_MAX_TEXTURES        1024
#define RUIN_MAX_MATERIALS       512
#define RUIN_MAX_MESHES          1024
#define RUIN_MAX_CAMERAS         16
#define RUIN_MAX_RENDER_TARGETS  32
#define RUIN_MAX_SOUNDS          512
#define RUIN_MAX_MUSICS          32
#define RUIN_MAX_SOUND_LISTENERS 1
#define RUIN_MAX_ENTITIES        20000

typedef uint32_t REntityID;
typedef uint16_t RTextureID;
typedef uint16_t RMaterialID;
typedef uint16_t RSoundID;
typedef uint16_t RMusicID;
typedef uint16_t RMeshID;
typedef uint8_t  RRenderTargetID;

typedef enum RKey {
    RUIN_KEY_0 = 39,
    RUIN_KEY_1 = 30,
    RUIN_KEY_2 = 31,
    RUIN_KEY_3 = 32,
    RUIN_KEY_4 = 33,
    RUIN_KEY_5 = 34,
    RUIN_KEY_6 = 35,
    RUIN_KEY_7 = 36,
    RUIN_KEY_8 = 37,
    RUIN_KEY_9 = 38,

    RUIN_KEY_A = 4,
    RUIN_KEY_B = 5,
    RUIN_KEY_C = 6,
    RUIN_KEY_D = 7,
    RUIN_KEY_E = 8,
    RUIN_KEY_F = 9,
    RUIN_KEY_G = 10,
    RUIN_KEY_H = 11,
    RUIN_KEY_I = 12,
    RUIN_KEY_J = 13,
    RUIN_KEY_K = 14,
    RUIN_KEY_L = 15,
    RUIN_KEY_M = 16,
    RUIN_KEY_N = 17,
    RUIN_KEY_O = 18,
    RUIN_KEY_P = 19,
    RUIN_KEY_Q = 20,
    RUIN_KEY_R = 21,
    RUIN_KEY_S = 22,
    RUIN_KEY_T = 23,
    RUIN_KEY_U = 24,
    RUIN_KEY_V = 25,
    RUIN_KEY_W = 26,
    RUIN_KEY_X = 27,
    RUIN_KEY_Y = 28,
    RUIN_KEY_Z = 29,

    RUIN_KEY_SPACE     = 44,
    RUIN_KEY_ENTER     = 40,
    RUIN_KEY_TAB       = 43,
    RUIN_KEY_ESCAPE    = 41,
    RUIN_KEY_BACKSPACE = 42,

    RUIN_KEY_F1  = 58,
    RUIN_KEY_F2  = 59,
    RUIN_KEY_F3  = 60,
    RUIN_KEY_F4  = 61,
    RUIN_KEY_F5  = 62,
    RUIN_KEY_F6  = 63,
    RUIN_KEY_F7  = 64,
    RUIN_KEY_F8  = 65,
    RUIN_KEY_F9  = 66,
    RUIN_KEY_F10 = 67,
    RUIN_KEY_F11 = 68,
    RUIN_KEY_F12 = 69,

    RUIN_KEY_LEFT_SHIFT  = 225,
    RUIN_KEY_RIGHT_SHIFT = 229,
    RUIN_KEY_LEFT_CTRL   = 224,
    RUIN_KEY_RIGHT_CTRL  = 228,
    RUIN_KEY_LEFT_ALT    = 226,
    RUIN_KEY_RIGHT_ALT   = 230,

    RUIN_KEY_UP    = 82,
    RUIN_KEY_DOWN  = 81,
    RUIN_KEY_LEFT  = 80,
    RUIN_KEY_RIGHT = 79
} RKey;

typedef enum RMouseButton {
    RUIN_MOUSE_LEFT   = 1,
    RUIN_MOUSE_MIDDLE = 2,
    RUIN_MOUSE_RIGHT  = 3,
    RUIN_MOUSE_X1     = 4,
    RUIN_MOUSE_X2     = 5
} RMouseButton;

typedef enum RMaterialMask {
    RUIN_MAT3D_MASK_ALBEDO        = 1 << 0,
    RUIN_MAT3D_MASK_NORMAL        = 1 << 1,
    RUIN_MAT3D_MASK_ROUGHNESS     = 1 << 2,
    RUIN_MAT3D_MASK_METALLIC      = 1 << 3,
    RUIN_MAT3D_MASK_TINT          = 1 << 4,
    RUIN_MAT3D_MASK_ALPHA         = 1 << 5,
    RUIN_MAT3D_MASK_ROUGHNESS_VAL = 1 << 6,
    RUIN_MAT3D_MASK_METALLIC_VAL  = 1 << 7,
    RUIN_MAT3D_MASK_TILING_X      = 1 << 8,
    RUIN_MAT3D_MASK_TILING_Y      = 1 << 9,
    RUIN_MAT3D_MASK_ALL           = RUIN_MAT3D_MASK_ALBEDO    | RUIN_MAT3D_MASK_NORMAL        |
                                    RUIN_MAT3D_MASK_METALLIC  | RUIN_MAT3D_MASK_METALLIC_VAL  |
                                    RUIN_MAT3D_MASK_ROUGHNESS | RUIN_MAT3D_MASK_ROUGHNESS_VAL |
                                    RUIN_MAT3D_MASK_TINT      | RUIN_MAT3D_MASK_ALPHA         |
                                    RUIN_MAT3D_MASK_TILING_X  | RUIN_MAT3D_MASK_TILING_Y
} RMaterialMask;

typedef enum RProjection {
    RUIN_PROJECTION_ORTHOGRAPHIC,
    RUIN_PROJECTION_PERSPECTIVE
} RProjection;

typedef enum RRigidBodyType {
    RUIN_RIGIDBODY_TYPE_DYNAMIC,
    RUIN_RIGIDBODY_TYPE_STATIC,
    RUIN_RIGIDBODY_TYPE_KINEMATIC
} RRigidBodyType;

typedef enum RRigidBody2DShape {
    RUIN_RIGIDBODY2D_SHAPE_SQUARE,
    RUIN_RIGIDBODY2D_SHAPE_CIRCLE
} RRigidBody2DShape;

typedef enum RRigidBody3DShape {
    RUIN_RIGIDBODY3D_SHAPE_CUBE,
    RUIN_RIGIDBODY3D_SHAPE_SPHERE,
    RUIN_RIGIDBODY3D_SHAPE_CYLINDER
} RRigidBody3DShape;



typedef struct RVec2 {
    float x, y;
} RVec2;

typedef struct RVec3 {
    float x, y, z;
} RVec3;

typedef struct RVec4 {
    float x, y, z, w;
} RVec4;

typedef struct RColor {
    float r, g, b, a;
} RColor;

typedef struct RTransform {
    RVec3      position;
    RVec3      rotation;
    RVec3      scale;
    REntityID  parent;
    RBool      dirty;
} RTransform;

typedef struct RPhysicsWorld {
    RVec3 gravity;
} RPhysicsWorld;

typedef struct RRigidBody2D {
    RRigidBodyType    type;
    RRigidBody2DShape shape;
    RVec3             position;
    RVec3             rotation;
    RVec3             scale;
    RVec3             velocity;
    RVec3             angular_velocity;
    float             mass;
    float             friction;
    float             restitution;
    RBool             ignore_gravity;
} RRigidBody2D;

typedef struct RRigidBody3D {
    RRigidBodyType    type;
    RRigidBody3DShape shape;
    RVec3             position;
    RVec3             rotation;
    RVec3             scale;
    RVec3             velocity;
    RVec3             angular_velocity;
    float             mass;
    float             friction;
    float             restitution;
    RBool             ignore_gravity;
} RRigidBody3D;

typedef struct RSoundListener {
    RVec3 position;
    RVec3 rotation;
    RVec3 velocity;
} RSoundListener;

typedef struct RSoundPlayer {
    RSoundID sound;
    float    volume;
} RSoundPlayer;

typedef struct RMusicPlayer {
    RMusicID music;
    float    volume;
} RMusicPlayer;


typedef struct RMaterialInfo {
    RMaterialMask masks;
    RTextureID    albedo;
    RTextureID    normal;
    RTextureID    roughness;
    RTextureID    metallic;
    RColor        tint;
    float         alpha;
    float         roughness_val;
    float         metallic_val;
    float         tiling_x;
    float         tiling_y;
} RMaterialInfo;

typedef struct RRenderTargetInfo {
    int32_t width;
    int32_t height;
    RBool   depth;
} RRenderTargetInfo;

typedef struct RCamera2D {
    RRenderTargetID target;
    float width;
    float height;
    float far;
    float near;
} RCamera2D;

typedef struct RCamera3D {
    RRenderTargetID target;
    float width;
    float height;
    float far;
    float near;
    float fov;
} RCamera3D;

typedef struct RSpriteRenderer {
    RTextureID texture;
    RColor     tint;
    float      opacity;
} RSpriteRenderer;

typedef struct RMeshRenderer {
    RMeshID mesh;
} RMeshRenderer;

RVec2 ruinVec2(float x, float y);
RVec3 ruinVec3(float x, float y, float z);
RVec4 ruinVec4(float x, float y, float z, float w);

RVec2 ruinVec2Sum(const RVec2 *a, const RVec2 *b);
RVec2 ruinVec2Sub(const RVec2 *a, const RVec2 *b);
RVec2 ruinVec2Mul(const RVec2 *a, float f);
RVec2 ruinVec2Div(const RVec2 *a, float f);

float ruinVec2Mag(const RVec2 *v);
RVec2 ruinVec2Nor(const RVec2 *v);

RVec3 ruinVec3Sum(const RVec3 *a, const RVec3 *b);
RVec3 ruinVec3Sub(const RVec3 *a, const RVec3 *b);
RVec3 ruinVec3Mul(const RVec3 *a, float f);
RVec3 ruinVec3Div(const RVec3 *a, float f);

float ruinVec3Mag(const RVec3 *v);
RVec3 ruinVec3Nor(const RVec3 *v);

RVec4 ruinVec4Sum(const RVec4 *a, const RVec4 *b);
RVec4 ruinVec4Sub(const RVec4 *a, const RVec4 *b);
RVec4 ruinVec4Mul(const RVec4 *a, float f);
RVec4 ruinVec4Div(const RVec4 *a, float f);

float ruinVec4Mag(const RVec4 *v);
RVec4 ruinVec4Nor(const RVec4 *v);

RBool ruinInit(void);
RBool ruinKill(void);

void ruinFrameBegin(void);
void ruinFrameEnd(void);

REntityID ruinEntityCreate(void);
void      ruinEntityKill(REntityID e);
RBool     ruinEntityValid(REntityID e);

RBool ruinWindowCreate(int32_t w, int32_t h, const char *title);
RBool ruinWindowRunning(void);
RVec2 ruinWindowSize(void);
RVec2 ruinWindowPosition(void);
RBool ruinWindowFocused(void);
RBool ruinWindowMinimized(void);
RBool ruinWindowFullscreen(void);

void ruinWindowSetTitle(const char *t);
void ruinWindowSetSize(int32_t w, int32_t h);
void ruinWindowSetFullscreen(RBool f);
void ruinWindowSetVsync(RBool vs);
void ruinWindowSetCursorVisible(RBool v);
void ruinWindowSetCursorLocked(RBool l);
void ruinWindowSetProjection(RProjection p);
void ruinWindowSetResolution(int32_t w, int32_t h);

uint8_t ruinTimeFPS(void);
float   ruinTimeDelta(void);
float   ruinTimeElapsed(void);
float   ruinTimeDeltaFixed(void);
float   ruinTimeElapsedFixed(void);
void    ruinTimeSetSpeed(float s);
void    ruinTimeSetTargetFPS(uint8_t t);

RBool ruinKeyDown(RKey k);
RBool ruinKeyHold(RKey k);
RBool ruinKeyUp(RKey k);

RBool ruinMouseDown(RMouseButton b);
RBool ruinMouseHold(RMouseButton b);
RBool ruinMouseUp(RMouseButton b);
float ruinMouseScroll(void);

RRenderTargetID ruinRenderTargetCreate(RRenderTargetInfo *i);
void            ruinRenderTargetKill(RRenderTargetID t);

RTextureID ruinTextureLoad(const char *path);
RTextureID ruinTextureFromRenderTarget(RRenderTargetID t);
void       ruinTextureKill(RTextureID t);

RMeshID ruinMeshLoad(const char *path);
void    ruinMeshKill(RMeshID m);

RSoundID ruinSoundLOad(const char *path);
void     ruinSoundKill(RSoundID s);

RMusicID ruinMusicLoad(const char *path);
void     ruinMusicKill(RMusicID m);

RMaterialID ruinMaterialCreate(const RMaterialInfo *i);
void        ruinMaterialUpdate(RMaterialID m, const RMaterialInfo *i);
void        ruinMaterialKill(RMaterialID m);

RTransform  ruinDefaultTransform(void);
RTransform *ruinEntityTransformGet(REntityID e);
void        ruinEntityTransformAdd(REntityID e, RTransform t);
void        ruinEntityTransformKill(REntityID e);
void        ruinEntityTransformSetDirty(REntityID e, RBool d);
RVec3       ruinEntityTransformGetWorldPosition(REntityID e);
RVec3       ruinEntityTransformGetWorldRotation(REntityID e);
RVec3       ruinEntityTransformGetWorldScale(REntityID e);

RRigidBody2D *ruinEntityRigidBody2dGet(REntityID e);
void          ruinEntityRigidBody2dAdd(REntityID e, RRigidBody2D b);
void          ruinEntityRigidBody2dKill(REntityID e);

RRigidBody3D *ruinEntityRigidBody3dGet(REntityID e);
void          ruinEntityRigidBody3dAdd(REntityID e, RRigidBody3D b);
void          ruinEntityRigidBody3dKill(REntityID e);

RSoundListener *ruinEntitySoundListenerGet(REntityID e);
void            ruinEntitySoundListenerAdd(REntityID e, RSoundListener l);
void            ruinEntitySoundListenerKill(REntityID e);

RSoundPlayer *ruinEntitySoundPlayerGet(REntityID e);
void          ruinEntitySoundPlayerAdd(REntityID e, RSoundPlayer p);
void          ruinEntitySoundPlayerKill(REntityID e);
void          ruinEntitySoundPlayerPlay(REntityID e);
void          ruinEntitySoundPlayerStop(REntityID e);

RMusicPlayer *ruinEntityMusicPlayerGet(REntityID e);
void          ruinEntityMusicPlayerAdd(REntityID e, RMusicPlayer p);
void          ruinEntityMusicPlayerKill(REntityID e);
void          ruinEntityMusicPlayerPlay(REntityID e);
void          ruinEntityMusicPlayerStop(REntityID e);



RCamera2D *ruinEntityCamera2dGet(REntityID e);
void       ruinEntityCamera2dAdd(REntityID e, RCamera2D c);
void       ruinEntityCamera2dKill(REntityID e);
void       ruinEntityCamera2dSetRenderTarget(REntityID e, RRenderTargetID t);

RCamera3D *ruinEntityCamera3dGet(REntityID e);
void       ruinEntityCamera3dAdd(REntityID e, RCamera3D c);
void       ruinEntityCamera3dKill(REntityID e);
void       ruinEntityCamera3dSetRenderTarget(REntityID e, RRenderTargetID t);

void ruinEntityCameraUse(REntityID e, RProjection p);

void ruinEntitySpriteRendererAdd(REntityID e, RSpriteRenderer r);
void ruinEntitySpriteRendererKill(REntityID e);

void ruinEntityMeshRendererAdd(REntityID e, RMeshRenderer r);
void ruinEntityMeshRendererKill(REntityID e);




#ifdef __cplusplus
}
#endif

#endif
