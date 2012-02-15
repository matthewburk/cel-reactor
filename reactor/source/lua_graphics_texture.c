#include <stdlib.h>
#include <debug.h>
#include "gl.h"
#include "reactor_graphics.h"
#include <math.h>
#include "lua_cairo.h"

GLuint texobj = 0;

void checkself_texture(lua_State* L, texture_t** rpp) {
  *rpp = luaL_checkudata(L, 1, "reactor_graphics_texture_t");  
  if (0 == (*rpp)->id) {
    luaL_argerror(L, 1, "texture is invalid becuase it has been destroyed");
  }
}

texture_t* check_texture(lua_State* L, int arg) {
  texture_t* texture = luaL_checkudata(L, arg, "reactor_graphics_texture_t");  
  if (0 == texture->id) {
    luaL_argerror(L, arg, "texture is invalid becuase it has been destroyed");
  }
  return texture;
}


static int graphics_texture_create_L(lua_State* L) {
  DBG_ENTER();
  {
    int w = 0;
    int h = 0;
    texture_t* texture = 0;  
    texture = lua_newuserdata(L, sizeof(texture_t));
    luaL_getmetatable(L, "reactor_graphics_texture_t");
    lua_setmetatable(L, -2);

    w = luaL_checkint(L, 1);
    h = luaL_checkint(L, 2);

    glGenTextures( 1, &texture->id );
    if (glGetError()) return luaL_error(L, "%d", glGetError());
    glBindTexture( GL_TEXTURE_2D, texture->id );
    texobj = texture->id;
    if (glGetError()) return luaL_error(L, "%d", glGetError());

    for ( texture->w = 1; texture->w < w; texture->w <<= 1 );
    for ( texture->h = 1; texture->h < h; texture->h <<= 1 );  

    texture->np2w = w;
    texture->np2h = h;

    glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP );
    if (glGetError()) return luaL_error(L, "%d", glGetError());
    glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP );
    if (glGetError()) return luaL_error(L, "%d", glGetError());
    glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR );
    if (glGetError()) return luaL_error(L, "%d", glGetError());
    glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR );
    if (glGetError()) return luaL_error(L, "%d", glGetError());

    glTexImage2D( GL_TEXTURE_2D, 0, GL_RGBA8, texture->w, texture->h, 0, GL_BGRA, GL_UNSIGNED_BYTE, 0 );
    if (glGetError()) return luaL_error(L, "%d", glGetError());
  }
  DBG_RETURN(1);
}

static int graphics_texture__gc_L(lua_State* L) {
  DBG_ENTER();
  {
  texture_t* texture = lua_touserdata(L, 1); 
  if (texture->id)
    glDeleteTextures(1, &texture->id);     
  }
  DBG_RETURN(0);
}

static int graphics_texture_destroy_L(lua_State* L) {
  texture_t* texture = 0;  
  DBG_ENTER();
  checkself_texture(L, &texture);
  {
    glDeleteTextures(1, &texture->id);
    texture->id = 0;
  }
  DBG_RETURN(0);
}

void luaopen_reactor_graphics_texture(lua_State* L) {
  DBG_ENTER();
  {  
    static const luaL_reg texture_functions[] = {
      {"__gc", graphics_texture__gc_L},
      {"destroy", graphics_texture_destroy_L},    
      {NULL, NULL}
    }; 

    static const luaL_reg module_functions[] = {
      {"create", graphics_texture_create_L}, 
      {"destroy", graphics_texture_destroy_L}, 
      {NULL, NULL}
    };

    luaL_newmetatable(L, "reactor_graphics_texture_t");
    lua_pushvalue(L, -1);
    lua_setfield(L, -2, "__index");
    luaL_register(L, 0, texture_functions);
    lua_pop(L, 1);
    
    lua_newtable(L); 
    luaL_register(L, 0, module_functions);
  }
  DBG_RETURN_VOID();
}