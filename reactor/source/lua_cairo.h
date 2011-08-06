#ifndef reactor_lua_cairo_H
#define reactor_lua_cairo_H

#include <lua.h>
#include <lauxlib.h>
#include <lualib.h>
#include <cairo.h>

typedef struct reactor_cairo {
  cairo_t* cr;
} reactor_cairo_t;

typedef struct reactor_cairo_surface {
  cairo_surface_t* surface;
  unsigned char* data;
  int w;
  int h;
} reactor_cairo_surface_t;

typedef struct reactor_cairo_pattern {
  cairo_pattern_t* pattern;
} reactor_cairo_pattern_t;

typedef struct reactor_cairo_font_face {
  cairo_font_face_t* face;
} reactor_cairo_font_face_t;

void checkself_cairo(lua_State* L, reactor_cairo_t** rcr, cairo_t** cr);
void checkself_cairo_surface(lua_State* L, reactor_cairo_surface_t** rpp, cairo_surface_t** pp);
void checkself_cairo_pattern(lua_State* L, reactor_cairo_pattern_t** rpp, cairo_pattern_t** pp);
void checkself_cairo_font_face(lua_State* L, reactor_cairo_font_face_t** rpp, cairo_font_face_t** pp);

reactor_cairo_surface_t* check_reactor_cairo_surface(lua_State* L, int arg);

cairo_surface_t* check_cairo_surface(lua_State* L, int arg);
cairo_pattern_t* check_cairo_pattern(lua_State* L, int arg);
cairo_font_face_t* check_cairo_font_face(lua_State* L, int arg);

void create_reactor_cairo_pattern(lua_State* L, cairo_pattern_t* pattern);
void create_reactor_cairo_surface(lua_State* L, cairo_surface_t* surface);

void luaopen_cairo(lua_State* L);
void luaopen_cairo_surface(lua_State* L);
void luaopen_cairo_pattern(lua_State* L);
void luaopen_cairo_font_face(lua_State* L);

char* slant_options[];
char* weight_options[];
char* content_options[];
char* antialias_options[];
char* line_cap_options[];
char* line_join_options[];
char* operator_options[];

ptrdiff_t posrelat (ptrdiff_t pos, size_t len);
#endif
