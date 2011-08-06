#include <toolkits/dbg/debug.h>
#include <toolkits/aud/audio.h>
#include <toolkits/aud/source.h>
#include "reactor.h"

static aud_device_t* getdevice(lua_State* L)
{
  if (!reactor.device) {
    reactor.device = aud_device_create();    
  }

  return reactor.device;
}

//1 font
static int graphics_setfont(lua_State* L) {
  gfx_font_t* font = *(void**)luaL_checkudata(L, 1, "reactor_graphics_font");
  lua_pushlightuserdata(L, font);
  lua_setfield(L, LUA_ENVIRONINDEX, "font");
  return 0;
}

static void reactor_audio_source_ref(lua_State* L, aud_source_t* source)
{
  lua_pushlightuserdata(L, source);
  lua_settable(L, LUA_ENVIRONINDEX);
}

aud_source_t* reactor_audio_source_obtain(lua_State* L, const char* name, aud_sourcekind_t kind)
{
  lua_gettable(L, LUA_ENVIRONINDEX)
  font = lua_touserdata(L, -1);

   *source_ud = aud_source_create( getdevice(L), name, sourcekind );

   

  if (!font) {
    return luaL_error(L, "no font set");
  }
}


static int source_new(lua_State* L)
{
  static char* audiosourcemodes[] = {
    "sample",    
    "sample", 
    "stream",
    0 
  };

  const char* name = luaL_checkstring(L, 1);
  aud_sourcekind_t sourcekind = (aud_sourcekind_t)luaL_checkoption(L, 2, "stream", audiosourcemodes);
  aud_source_t** source_ud = lua_newuserdata(L, sizeof(void*));
  *source_ud = aud_source_create( getdevice(L), name, sourcekind );
  
  luaL_getmetatable(L, "reactor_audio_source");
  lua_setmetatable(L, -2);

  return 1;
}

int luaopen_reactor_audio_source(lua_State* L) {
  static const luaL_reg reactor_audio_source[] = {
    {"new", source_new}, 
    {NULL, NULL}
  };

  static const luaL_reg reactor_audio_source_functions[] = {    
    {NULL, NULL}
  };

  luaL_newmetatable(L, "reactor_audio_source");
  lua_pushvalue(L, -1);
  lua_setfield(L, -2, "__index");
  luaL_register(L, 0, reactor_audio_source_functions);
  lua_pop(L, 1);

  lua_newtable(L); 
  luaL_register(L, 0, reactor_audio_source);

  return 1;
}