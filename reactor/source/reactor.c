
/*============================================================================================================================================================*/
/*                                                                                                                                                            */
/*============================================================================================================================================================*/
/*       1         2         3         4         5         6         7         8         9         0         1         2         3         4         5        */
/*345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678*/
/*============================================================================================================================================================*/

#include <stdlib.h>
#include <signal.h>
#include <math.h>
#include <lua.h>
#include <lauxlib.h>
#include <lualib.h>
#include <debug.h>
#include "reactor.h"
#include "lua_cairo.h"


extern int luaopen_reactor_graphics(lua_State* L);
extern int luaopen_reactor_clipboard(lua_State* L);

static lua_State* L = 0;

struct reactor reactor = {0};

static int traceback (lua_State *L) {
  if (!lua_isstring(L, 1))  /* 'message' not a string? */
    return 1;  /* keep it intact */
  lua_getfield(L, LUA_GLOBALSINDEX, "debug");
  if (!lua_istable(L, -1)) {
    lua_pop(L, 1);
    return 1;
  }
  lua_getfield(L, -1, "traceback");
  if (!lua_isfunction(L, -1)) {
    lua_pop(L, 2);
    return 1;
  }
  lua_pushvalue(L, 1);  /* pass error message */
  lua_pushinteger(L, 2);  /* skip this function and traceback */
  lua_call(L, 2, 1);  /* call debug.traceback */
  return 1;
}

static int docall(lua_State *L, int narg, int nresults) {
  int status;
  int top = lua_gettop(L);
  int base = top - narg;  /* function index */
  //TODO pushing traceback causes huge memory leak
  lua_getglobal(L, "errorfunc");
  //lua_pushcfunction(L, traceback);  /* push traceback function */
  lua_insert(L, base);  /* put it under chunk and args */
  status = lua_pcall(L, narg, nresults, base);
  lua_remove(L, base);  /* remove traceback function */

  if (status) {
    printf("%s", lua_tostring(L, -1));
    fflush(stdout);
    fflush(stderr);
    lua_pop(L, 1);
  }

  return status;
}

void reactor_winevent(const char* name) {
  int nargs = 0;
  if ( !strcmp(name, "create") ) {      
    reactor_driver_get_windowrect(&reactor.x, &reactor.y, &reactor.w, &reactor.h);  
    return;
  }
  else if (!strcmp(name, "resize")  ){    
    reactor_driver_get_windowrect(&reactor.x, &reactor.y, &reactor.w, &reactor.h);  
    if (L) {
      lua_getglobal(L, "reactor");
      lua_pushliteral(L, "w");
      lua_pushnumber(L, reactor.w);
      lua_settable(L, -3);

      lua_pushliteral(L, "h");
      lua_pushnumber(L, reactor.h);
      lua_settable(L, -3);

      lua_pushliteral(L, "resized");
      lua_gettable(L, -2);
     
      if (lua_isfunction(L, -1)) { 
        lua_pushinteger(L, reactor.w); nargs++;
        lua_pushinteger(L, reactor.h); nargs++;

        docall(L, nargs, 0);
        lua_pop(L, 1);
      }
      else {
        lua_pop(L, 2);
      }
    }
  }
  else if (!strcmp(name, "show") ) {
  } 
}

