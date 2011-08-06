#ifndef reactor_H
#define reactor_H

#ifdef __cplusplus
extern "C" {
#endif

#include <toolkits/dbg/debug.h>
#include <toolkits/app/context.h>
#include <toolkits/gfx/graphics.h>
#include <toolkits/sys/timer.h>
#include <toolkits/aud/audio.h>
#include <toolkits/aud/device.h>
#include <lua.h>
#include <lauxlib.h>
#include <lualib.h>

struct reactor
{
  app_window_t* window;
  app_context_t* context;
  sys_timer_t* timer;
  aud_device_t* device;
  int loaded; 
  int w;
  int h;
  double fps;
};

extern struct reactor reactor;

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

int luaopen_reactor_clipboard(lua_State* L);
int luaopen_reactor_graphics(lua_State* L);
int luaopen_reactor_audio(lua_State* L);

#ifdef __cplusplus
}
#endif

#endif
