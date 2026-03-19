#include "audio_manager.h"
#include "types.h"

typedef enum {
    TRACK_DAY    = 0,
    TRACK_RAIN   = 1,
    TRACK_COMBAT = 2,
    TRACK_CHILL  = 3,
    TRACK_NIGHT  = 4,
    TRACK_COUNT
} TrackID;

static const char *TRACK_PATHS[TRACK_COUNT] = {
    "assets/music/nhacnen.ogg",
    "assets/music/mua.mp3",
    "assets/music/damquai.wav",
    "assets/music/chill.mp3",
    "assets/music/night.mp3",
};

static Music   sTracks[TRACK_COUNT];
static bool    sLoaded[TRACK_COUNT];
static TrackID sCurrent  = (TrackID)-1;
static float   sVolume   = 1.0f;
static bool    sReady    = false;

/* Fade */
static float   sFadeVol  = 1.0f;
static float   sFadeDir  = 0.0f;   /* -1=out, +1=in */
static TrackID sFadeTo   = (TrackID)-1;
#define FADE_SPD 1.5f

static void StopCurrent(void) {
    if ((int)sCurrent >= 0 && sLoaded[sCurrent])
        StopMusicStream(sTracks[sCurrent]);
    sCurrent = (TrackID)-1;
}

static void PlayTrack(TrackID id) {
    if (id == sCurrent) return;
    if ((int)id < 0 || id >= TRACK_COUNT || !sLoaded[id]) { StopCurrent(); return; }
    StopCurrent();
    SetMusicVolume(sTracks[id], sVolume * sFadeVol);
    PlayMusicStream(sTracks[id]);
    sCurrent = id;
}

static void FadeTo(TrackID id) {
    if (id == sCurrent) return;
    sFadeTo  = id;
    sFadeDir = -1.0f;
}

void Audio_Init(void) {
    InitAudioDevice();
    if (!IsAudioDeviceReady()) return;
    sReady = true;
    for (int i = 0; i < TRACK_COUNT; i++) {
        sLoaded[i] = false;
        if (FileExists(TRACK_PATHS[i])) {
            sTracks[i] = LoadMusicStream(TRACK_PATHS[i]);
            sTracks[i].looping = true;
            SetMusicVolume(sTracks[i], sVolume);
            sLoaded[i] = true;
            TraceLog(LOG_INFO, "AUDIO: Loaded %s", TRACK_PATHS[i]);
        } else {
            TraceLog(LOG_WARNING, "AUDIO: Missing %s (game runs fine without)", TRACK_PATHS[i]);
        }
    }
    sFadeVol = 1.0f;
    PlayTrack(TRACK_DAY);
}

void Audio_Update(void) {
    if (!sReady) return;

    /* Chon track dua tren context */
    TrackID want = TRACK_DAY;
    if (G.screen == SCR_GAME || G.screen == SCR_PAUSE) {
        /* Kiểm tra kẻ thù gần */
        bool nearEnemy = false;
        for (int i = 0; i < MAX_ENEMIES; i++) {
            Enemy *e = &G.enemies[i];
            if (!e->active || e->state == ESTATE_DEAD) continue;
            float dx = e->pos.x - G.player.pos.x;
            float dy = e->pos.y - G.player.pos.y;
            float combatRange = G.isNight
                ? (float)(TILE_SIZE*16)*(TILE_SIZE*16)   /* đêm: nghe nhạc combat từ xa hơn */
                : (float)(TILE_SIZE*10)*(TILE_SIZE*10);
            if (dx*dx + dy*dy < combatRange) {
                nearEnemy = true; break;
            }
        }

        if (nearEnemy)
            want = TRACK_COMBAT;
        else if (G.weather.current == WEATHER_RAINY)
            want = TRACK_RAIN;
        else if (G.isNight)
            want = TRACK_NIGHT;  
        else
            want = TRACK_DAY;
    } else {
        want = TRACK_CHILL;
    }

    /* Xu ly fade cross */
    float dt = GetFrameTime();
    if (want != sCurrent && sFadeDir == 0.0f)
        FadeTo(want);

    if (sFadeDir != 0.0f) {
        sFadeVol += sFadeDir * FADE_SPD * dt;
        if (sFadeDir < 0 && sFadeVol <= 0.0f) {
            sFadeVol = 0.0f;
            PlayTrack(sFadeTo);
            sFadeDir = 1.0f;
        } else if (sFadeDir > 0 && sFadeVol >= 1.0f) {
            sFadeVol = 1.0f;
            sFadeDir = 0.0f;
            sFadeTo  = (TrackID)-1;
        }
        if ((int)sCurrent >= 0 && sLoaded[sCurrent])
            SetMusicVolume(sTracks[sCurrent], sVolume * sFadeVol);
    }

    /* Bat buoc goi moi frame de stream audio */
    if ((int)sCurrent >= 0 && sLoaded[sCurrent] && !G.paused)
        UpdateMusicStream(sTracks[sCurrent]);
}

void Audio_Pause(void) {
    if (!sReady) return;
    if ((int)sCurrent >= 0 && sLoaded[sCurrent])
        PauseMusicStream(sTracks[sCurrent]);
}

void Audio_Resume(void) {
    if (!sReady) return;
    if ((int)sCurrent >= 0 && sLoaded[sCurrent])
        ResumeMusicStream(sTracks[sCurrent]);
}

void Audio_SetVolume(float vol) {
    sVolume = Clamp(vol, 0.0f, 1.0f);
    if (!sReady) return;
    if ((int)sCurrent >= 0 && sLoaded[sCurrent])
        SetMusicVolume(sTracks[sCurrent], sVolume * sFadeVol);
}

void Audio_Unload(void) {
    if (!sReady) return;
    StopCurrent();
    for (int i = 0; i < TRACK_COUNT; i++)
        if (sLoaded[i]) UnloadMusicStream(sTracks[i]);
    CloseAudioDevice();
}
