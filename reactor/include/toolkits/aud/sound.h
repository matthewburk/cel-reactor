
#ifndef AUD_SOUND_H
#define AUD_SOUND_H


/*============================================================================================================================================================*/
/*                                                                                                                                                            */
/*============================================================================================================================================================*/
/*       1         2         3         4         5         6         7         8         9         0         1         2         3         4         5        */
/*345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678*/
/*============================================================================================================================================================*/


#include <toolkits/aud/audio.h>
#include <toolkits/mat/vector.h>


#ifdef __cplusplus
extern "C" {
#endif


SYS_API void aud_sound_getgroup( aud_sound_t* sound, aud_group_t** group );
SYS_API void aud_sound_setgroup( aud_sound_t* sound, aud_group_t* group );

SYS_API int32_t aud_sound_getloopcount( aud_sound_t* sound );
SYS_API void aud_sound_setloopcount( aud_sound_t* sound, int32_t loopcount );

SYS_API bool_t aud_sound_isplaying( aud_sound_t* sound );
SYS_API void aud_sound_stop( aud_sound_t* sound );

SYS_API bool_t aud_sound_ispaused( aud_sound_t* sound );
SYS_API void aud_sound_setpaused( aud_sound_t* sound, bool_t paused );

SYS_API bool_t aud_sound_ismute( aud_sound_t* sound );
SYS_API void aud_sound_setmute( aud_sound_t* sound, bool_t mute );

SYS_API float aud_sound_getvolume( aud_sound_t* sound );
SYS_API void aud_sound_setvolume( aud_sound_t* sound, float volume );

SYS_API float aud_sound_getpitch( aud_sound_t* sound );
SYS_API void aud_sound_setpitch( aud_sound_t* sound, float pitch );

SYS_API float aud_sound_getmindistance( aud_sound_t* sound );
SYS_API void aud_sound_setmindistance( aud_sound_t* sound, float mindistance );

SYS_API float aud_sound_getmaxdistance( aud_sound_t* sound );
SYS_API void aud_sound_setmaxdistance( aud_sound_t* sound, float maxdistance );

SYS_API void aud_sound_getposition( aud_sound_t* sound, mat_vector_t* position );
SYS_API void aud_sound_setposition( aud_sound_t* sound, const mat_vector_t* position );

SYS_API void aud_sound_getvelocity( aud_sound_t* sound, mat_vector_t* velocity );
SYS_API void aud_sound_setvelocity( aud_sound_t* sound, const mat_vector_t* velocity );


#ifdef __cplusplus
}
#endif


/*============================================================================================================================================================*/
/*                                                                                                                                                            */
/*============================================================================================================================================================*/
/*       1         2         3         4         5         6         7         8         9         0         1         2         3         4         5        */
/*345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678*/
/*============================================================================================================================================================*/


#endif
