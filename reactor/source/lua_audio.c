#if 0
#include <toolkits/dbg/debug.h>
#include <toolkits/aud/audio.h>
#include <toolkits/aud/source.h>
#include <toolkits/aud/sound.h>
#include "reactor.h"

static aud_device_t* getdevice(lua_State* L)
{
  if (!reactor.device) {
    reactor.device = aud_device_create();    
  }

  return reactor.device;
}

static int source_gc(lua_State* L) 
{
  if (reactor.device) {
  aud_source_t** source_ud = lua_touserdata(L, 1);
  aud_source_t* source = *source_ud;
  DBG_ASSERT(source);
  printf("collecting source\n");   
  //aud_source_destroy(source); //TODO put this back after TALKIN WITH TOM
  printf("collected source\n"); 
  }
  return 0;
}

static aud_source_t* source_new(lua_State* L, const char* name, aud_sourcekind_t kind)
{
  aud_source_t* source;
  aud_source_t** source_ud = lua_newuserdata(L, sizeof(void*));
  luaL_getmetatable(L, "reactor_audio_source");
  lua_setmetatable(L, -2);

  source = aud_source_create(getdevice(L), name, kind);
  DBG_ASSERT(source);
  *source_ud = source;
  return source;
}

static void luaopen_reactor_audio_source(lua_State* L) {  
  static const luaL_reg reactor_audio_source_functions[] = {   
    {"__gc", source_gc}, 
    {NULL, NULL}
  };

  luaL_newmetatable(L, "reactor_audio_source");
  lua_pushvalue(L, -1);
  lua_setfield(L, -2, "__index");
  luaL_register(L, 0, reactor_audio_source_functions);
  lua_pop(L, 1);

  //lua_newtable(L); 
  //luaL_register(L, 0, reactor_audio_source);

  //return 1;
}



//1 sample
static int sample_play(lua_State* L) {
  aud_sound_t* sample = *(aud_sound_t**)luaL_checkudata(L, 1, "reactor_audio_sample");
  aud_sound_play(sample);
  return 0;
}

//1 sample
static int sample_stop(lua_State* L) {
  aud_sound_t* sample = *(aud_sound_t**)luaL_checkudata(L, 1, "reactor_audio_sample");
  aud_sound_stop(sample);
  return 0;
}

static int sample_gc(lua_State* L) 
{  
  if (reactor.device) {
    aud_sound_t* sound = *(void**)lua_touserdata(L, 1);
    printf("collecting sample ... "); 
    aud_sound_destroy(sound);
    printf("collected sample\n"); 
    
  }
  return 0;
}

//1 name
static int sample_new(lua_State* L)
{
  const char* name = 0;
  aud_source_t** source_ud = 0;
  aud_source_t* source = 0;
  aud_sound_t** sample_ud = 0;

  DBG_ENTER();

  name = luaL_checkstring(L, 1);
  sample_ud = lua_newuserdata(L, sizeof(void*));

  {
  
    lua_pushvalue(L, 1); //name
    lua_gettable(L, LUA_ENVIRONINDEX);
    source_ud = lua_touserdata(L, -1);  

    if (source_ud) {
      source = *source_ud;
      printf("reusing source %s\n", name);
    }
    else {       
      printf("created new source %s\n", name);
      lua_pop(L, 1);
      source = source_new(L, name, AUD_SOURCEKIND_SAMPLE);
      
      lua_pushvalue(L, 1); //name
      lua_pushvalue(L, -2); //source
      lua_settable(L, LUA_ENVIRONINDEX);             
    }
   

    DBG_ASSERT(source);
  
  }

  lua_setfenv(L, -2);

  *sample_ud = aud_sound_create( source );

  DBG_ASSERT(*sample_ud);
  
  luaL_getmetatable(L, "reactor_audio_sample");
  lua_setmetatable(L, -2);

  luaL_checkudata(L, -1, "reactor_audio_sample");

  DBG_RETURN(1);
}

static int luaopen_reactor_audio_sample(lua_State* L) {
  static const luaL_reg reactor_audio_sample[] = {
    {"new", sample_new}, 
    {NULL, NULL}
  };

  static const luaL_reg reactor_audio_sample_functions[] = {  
    {"play", sample_play},
    {"stop", sample_stop},
    {"__gc", sample_gc},
    {NULL, NULL}
  };

  luaL_newmetatable(L, "reactor_audio_sample");
  lua_pushvalue(L, -1);
  lua_setfield(L, -2, "__index");
  luaL_register(L, 0, reactor_audio_sample_functions);
  lua_pop(L, 1);

  lua_newtable(L); 
  luaL_register(L, 0, reactor_audio_sample);

  return 1;
}

static int audio_getenv(lua_State* L)
{
  lua_pushvalue(L, LUA_ENVIRONINDEX);
  return 1;
}

int luaopen_reactor_audio(lua_State* L) {
  static const luaL_reg reactor_audio[] = {
    {"getenv", audio_getenv},
    {NULL, NULL}
  };
  
  lua_newtable(L);
  lua_newtable(L); 
  lua_pushliteral(L, "kv");
  lua_setfield(L, -2, "__mode");
  lua_setmetatable(L, -2);
    
  lua_replace(L, LUA_ENVIRONINDEX);

  lua_newtable(L); 
  luaL_register(L, 0, reactor_audio);

  luaopen_reactor_audio_source(L);//value
  
  lua_pushliteral(L, "sample");  //key 
  luaopen_reactor_audio_sample(L);//value
  lua_settable(L, -3);

  //lua_pushliteral(L, "stream");  //key 
  //luaopen_reactor_audio_stream(L);//value
  //lua_settable(L, -3);


  return 1;
}

#endif