void reactor_command(const char* command) {
  //case APP_EVENTKIND_CLIPBOARDCOPY:
  //  {
  //  
  //    lua_getglobal(L, "reactor");
  //    lua_pushliteral(L, "command");
  //    lua_gettable(L, -2);
  //   
  //    if (lua_isfunction(L, -1)) { 
  //      lua_pushliteral(L, "copy"); nargs++;
  //    
  //      docall(L, nargs, 0);
  //      lua_pop(L, 1);
  //    }
  //    else {
  //      lua_pop(L, 2);
  //    }

  //    DBG_RETURN_VOID();
  //  }

  //  case APP_EVENTKIND_CLIPBOARDCUT:
  //  {
  //  
  //    lua_getglobal(L, "reactor");
  //    lua_pushliteral(L, "command");
  //    lua_gettable(L, -2);
  //   
  //    if (lua_isfunction(L, -1)) { 
  //      lua_pushliteral(L, "cut"); nargs++;
  //    
  //      docall(L, nargs, 0);
  //      lua_pop(L, 1);
  //    }
  //    else {
  //      lua_pop(L, 2);
  //    }

  //    DBG_RETURN_VOID();
  //  }
  //  case APP_EVENTKIND_CLIPBOARDPASTE:
  //  {
  //    lua_getglobal(L, "reactor");
  //    lua_pushliteral(L, "command");
  //    lua_gettable(L, -2);
  //   
  //    if (lua_isfunction(L, -1)) { 
  //      lua_pushliteral(L, "paste"); nargs++;
  //    
  //      docall(L, nargs, 0);
  //      lua_pop(L, 1);
  //    }
  //    else {
  //      lua_pop(L, 2);
  //    }

  //    DBG_RETURN_VOID();
  //  }
}

void reactor_mousedblclick(int x, int y, const char* button, int alt, int ctrl, int shift) {
  int nargs = 0;
  lua_getglobal(L, "reactor");
  lua_pushliteral(L, "mousedblclick");
  lua_gettable(L, -2);
 
  if (lua_isfunction(L, -1)) { 
    lua_pushinteger(L, x ); nargs++;
    lua_pushinteger(L, y ); nargs++;
    lua_pushstring(L, button); nargs++;
    lua_pushboolean(L, alt); nargs++;
    lua_pushboolean(L, ctrl); nargs++;
    lua_pushboolean(L, shift); nargs++;
    docall(L, nargs, 0);
    lua_pop(L, 1);
  }
  else {
    lua_pop(L, 2);
  }
}

void reactor_mousedown(int x, int y, const char* button, int alt, int ctrl, int shift) {
  int nargs = 0;
  lua_getglobal(L, "reactor");
  lua_pushliteral(L, "mousedown");
  lua_gettable(L, -2);
 
  if (lua_isfunction(L, -1)) { 
    lua_pushinteger(L, x ); nargs++;
    lua_pushinteger(L, y ); nargs++;
    lua_pushstring(L, button); nargs++;
    lua_pushboolean(L, alt); nargs++;
    lua_pushboolean(L, ctrl); nargs++;
    lua_pushboolean(L, shift); nargs++;
    docall(L, nargs, 0);
    lua_pop(L, 1);
  }
  else {
    lua_pop(L, 2);
  }
}

void reactor_mouseup(int x, int y, const char* button, int alt, int ctrl, int shift) {
  int nargs = 0;
  lua_getglobal(L, "reactor");
  lua_pushliteral(L, "mouseup");
  lua_gettable(L, -2);
 
  if (lua_isfunction(L, -1)) { 
    lua_pushinteger(L, x ); nargs++;
    lua_pushinteger(L, y ); nargs++;
    lua_pushstring(L, button); nargs++;
    lua_pushboolean(L, alt); nargs++;
    lua_pushboolean(L, ctrl); nargs++;
    lua_pushboolean(L, shift); nargs++;
    docall(L, nargs, 0);
    lua_pop(L, 1);
  }
  else {
    lua_pop(L, 2);
  }
}

void reactor_mousewheel(int x, int y, int delta, int step, int alt, int ctrl, int shift) {
  int nargs = 0;
  lua_getglobal(L, "reactor");
  lua_pushliteral(L, "mousewheel");
  lua_gettable(L, -2);

  if (lua_isfunction(L, -1)) { 
    lua_pushinteger(L, x); nargs++;
    lua_pushinteger(L, y); nargs++;
    lua_pushinteger(L, delta); nargs++;
    lua_pushinteger(L, step); nargs++;
    lua_pushboolean(L, alt); nargs++;
    lua_pushboolean(L, ctrl); nargs++;
    lua_pushboolean(L, shift); nargs++;

    docall(L, nargs, 0);
    lua_pop(L, 1);
  }
  else {
    lua_pop(L, 2);
  }
}

