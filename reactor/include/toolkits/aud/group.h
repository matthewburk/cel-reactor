
#ifndef AUD_GROUP_H
#define AUD_GROUP_H


/*============================================================================================================================================================*/
/*                                                                                                                                                            */
/*============================================================================================================================================================*/
/*       1         2         3         4         5         6         7         8         9         0         1         2         3         4         5        */
/*345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678*/
/*============================================================================================================================================================*/


#include <toolkits/aud/audio.h>


#ifdef __cplusplus
extern "C" {
#endif


SYS_API aud_group_t* aud_group_create( aud_device_t* device );
SYS_API void aud_group_destroy( aud_group_t* group );

SYS_API void aud_group_getparent( aud_group_t* group, aud_group_t** parent );
SYS_API void aud_group_addchild( aud_group_t* group, aud_group_t* child );

SYS_API void aud_group_stop( aud_group_t* group );

SYS_API bool_t aud_group_ispaused( aud_group_t* group );
SYS_API void aud_group_setpaused( aud_group_t* group, bool_t paused );

SYS_API bool_t aud_group_ismute( aud_group_t* group );
SYS_API void aud_group_setmute( aud_group_t* group, bool_t mute );

SYS_API float aud_group_getvolume( aud_group_t* group );
SYS_API void aud_group_setvolume( aud_group_t* group, float volume );

SYS_API float aud_group_getpitch( aud_group_t* group );
SYS_API void aud_group_setpitch( aud_group_t* group, float pitch );


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
