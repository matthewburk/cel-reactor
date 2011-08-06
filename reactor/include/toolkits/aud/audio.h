
#ifndef AUD_AUDIO_H
#define AUD_AUDIO_H


/*============================================================================================================================================================*/
/*                                                                                                                                                            */
/*============================================================================================================================================================*/
/*       1         2         3         4         5         6         7         8         9         0         1         2         3         4         5        */
/*345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678*/
/*============================================================================================================================================================*/


#include <stddef.h>
#include <toolkits/sys/intrinsics.h>
#include <toolkits/sys/stdbool.h>
#include <toolkits/sys/stdint.h>


#ifdef __cplusplus
extern "C" {
#endif


#define AUD_NAMESPACE "aud"


#define AUD_SOUND_LOOPFOREVER -1
#define AUD_SOURCE_UNLIMITEDSOUNDS -1


/* enumerated types */
typedef enum aud_eventkind_t aud_eventkind_t;
typedef enum aud_sourceformat_t aud_sourceformat_t;
typedef enum aud_sourcekind_t aud_sourcekind_t;
typedef enum aud_sourcetype_t aud_sourcetype_t;

/* opaque types */
typedef struct aud_device_t aud_device_t;
typedef struct aud_group_t aud_group_t;
typedef struct aud_sound_t aud_sound_t;
typedef struct aud_source_t aud_source_t;

/* transparent types */
typedef struct aud_eventlisteners_t aud_eventlisteners_t;

/* event types */
typedef struct aud_soundevent_t aud_soundevent_t;
typedef union aud_event_t aud_event_t;

/* function pointer types */
typedef void (*aud_eventlistener_t)( const aud_event_t* event, void* userdata );


enum aud_eventkind_t
{
  AUD_EVENTKIND_UNKNOWN,
  AUD_EVENTKIND_SOUNDEND
};

enum aud_sourceformat_t
{
  AUD_SOURCEFORMAT_UNKNOWN,
  AUD_SOURCEFORMAT_PCM8,
  AUD_SOURCEFORMAT_PCM16,
  AUD_SOURCEFORMAT_PCM24,
  AUD_SOURCEFORMAT_PCM32,
  AUD_SOURCEFORMAT_PCMFLOAT
};

enum aud_sourcekind_t
{
  AUD_SOURCEKIND_UNKNOWN,
  AUD_SOURCEKIND_SAMPLE,
  AUD_SOURCEKIND_STREAM
};

enum aud_sourcetype_t
{
  AUD_SOURCETYPE_UNKNOWN,
  AUD_SOURCETYPE_AIFF,
  AUD_SOURCETYPE_CDDA,
  AUD_SOURCETYPE_MIDI,
  AUD_SOURCETYPE_OGGVORBIS,
  AUD_SOURCETYPE_RAW,
  AUD_SOURCETYPE_WAV
};

struct aud_eventlisteners_t
{
  aud_eventlistener_t listener;
  void* userdata;
  aud_eventlisteners_t* next;
};

struct aud_soundevent_t
{
  aud_eventkind_t kind;
  aud_sound_t* sound;
};

union aud_event_t
{
  aud_eventkind_t kind;
  aud_soundevent_t soundevent;
};


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