void reactor_mousemove(int x, int y, int alt, int ctrl, int shift) {
  int nargs = 0;
  lua_getglobal(L, "reactor");
  lua_pushliteral(L, "mousemove");
  lua_gettable(L, -2);

  if (lua_isfunction(L, -1)) { 
    lua_pushinteger(L, x ); nargs++;
    lua_pushinteger(L, y ); nargs++;

    docall(L, nargs, 0);
    lua_pop(L, 1);
  }
  else {
    lua_pop(L, 2);
  }
}

void reactor_char(int c) {
  int nargs = 0;
  lua_getglobal(L, "reactor");
  lua_pushliteral(L, "character");
  lua_gettable(L, -2);

  if (lua_isfunction(L, -1)) { 
    lua_pushfstring(L, "%c", c); nargs++;

    docall(L, nargs, 0);
    lua_pop(L, 1);
  }
  else {
    lua_pop(L, 2);
  }
}

void reactor_mouseexit(void) {
  //TODO
}

void reactor_mouseenter(void) {
  //TODO
}

void reactor_keydown(const char* key, int alt, int ctrl, int shift) {
  int nargs = 0;
  lua_getglobal(L, "reactor");
  lua_pushliteral(L, "keydown");
  lua_gettable(L, -2);

  if (lua_isfunction(L, -1)) { 
    lua_pushstring(L, key); nargs++;        
    lua_pushboolean(L, alt); nargs++;
    lua_pushboolean(L, ctrl); nargs++;
    lua_pushboolean(L, shift); nargs++;
    docall(L, nargs, 0);
    lua_pop(L, 1);
  }
  else {
    lua_pop(L, 2);
  }     
}

void reactor_keypress(const char* key, int alt, int ctrl, int shift) {
  int nargs = 0;
  lua_getglobal(L, "reactor");
  lua_pushliteral(L, "keypress");
  lua_gettable(L, -2);

  if (lua_isfunction(L, -1)) { 
    lua_pushstring(L, key); nargs++;        
    lua_pushboolean(L, alt); nargs++;
    lua_pushboolean(L, ctrl); nargs++;
    lua_pushboolean(L, shift); nargs++;
    docall(L, nargs, 0);
    lua_pop(L, 1);
  }
  else {
    lua_pop(L, 2);
  }     
}

void reactor_keyup(const char* key, int alt, int ctrl, int shift) {
  int nargs = 0;
  lua_getglobal(L, "reactor");
  lua_pushliteral(L, "keyup");
  lua_gettable(L, -2);

  if (lua_isfunction(L, -1)) { 
    lua_pushstring(L, key); nargs++;        
    lua_pushboolean(L, alt); nargs++;
    lua_pushboolean(L, ctrl); nargs++;
    lua_pushboolean(L, shift); nargs++;
    docall(L, nargs, 0);
    lua_pop(L, 1);
  }
  else {
    lua_pop(L, 2);
  }     
}

void reactor_paint(void) {
  DBG_ASSERT(L);
  lua_getglobal(L, "reactor");
  lua_pushliteral(L, "draw");
  lua_gettable(L, -2);
     
  if (lua_isfunction(L, -1)) { 
    if (docall(L, 0, 0)) {
      reactor_driver_quit();
    }
    lua_pop(L, 1);
  }
  else {
    lua_pop(L, 2);
  }
}

