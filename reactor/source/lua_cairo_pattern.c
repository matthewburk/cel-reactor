#include <stdlib.h>
#include <debug.h>
#include "gl.h"
#include "reactor_graphics.h"
#include "lua_cairo.h"

void checkself_cairo_pattern(lua_State* L, reactor_cairo_pattern_t** rpp, cairo_pattern_t** pp) {
  *rpp = luaL_checkudata(L, 1, "reactor_cairo_pattern_t");
  *pp = (*rpp)->pattern;
  if (!*pp) {
    luaL_argerror(L, 1, "cairo pattern is invalid becuase it has been destroyed");
  }
}

cairo_pattern_t* check_cairo_pattern(lua_State* L, int arg) {
  reactor_cairo_pattern_t* rpattern = luaL_checkudata(L, arg, "reactor_cairo_pattern_t");
  return rpattern->pattern;
}

void create_reactor_cairo_pattern(lua_State* L, cairo_pattern_t* pattern) {
  DBG_ENTER();
  {
    reactor_cairo_pattern_t* rpattern = 0;  
    rpattern = lua_newuserdata(L, sizeof(reactor_cairo_pattern_t));
    luaL_getmetatable(L, "reactor_cairo_pattern_t");
    lua_setmetatable(L, -2);
    rpattern->pattern = pattern;
  }
  DBG_RETURN_VOID();
}

static int cairo_pattern_create_rgb_L(lua_State* L) {  
  DBG_ENTER();
  {
    reactor_cairo_pattern_t* rpattern = 0;  
    rpattern = lua_newuserdata(L, sizeof(reactor_cairo_pattern_t));
    luaL_getmetatable(L, "reactor_cairo_pattern_t");
    lua_setmetatable(L, -2);
    rpattern->pattern = cairo_pattern_create_rgb(luaL_checknumber(L, 1), luaL_checknumber(L, 2),luaL_checknumber(L, 3));
  }
  DBG_RETURN(1);
}

static int cairo_pattern_create_rgba_L(lua_State* L) {  
  DBG_ENTER();
  {
    reactor_cairo_pattern_t* rpattern = 0;  
    rpattern = lua_newuserdata(L, sizeof(reactor_cairo_pattern_t));
    luaL_getmetatable(L, "reactor_cairo_pattern_t");
    lua_setmetatable(L, -2);
    rpattern->pattern = cairo_pattern_create_rgba(luaL_checknumber(L, 1), luaL_checknumber(L, 2), luaL_checknumber(L, 3), luaL_checknumber(L, 4));
  }
  DBG_RETURN(1);
}

static int cairo_pattern_create_for_surface_L(lua_State* L) {  
  DBG_ENTER();
  {
    reactor_cairo_pattern_t* rpattern = 0;  
    rpattern = lua_newuserdata(L, sizeof(reactor_cairo_pattern_t));
    luaL_getmetatable(L, "reactor_cairo_pattern_t");
    lua_setmetatable(L, -2);
    rpattern->pattern = cairo_pattern_create_for_surface(check_cairo_surface(L, 1));
  }
  DBG_RETURN(1);
}

static int cairo_pattern_create_linear_L(lua_State* L) {  
  DBG_ENTER();
  {
    reactor_cairo_pattern_t* rpattern = 0;  
    rpattern = lua_newuserdata(L, sizeof(reactor_cairo_pattern_t));
    luaL_getmetatable(L, "reactor_cairo_pattern_t");
    lua_setmetatable(L, -2);
    rpattern->pattern = cairo_pattern_create_linear(luaL_checknumber(L, 1), luaL_checknumber(L, 2), luaL_checknumber(L, 3), luaL_checknumber(L, 4));
  }
  DBG_RETURN(1);
}

static int cairo_pattern_create_radial_L(lua_State* L) {  
  DBG_ENTER();
  {
    reactor_cairo_pattern_t* rpattern = 0;  
    rpattern = lua_newuserdata(L, sizeof(reactor_cairo_pattern_t));
    luaL_getmetatable(L, "reactor_cairo_pattern_t");
    lua_setmetatable(L, -2);
    rpattern->pattern = cairo_pattern_create_radial(luaL_checknumber(L, 1), luaL_checknumber(L, 2), luaL_checknumber(L, 3), luaL_checknumber(L, 4), luaL_checknumber(L, 5), luaL_checknumber(L, 6));
  }
  DBG_RETURN(1);
}

static int cairo_pattern__gc_L(lua_State* L) {
  DBG_ENTER();
  {
  reactor_cairo_pattern_t* rpattern = lua_touserdata(L, 1); 
  if (rpattern->pattern)
    cairo_pattern_destroy(rpattern->pattern);    
  }
  DBG_RETURN(0);
}

static int cairo_pattern_destroy_L(lua_State* L) {
  reactor_cairo_pattern_t* rpattern = 0;
  cairo_pattern_t* pattern = 0;
  DBG_ENTER();
  checkself_cairo_pattern(L, &rpattern, &pattern);
  {
    rpattern->pattern = 0;
    cairo_pattern_destroy(pattern);
  }
  DBG_RETURN(0);
}

static int cairo_pattern_add_color_stop_L(lua_State* L) {
  cairo_pattern_t* pattern = check_cairo_pattern(L, 1);
  double alpha = luaL_optnumber(L, 6, -3);

  if (alpha == -3) {
    cairo_pattern_add_color_stop_rgb(
      pattern,
      luaL_checknumber(L, 2),
      luaL_checknumber(L, 3),
      luaL_checknumber(L, 4),
      luaL_checknumber(L, 5));
  }
  else {
    cairo_pattern_add_color_stop_rgba(
      pattern,
      luaL_checknumber(L, 2),
      luaL_checknumber(L, 3),
      luaL_checknumber(L, 4),
      luaL_checknumber(L, 5),
      alpha);
  }

  return 0;
}


void luaopen_cairo_pattern(lua_State* L) {
  DBG_ENTER();
  {  
    static const luaL_reg pattern_functions[] = {
      {"__gc", cairo_pattern__gc_L},
      {"destroy", cairo_pattern_destroy_L},  
      {"add_color_stop", cairo_pattern_add_color_stop_L},
      {NULL, NULL}
    }; 

    static const luaL_reg module_functions[] = {
      {"create_rgb", cairo_pattern_create_rgb_L}, 
      {"create_rgba", cairo_pattern_create_rgba_L}, 
      {"create_for_surface", cairo_pattern_create_for_surface_L}, 
      {"create_linear", cairo_pattern_create_linear_L}, 
      {"create_radial", cairo_pattern_create_radial_L}, 
      {NULL, NULL}
    };

    luaL_newmetatable(L, "reactor_cairo_pattern_t");
    lua_pushvalue(L, -1);
    lua_setfield(L, -2, "__index");
    luaL_register(L, 0, pattern_functions);
    lua_pop(L, 1);
    
    lua_newtable(L); 
    luaL_register(L, 0, module_functions);
  }
  DBG_RETURN_VOID();
}