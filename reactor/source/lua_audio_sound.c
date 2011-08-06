#include <toolkits/dbg/debug.h>
#include <toolkits/aud/audio.h>
#include <toolkits/aud/source.h>
#include <toolkits/aud/sound.h>
#include "reactor.h"

//1 sound
static int sound_play(lua_State* L) {
  aud_sound_t* sound = *(void**)luaL_checkudata(L, 1, "reactor_audio_sound");
  aud_sound_play(sound);
  return 0;
}

//1 sound
static int sound_stop(lua_State* L) {
  aud_sound_t* sound = *(void**)luaL_checkudata(L, 1, "reactor_audio_sound");
  aud_sound_stop(sound);
  return 0;
}

static int sound_new(lua_State* L)
{
  aud_source_t* source = *(void**)luaL_checkudata(L, 1, "reactor_audio_source");  
  aud_sound_t** sound_ud = lua_newuserdata(L, sizeof(void*));
  *sound_ud = aud_sound_create( source );
  
  luaL_getmetatable(L, "reactor_audio_sound");
  lua_setmetatable(L, -2);

  return 1;
}

int luaopen_reactor_audio_sound(lua_State* L) {
  static const luaL_reg reactor_audio_sound[] = {
    {"new", sound_new}, 
    {NULL, NULL}
  };

  static const luaL_reg reactor_audio_sound_functions[] = {  
    {"play", sound_play},
    {"stop", sound_stop},
    {NULL, NULL}
  };

  luaL_newmetatable(L, "reactor_audio_sound");
  lua_pushvalue(L, -1);
  lua_setfield(L, -2, "__index");
  luaL_register(L, 0, reactor_audio_sound_functions);
  lua_pop(L, 1);

  lua_newtable(L); 
  luaL_register(L, 0, reactor_audio_sound);

  return 1;
}