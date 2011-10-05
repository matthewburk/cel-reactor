#ifndef reactor_graphics_H
#define reactor_graphics_H

#include "reactor.h"
#include "gl.h"
#include <lua.h>
#include <lauxlib.h>
#include <lualib.h>

#ifdef __cplusplus
extern "C" {
#endif

typedef struct texture {
  GLuint id;
  int w;
  int h;
} texture_t;

typedef struct texture_rect {
  texture_t* source;
  int x;
  int y;
  int w;
  int h;
} texture_rect_t;


void checkself_texture(lua_State* L, texture_t** rpp);

texture_t* check_texture(lua_State* L, int arg);

#ifdef __cplusplus
}
#endif

#endif