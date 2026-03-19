#ifndef AUDIO_MANAGER_H
#define AUDIO_MANAGER_H
/* =====================================================
   AUDIO MANAGER - Load nhac tu assets/music/
   day.ogg     - nhac ban ngay
   rain.ogg    - nhac troi mua
   combat.ogg  - nhac chien dau
   chill.ogg   - nhac toi / binh thuong
   ===================================================== */
void Audio_Init(void);
void Audio_Update(void);
void Audio_Pause(void);
void Audio_Resume(void);
void Audio_Unload(void);
void Audio_SetVolume(float vol);
#endif
