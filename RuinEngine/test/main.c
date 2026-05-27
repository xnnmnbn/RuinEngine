#include "ruin.h"

#include <stdio.h>

typedef struct {
    REntityID  camera;
    REntityID  player;
    REntityID  enemy;
    REntityID  pistol1;
    REntityID  pistol2;
    REntityID  background;
    REntityID *bullet_pool;
    size_t     bullet_count;
    size_t     next_bullet_idx;
} MyGameEntities;

typedef struct {
    RTransform  *player_t;
    RTransform  *enemy_t;
    RTransform  *background_t;
    RTransform  *pistol1_t;
    RTransform  *pistol2_t;
    RTransform **bullet_ts;
} MyGameTransforms;

typedef struct {
    RSpriteRenderer *player;
    RSpriteRenderer *enemy;
    RSpriteRenderer *pistol1;
    RSpriteRenderer *pistol2;
    RSpriteRenderer *background;
    RSpriteRenderer *bullets;
} MyGameRenderers2D;

typedef struct {
    RTextureID background;
    RTextureID player_idle;
    RTextureID player_walking1;
    RTextureID player_walking2;
    RTextureID enemy_idle;
    RTextureID enemy_walking1;
    RTextureID enemy_walking2;
    RTextureID pistol;
    RTextureID bullet;
} MyGameTextures;

typedef struct {
    RSoundID walking;
    RSoundID pistol_boom;
    RSoundID pistol_reload;
} MyGameSounds;

typedef struct {
    RMusicID battle;
    RMusicID win;
    RMusicID fail;
} MyGameMusics;

typedef struct {
    MyGameEntities    entities;
    MyGameTextures    textures;
    MyGameSounds      sounds;
    MyGameMusics      musics;
    MyGameTransforms  transforms;
    MyGameRenderers2D renderers;
} MyGame;

static MyGame game = {0};

void myGameInit(MyGame *g) {
    ruinInit();
    ruinWindowCreate(800, 450, "Ruin Test");
    ruinTimeSetTargetFPS(30);
    

    ruinEntityTransformGet(89);
}

void myGameUpdate(MyGame *g) {
ruinFrameBegin();

    if (ruinKeyHold(RUIN_KEY_SPACE)) {
        RUIN_DEBUG("FPS: %d", ruinTimeFPS());
    }
    
    
ruinFrameEnd();
}

void myGameKill(MyGame *g) {
    ruinKill();
}


int main(void) {

    setvbuf(stdout, NULL, _IONBF, 0);

    myGameInit(&game);

    while (ruinWindowRunning()) {
        myGameUpdate(&game);
    }

    myGameKill(&game);

    return 0;
}
