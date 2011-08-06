#include <toolkits/dbg/debug.h>
#include <toolkits/app/window.h>
#include "reactor.h"


//1 string
static int clipboard_put(lua_State* L) {
  const char* string = luaL_checkstring(L, 1);
  app_window_setclipboard(reactor.window, string);
  return 0;
}

//returns 
//1 string
static int clipboard_get(lua_State* L) {
  const char* string = 0;
  app_window_getclipboard(reactor.window, &string);
  lua_pushstring(L, string);
  return 1;
}

int luaopen_reactor_clipboard(lua_State* L) {
  static const luaL_reg reactor_clipboard[] = {
    {"get", clipboard_get},
    {"put", clipboard_put},
    {NULL, NULL}
  };

  lua_newtable(L); 
  lua_replace(L, LUA_ENVIRONINDEX);

  lua_newtable(L); 
  luaL_register(L, 0, reactor_clipboard);

  return 1;
}
