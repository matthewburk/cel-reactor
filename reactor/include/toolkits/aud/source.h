
#ifndef AUD_SOURCE_H
#define AUD_SOURCE_H


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


SYS_API aud_source_t* aud_source_create( aud_device_t* device, const char* name, aud_sourcekind_t kind );
SYS_API void aud_source_destroy( aud_source_t* source );

SYS_API void aud_source_addlistener( aud_source_t* source, aud_eventlistener_t listener, void* userdata );
SYS_API void aud_source_removelistener( aud_source_t* source, aud_eventlistener_t listener, void* userdata );

SYS_API aud_sourcekind_t aud_source_getkind( aud_source_t* source );

SYS_API aud_sourcetype_t aud_source_gettype( aud_source_t* source );
SYS_API aud_sourceformat_t aud_source_getformat( aud_source_t* source );
SYS_API size_t aud_source_getlength( aud_source_t* source );

SYS_API int32_t aud_source_getmaxsounds( aud_source_t* source );
SYS_API void aud_source_setmaxsounds( aud_source_t* source, int32_t maxsounds );

SYS_API aud_sound_t* aud_source_playsound( aud_source_t* source, bool_t paused );


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
