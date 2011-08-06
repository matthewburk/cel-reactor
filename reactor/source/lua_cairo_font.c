#include <stdlib.h>
#include <toolkits/dbg/debug.h>
#include <toolkits/app/gl.h>
#include <toolkits/gfx/graphics.h>
#include <toolkits/gfx/texture.h>
#include "reactor.h"
#include "lua_cairo.h"

void checkself_cairo_font_face(lua_State* L, reactor_cairo_font_face_t** rpp, cairo_font_face_t** pp) {
  *rpp = luaL_checkudata(L, 1, "reactor_cairo_font_face_t");
  *pp = (*rpp)->face;
  if (!*pp) {
    luaL_argerror(L, 1, "cairo font_face is invalid becuase it has been destroyed");
  }
}

cairo_font_face_t* check_cairo_font_face(lua_State* L, int arg) {
  reactor_cairo_font_face_t* rfont_face = luaL_checkudata(L, arg, "reactor_cairo_font_face_t");
  return rfont_face->face;
}

ptrdiff_t posrelat (ptrdiff_t pos, size_t len) {  
  return (pos>=0) ? pos : (ptrdiff_t)len+pos+1;
}

static int cairo_toy_font_face_create_L(lua_State* L) {
  DBG_ENTER();
  {
    reactor_cairo_font_face_t* rface = 0;
    rface = lua_newuserdata(L, sizeof(reactor_cairo_font_face_t));
    luaL_getmetatable(L, "reactor_cairo_font_face_t");
    lua_setmetatable(L, -2);

    rface->face = cairo_toy_font_face_create(luaL_checkstring(L, 1), luaL_checkoption (L, 2, "normal", slant_options), luaL_checkoption(L, 3, "normal", weight_options));   
  }
  DBG_RETURN(1);
}

static int cairo_font_face__gc_L(lua_State* L) {
  DBG_ENTER();
  {
    reactor_cairo_font_face_t* rface = lua_touserdata(L, 1); 
    if (rface->face)
      cairo_font_face_destroy(rface->face);    
  }
  DBG_RETURN(0);
}

static int cairo_font_face_destroy_L(lua_State* L) {
  reactor_cairo_font_face_t* rface = 0;
  cairo_font_face_t* face = 0;
  DBG_ENTER();
  checkself_cairo_font_face(L, &rface, &face);
  {
    rface->face = 0;
    cairo_font_face_destroy(face);
  }
  DBG_RETURN(0);
}

void luaopen_cairo_font_face(lua_State* L) {
  DBG_ENTER();
  {  
    static const luaL_reg font_face_functions[] = {
      {"__gc", cairo_font_face__gc_L},
      {"destroy", cairo_font_face_destroy_L},    
      {NULL, NULL}
    }; 

    static const luaL_reg module_functions[] = {
      {"face_create", cairo_toy_font_face_create_L}, 
      {"face_destroy", cairo_font_face_destroy_L},       
      {NULL, NULL}
    };

    luaL_newmetatable(L, "reactor_cairo_font_face_t");
    lua_pushvalue(L, -1);
    lua_setfield(L, -2, "__index");
    luaL_register(L, 0, font_face_functions);
    lua_pop(L, 1);
    
    lua_newtable(L); 
    luaL_register(L, 0, module_functions);
  }
  DBG_RETURN_VOID();
}