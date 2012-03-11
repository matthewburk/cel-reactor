#include <stdlib.h>
#include <debug.h>
#include "gl.h"
#include "reactor_graphics.h"
#include "lua_cairo.h"

void checkself_cairo_surface(lua_State* L, reactor_cairo_surface_t** rpp, cairo_surface_t** pp) {
  *rpp = luaL_checkudata(L, 1, "reactor_cairo_surface_t");
  *pp = (*rpp)->surface;
  if (!*pp) {
    luaL_argerror(L, 1, "cairo surface is invalid becuase it has been destroyed");
  }
}


reactor_cairo_surface_t* check_reactor_cairo_surface(lua_State* L, int arg) {
  reactor_cairo_surface_t* rsurface = luaL_checkudata(L, arg, "reactor_cairo_surface_t");
  if (!rsurface->surface) {
    luaL_argerror(L, arg, "cairo surface is invalid becuase it has been destroyed");
  }
  return rsurface;
}

cairo_surface_t* check_cairo_surface(lua_State* L, int arg) {
  reactor_cairo_surface_t* rsurface = luaL_checkudata(L, arg, "reactor_cairo_surface_t");
  if (!rsurface->surface) {
    luaL_argerror(L, arg, "cairo surface is invalid becuase it has been destroyed");
  }
  return rsurface->surface;
}

static int cairo_image_surface_create_L(lua_State* L) {  
  DBG_ENTER();
  {
    reactor_cairo_surface_t* rsurface = 0;  
    int w = luaL_checkint(L, 1);
    int h = luaL_checkint(L, 2);

    rsurface = lua_newuserdata(L, sizeof(reactor_cairo_surface_t));
    luaL_getmetatable(L, "reactor_cairo_surface_t");
    lua_setmetatable(L, -2);

    rsurface->surface = cairo_image_surface_create(CAIRO_FORMAT_ARGB32, w, h);
    rsurface->w = cairo_image_surface_get_width(rsurface->surface);
    rsurface->h = cairo_image_surface_get_height(rsurface->surface);
    rsurface->data = cairo_image_surface_get_data(rsurface->surface);    
  }
  DBG_RETURN(1);
}

static int cairo_image_surface_create_from_png_L(lua_State* L) {  
  DBG_ENTER();
  {
    reactor_cairo_surface_t* rsurface = 0;  
    const char* filename = luaL_checkstring(L, 1);
    
    rsurface = lua_newuserdata(L, sizeof(reactor_cairo_surface_t));
    luaL_getmetatable(L, "reactor_cairo_surface_t");
    lua_setmetatable(L, -2);

    rsurface->surface = cairo_image_surface_create_from_png(filename);

    {
      int status = cairo_surface_status(rsurface->surface);
      switch(status) {
        case CAIRO_STATUS_FILE_NOT_FOUND:
          return luaL_error(L, "file not found %s", filename);
        case CAIRO_STATUS_READ_ERROR:
          return luaL_error(L, "read error on file %s", filename);
        case CAIRO_STATUS_NO_MEMORY:
          return luaL_error(L, "no memory for file %s", filename);
      }
    }

    rsurface->w = cairo_image_surface_get_width(rsurface->surface);
    rsurface->h = cairo_image_surface_get_height(rsurface->surface);
    rsurface->data = cairo_image_surface_get_data(rsurface->surface);    
  }
  DBG_RETURN(1);
}

static int cairo_surface__gc_L(lua_State* L) {
  DBG_ENTER();
  {
    reactor_cairo_surface_t* rsurface = lua_touserdata(L, 1); 
    if (rsurface->surface)
      cairo_surface_destroy(rsurface->surface);    
  }
  DBG_RETURN(0);
}

static int cairo_surface_destroy_L(lua_State* L) {
  reactor_cairo_surface_t* rsurface = 0;
  cairo_surface_t* surface = 0;
  DBG_ENTER();
  checkself_cairo_surface(L, &rsurface, &surface);
  {
    rsurface->surface = 0;
    cairo_surface_destroy(surface);
  }
  DBG_RETURN(0);
}

static int cairo_surface_get_size_L(lua_State* L) {
  cairo_surface_t* surface = check_cairo_surface(L, 1);
  
  lua_pushnumber(L, cairo_image_surface_get_width(surface));
  lua_pushnumber(L, cairo_image_surface_get_height(surface));
  return 2;  
}

static int cairo_surface_write_to_png_L(lua_State* L) {
  cairo_surface_t* surface = check_cairo_surface(L, 1);
  int ok = cairo_surface_write_to_png(surface, luaL_checkstring(L, 2));
  lua_pushboolean(L, ok == CAIRO_STATUS_SUCCESS);
  return 1;  
}


void luaopen_cairo_surface(lua_State* L) {
  DBG_ENTER();
  {  
    static const luaL_reg surface_functions[] = {
      {"__gc", cairo_surface__gc_L},
      {"destroy", cairo_surface_destroy_L},    
      {"get_size", cairo_surface_get_size_L},   
      {"write_to_png", cairo_surface_write_to_png_L},   
      {NULL, NULL}
    }; 

    static const luaL_reg module_functions[] = {
      {"create", cairo_image_surface_create_L}, 
      {"create_from_png", cairo_image_surface_create_from_png_L}, 
      {"destroy", cairo_surface_destroy_L},      
      {"get_size", cairo_surface_get_size_L},    
      {"write_to_png", cairo_surface_write_to_png_L},    
      {NULL, NULL}
    };

    luaL_newmetatable(L, "reactor_cairo_surface_t");
    lua_pushvalue(L, -1);
    lua_setfield(L, -2, "__index");
    luaL_register(L, 0, surface_functions);
    lua_pop(L, 1);
    
    lua_newtable(L); 
    luaL_register(L, 0, module_functions);
  }
  DBG_RETURN_VOID();
}

////////////////////////////////
////////////////////////////////
////////////////////////////////
////////////////////////////////
////////////////////////////////
////////////////////////////////
////////////////////////////////
////////////////////////////////
////////////////////////////////
////////////////////////////////
////////////////////////////////
////////////////////////////////

//static int surface_clear(lua_State* L) {
//  surface_t* crs = 0;
//  cairo_t* cr = 0;
//  DBG_ENTER();  
//  crs = luaL_checkudata(L, 1, "reactor_cairo_surface");
//  cr = crs->cr;
//  cairo_set_source_rgb (cr, 
//    luaL_checknumber(L, 2),
//    luaL_checknumber(L, 3),
//    luaL_checknumber(L, 4));
//  cairo_paint (cr);
//  DBG_RETURN(0);
//}
//
//
//static int surface_copy_to_texture(lua_State* L) {
//  surface_t* crs = luaL_checkudata(L, 1, "reactor_cairo_surface");
//  texture_t* texture = lua_touserdata(L, 2);  
//
//  glBindTexture (GL_TEXTURE_2D, texture->id);
//  glTexSubImage2D(GL_TEXTURE_2D, 0, 0, 0, crs->w, crs->h, GL_BGRA, GL_UNSIGNED_BYTE, crs->data);
//  return 0;
//}
//