void reactor_update(void) {
  DBG_ENTER();
  DBG_ASSERT(L);
  
  

  lua_getglobal(L, "reactor");
  lua_pushliteral(L, "update");
  lua_gettable(L, -2);

  if (lua_isfunction(L, -1)) { 	  
    docall(L, 0, 0);
    lua_pop(L, 1);
  }
  else {
    lua_pop(L, 2);
  }
  
  lua_getglobal(L, "reactor");
  lua_getfield(L, -1, "tick");  

  if (lua_isfunction(L, -1)) { 	    
    lua_pushnumber(L, reactor_driver_millis()); 
    docall(L, 1, 0);
    lua_pop(L, 1);
  }
  else {
    lua_pop(L, 2);
  }

  DBG_RETURN_VOID();
}

static int reactor_timermillis_L(lua_State* L) {
  lua_pushnumber(L, reactor_driver_millis());  
  return 1;
}

static int reactor_quit_L(lua_State* L) {
  reactor_driver_quit();
  return 0;
}

static int reactor_getsize_L(lua_State* L) {
  lua_pushnumber(L, reactor.w);
  lua_pushnumber(L, reactor.h);
  return 2;
}

static int reactor_localtime_L(lua_State* L) {
  int h, m, s, ms;
  reactor_driver_localtime(&h, &m, &s, &ms);
  lua_pushnumber(L, h);
  lua_pushnumber(L, m);
  lua_pushnumber(L, s);
  lua_pushnumber(L, ms);
  return 4;
}

static int reactor_systemtime_L(lua_State* L) {
  int h, m, s, ms;
  reactor_driver_systemtime(&h, &m, &s, &ms);
  lua_pushnumber(L, h);
  lua_pushnumber(L, m);
  lua_pushnumber(L, s);
  lua_pushnumber(L, ms);
  return 4;
}

static int reactor_fullscreen_L(lua_State* L) {  
  reactor_driver_fullscreen(lua_toboolean(L, 1));
  return 0;
}

static int luaopen_reactor(lua_State* L) 
{
  static const luaL_reg reactor_L[] = {
    {"quit", reactor_quit_L},  
    {"timermillis", reactor_timermillis_L},
    {"localtime", reactor_localtime_L},        
    {"systemtime", reactor_systemtime_L},        
    {"getsize", reactor_getsize_L},
    {"fullscreen", reactor_fullscreen_L},        
    {0, 0}
  };

  DBG_ENTER();

  luaL_register(L, "reactor", reactor_L);

  lua_pushliteral(L, "w");
  lua_pushnumber(L, reactor.w);
  lua_settable(L, -3);

  lua_pushliteral(L, "h");
  lua_pushnumber(L, reactor.h);
  lua_settable(L, -3);
  
  lua_pushliteral(L, "graphics");
  luaopen_reactor_graphics(L);
  lua_settable(L, -3);

 /* lua_pushliteral(L, "clipboard");
  luaopen_reactor_clipboard(L);
  lua_settable(L, -3);*/

  luaopen_cairo(L); 
 
  DBG_RETURN(0);
}

void reactor_init( int argc, char* argv[] ) {
  reactor_driver_get_windowrect(&reactor.x, &reactor.y, &reactor.w, &reactor.h);  

  L = lua_open(); 
  luaL_openlibs(L);

  lua_pushcfunction(L, traceback);
  lua_setglobal(L, "errorfunc");

  lua_pushcfunction(L, luaopen_reactor);  
  docall(L, 0, 0);

  if (luaL_loadfile(L, argv[1])) {
    printf("%s", lua_tostring(L, -1));
    lua_pop(L, 1);  
  }
  else {
    int i = 0;
    for (i=2; i<argc; i++) {
      lua_pushstring(L, argv[i]);
    }
    docall(L, i-2, 0);
  }
}

void reactor_exit(void) {
  lua_close(L);
}

/*============================================================================================================================================================*/
/*                                                                                                                                                            */
/*============================================================================================================================================================*/
/*       1         2         3         4         5         6         7         8         9         0         1         2         3         4         5        */
/*345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678*/
/*============================================================================================================================================================*/
