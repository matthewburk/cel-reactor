
/*============================================================================================================================================================*/
/*                                                                                                                                                            */
/*============================================================================================================================================================*/
/*       1         2         3         4         5         6         7         8         9         0         1         2         3         4         5        */
/*345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678*/
/*============================================================================================================================================================*/

#include <stdlib.h>
#include <toolkits/app/context.h>
#include <toolkits/app/display.h>
#include <toolkits/app/gl.h>
#include <toolkits/app/window.h>
#include <toolkits/dbg/debug.h>
#include <toolkits/gfx/font.h>
#include <toolkits/gfx/graphics.h>
#include <toolkits/gfx/image.h>
#include <toolkits/gfx/texture.h>
#include <toolkits/mat/vector.h>
#include <toolkits/sys/string.h>
#include <toolkits/sys/timer.h>
#include "reactor.h"
#include "lua_cairo.h"
#include <signal.h>
#include <math.h>
#include <windows.h>

#define M_PI           3.14159265358979323846

struct reactor reactor = {0};
static lua_State* L;
static char* keymap[512] = {0};

static void reactor_update(lua_State* L);
static void reactor_render(lua_State* L);
static void appeventreactor( const app_event_t* event, void* userdata );
static void resizeviewport( uint32_t width, uint32_t height );
static int reactor_quit(lua_State* L);
static int reactor_run(lua_State* L);
static int luaopen_reactor(lua_State* L);

#define loadkey(key, string) keymap[key] = string
static void loadkeymap() {
  loadkey(APP_KEYBOARDKEY_UNKNOWN, "undefined");
  loadkey(APP_KEYBOARDKEY_BACKSPACE, "backspace");
  loadkey(APP_KEYBOARDKEY_TAB, "tab");
  loadkey(APP_KEYBOARDKEY_ENTER, "return");
  loadkey(APP_KEYBOARDKEY_PAUSE, "pause");
  loadkey(APP_KEYBOARDKEY_ESCAPE, "escape");
  loadkey(APP_KEYBOARDKEY_SPACE, " ");
  loadkey(APP_KEYBOARDKEY_APOSTROPHE, "'");
  loadkey(APP_KEYBOARDKEY_COMMA, ",");
  loadkey(APP_KEYBOARDKEY_MINUS, "-");
  loadkey(APP_KEYBOARDKEY_PERIOD, ".");
  loadkey(APP_KEYBOARDKEY_SLASH, "/");
  loadkey(APP_KEYBOARDKEY_0, "0");
  loadkey(APP_KEYBOARDKEY_1, "1");
  loadkey(APP_KEYBOARDKEY_2, "2");
  loadkey(APP_KEYBOARDKEY_3, "3");
  loadkey(APP_KEYBOARDKEY_4, "4");
  loadkey(APP_KEYBOARDKEY_5, "5");
  loadkey(APP_KEYBOARDKEY_6, "6");
  loadkey(APP_KEYBOARDKEY_7, "7");
  loadkey(APP_KEYBOARDKEY_8, "8");
  loadkey(APP_KEYBOARDKEY_9, "9");
  loadkey(APP_KEYBOARDKEY_SEMICOLON, ";");
  loadkey(APP_KEYBOARDKEY_EQUAL, "=");
  loadkey(APP_KEYBOARDKEY_A, "a");
  loadkey(APP_KEYBOARDKEY_B, "b");
  loadkey(APP_KEYBOARDKEY_C, "c");
  loadkey(APP_KEYBOARDKEY_D, "d");
  loadkey(APP_KEYBOARDKEY_E, "e");
  loadkey(APP_KEYBOARDKEY_F, "f");
  loadkey(APP_KEYBOARDKEY_G, "g");
  loadkey(APP_KEYBOARDKEY_H, "h");
  loadkey(APP_KEYBOARDKEY_I, "i");
  loadkey(APP_KEYBOARDKEY_J, "j");
  loadkey(APP_KEYBOARDKEY_K, "k");
  loadkey(APP_KEYBOARDKEY_L, "l");
  loadkey(APP_KEYBOARDKEY_M, "m");
  loadkey(APP_KEYBOARDKEY_N, "n");
  loadkey(APP_KEYBOARDKEY_O, "o");
  loadkey(APP_KEYBOARDKEY_P, "p");
  loadkey(APP_KEYBOARDKEY_Q, "q");
  loadkey(APP_KEYBOARDKEY_R, "r");
  loadkey(APP_KEYBOARDKEY_S, "s");
  loadkey(APP_KEYBOARDKEY_T, "t");
  loadkey(APP_KEYBOARDKEY_U, "u");
  loadkey(APP_KEYBOARDKEY_V, "v");
  loadkey(APP_KEYBOARDKEY_W, "w");
  loadkey(APP_KEYBOARDKEY_X, "x");
  loadkey(APP_KEYBOARDKEY_Y, "y");
  loadkey(APP_KEYBOARDKEY_Z, "z");
  loadkey(APP_KEYBOARDKEY_OPENBRACKET, "[");
  loadkey(APP_KEYBOARDKEY_BACKSLASH, "\\");
  loadkey(APP_KEYBOARDKEY_CLOSEBRACKET, "]");
  loadkey(APP_KEYBOARDKEY_GRAVEACCENT, "`");
  loadkey(APP_KEYBOARDKEY_DELETE, "delete");
  loadkey(APP_KEYBOARDKEY_INSERT, "insert");
  loadkey(APP_KEYBOARDKEY_HOME, "home");
  loadkey(APP_KEYBOARDKEY_END, "end");
  loadkey(APP_KEYBOARDKEY_PAGEUP, "pageup");
  loadkey(APP_KEYBOARDKEY_PAGEDOWN, "pagedown");
  loadkey(APP_KEYBOARDKEY_UPARROW, "up");
  loadkey(APP_KEYBOARDKEY_DOWNARROW, "down");
  loadkey(APP_KEYBOARDKEY_LEFTARROW, "left");
  loadkey(APP_KEYBOARDKEY_RIGHTARROW, "right");
  loadkey(APP_KEYBOARDKEY_F1, "f1");
  loadkey(APP_KEYBOARDKEY_F2, "f2");
  loadkey(APP_KEYBOARDKEY_F3, "f3");
  loadkey(APP_KEYBOARDKEY_F4, "f4t");
  loadkey(APP_KEYBOARDKEY_F5, "f5");
  loadkey(APP_KEYBOARDKEY_F6, "f6");
  loadkey(APP_KEYBOARDKEY_F7, "f7");
  loadkey(APP_KEYBOARDKEY_F8, "f8");
  loadkey(APP_KEYBOARDKEY_F9, "f9");
  loadkey(APP_KEYBOARDKEY_F10, "f10");
  loadkey(APP_KEYBOARDKEY_F11, "f11");
  loadkey(APP_KEYBOARDKEY_F12, "f12");
  loadkey(APP_KEYBOARDKEY_PRINTSCREEN, "print");
  loadkey(APP_KEYBOARDKEY_SCROLLLOCK, "scrollock");
  loadkey(APP_KEYBOARDKEY_NP0, "kp0");
  loadkey(APP_KEYBOARDKEY_NP1, "kp1");
  loadkey(APP_KEYBOARDKEY_NP2, "kp2");
  loadkey(APP_KEYBOARDKEY_NP3, "kp3");
  loadkey(APP_KEYBOARDKEY_NP4, "kp4");
  loadkey(APP_KEYBOARDKEY_NP5, "kp5");
  loadkey(APP_KEYBOARDKEY_NP6, "kp6");
  loadkey(APP_KEYBOARDKEY_NP7, "kp7");
  loadkey(APP_KEYBOARDKEY_NP8, "kp8");
  loadkey(APP_KEYBOARDKEY_NP9, "kp9");
  loadkey(APP_KEYBOARDKEY_ADD, "kp+");
  loadkey(APP_KEYBOARDKEY_SUBTRACT, "kp-");
  loadkey(APP_KEYBOARDKEY_MULTIPLY, "kp*");
  loadkey(APP_KEYBOARDKEY_DIVIDE, "kp/");
  loadkey(APP_KEYBOARDKEY_CAPSLOCK, "capslock");
  loadkey(APP_KEYBOARDKEY_NUMLOCK, "numlock");
  loadkey(APP_KEYBOARDKEY_SHIFT, "shift");
  loadkey(APP_KEYBOARDKEY_CTRL, "ctrl");
  loadkey(APP_KEYBOARDKEY_ALT, "alt");  
}

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

static int docall (lua_State *L, int narg, int nresults) {
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


static void appeventreactor( const app_event_t* event, void* userdata )
{
  app_bounds_t bounds = {0, 0, 1280, 1024};
  int nargs = 0;
  int ltop;

  DBG_ENTER();

  DBG_ASSERT( event );

  ltop = lua_gettop(L);

  switch ( event->kind ) 
  {
    case APP_EVENTKIND_DISPLAYCHANGE:
    {
      if ( APP_WINDOWSTYLE_NOBORDER == app_window_getstyle( event->displayevent.window ) ) {
        app_display_getbounds( event->displayevent.display, &bounds );
        app_window_setbounds( event->displayevent.window, &bounds );
      }

      lua_getglobal(L, "reactor");
      lua_pushliteral(L, "displaychanged");
      lua_gettable(L, -2);
     
      if (lua_isfunction(L, -1)) { 
        docall(L, nargs, 0);     
        //TODO should I pop like everywhere else?
      }
      else {
        lua_pop(L, 2);
      }

      DBG_RETURN_VOID();
    }

    case APP_EVENTKIND_KEYBOARDPRESS:
    {
      lua_getglobal(L, "reactor");
      lua_pushliteral(L, "keypressed");
      lua_gettable(L, -2);
     
      if (lua_isfunction(L, -1)) { 
        lua_pushstring(L, keymap[event->keyboardevent.key]); nargs++;        
        lua_pushboolean(L, event->keyboardevent.alt); nargs++;
        lua_pushboolean(L, event->keyboardevent.ctrl); nargs++;
        lua_pushboolean(L, event->keyboardevent.shift); nargs++;
        lua_pushboolean(L, event->keyboardevent.repeat); nargs++;

        docall(L, nargs, 0);
        lua_pop(L, 1);
      }
      else {
        lua_pop(L, 2);
      }
      DBG_RETURN_VOID();
    }

    case APP_EVENTKIND_KEYBOARDRELEASE:
    {
      lua_getglobal(L, "reactor");
      lua_pushliteral(L, "keyreleased");
      lua_gettable(L, -2);
     
      if (lua_isfunction(L, -1)) { 
        lua_pushstring(L, keymap[event->keyboardevent.key]); nargs++;
        lua_pushboolean(L, event->keyboardevent.alt); nargs++;
        lua_pushboolean(L, event->keyboardevent.ctrl); nargs++;
        lua_pushboolean(L, event->keyboardevent.shift); nargs++;


        docall(L, nargs, 0);
        lua_pop(L, 1);
      }
      else {
        lua_pop(L, 2);
      }
      DBG_RETURN_VOID();
    }

    case APP_EVENTKIND_MOUSEDOUBLECLICK:
    case APP_EVENTKIND_MOUSEPRESS:
    {
      lua_getglobal(L, "reactor");
      lua_pushliteral(L, "mousepressed");
      lua_gettable(L, -2);
     
      if (lua_isfunction(L, -1)) { 
        lua_pushinteger(L, event->mouseevent.point.x ); nargs++;
        lua_pushinteger(L, event->mouseevent.point.y ); nargs++;
        lua_pushinteger(L, event->mouseevent.button); nargs++;
        lua_pushboolean(L, event->mouseevent.alt); nargs++;
        lua_pushboolean(L, event->mouseevent.ctrl); nargs++;
        lua_pushboolean(L, event->mouseevent.shift); nargs++;

        docall(L, nargs, 0);
        lua_pop(L, 1);
      }
      else {
        lua_pop(L, 2);
      }

      DBG_RETURN_VOID();
    }

    case APP_EVENTKIND_MOUSERELEASE:
    {
      lua_getglobal(L, "reactor");
      lua_pushliteral(L, "mousereleased");
      lua_gettable(L, -2);
     
      if (lua_isfunction(L, -1)) { 
        lua_pushinteger(L, event->mouseevent.point.x ); nargs++;
        lua_pushinteger(L, event->mouseevent.point.y ); nargs++;
        lua_pushinteger(L, event->mouseevent.button); nargs++;
        lua_pushboolean(L, event->mouseevent.alt); nargs++;
        lua_pushboolean(L, event->mouseevent.ctrl); nargs++;
        lua_pushboolean(L, event->mouseevent.shift); nargs++;

        docall(L, nargs, 0);
        lua_pop(L, 1);
      }
      else {
        lua_pop(L, 2);
      }

      DBG_RETURN_VOID();
    }

    case APP_EVENTKIND_MOUSEWHEEL:
    {
      lua_getglobal(L, "reactor");
      lua_pushliteral(L, "mousewheel");
      lua_gettable(L, -2);
     
      if (lua_isfunction(L, -1)) { 
        lua_pushinteger(L, event->mouseevent.wheel.delta); nargs++;
        lua_pushinteger(L, event->mouseevent.wheel.step); nargs++;
        lua_pushboolean(L, event->mouseevent.alt); nargs++;
        lua_pushboolean(L, event->mouseevent.ctrl); nargs++;
        lua_pushboolean(L, event->mouseevent.shift); nargs++;

        docall(L, nargs, 0);
        lua_pop(L, 1);
      }
      else {
        lua_pop(L, 2);
      }

      DBG_RETURN_VOID();
    }

    case APP_EVENTKIND_MOUSEMOVE:
    {
      lua_getglobal(L, "reactor");
      lua_pushliteral(L, "mousemove");
      lua_gettable(L, -2);
     
      if (lua_isfunction(L, -1)) { 
        lua_pushinteger(L, event->mouseevent.point.x ); nargs++;
        lua_pushinteger(L, event->mouseevent.point.y ); nargs++;

        docall(L, nargs, 0);
        lua_pop(L, 1);
      }
      else {
        lua_pop(L, 2);
      }

      DBG_RETURN_VOID();
    }

    case APP_EVENTKIND_KEYBOARDCHARACTER:
    {
      lua_getglobal(L, "reactor");
      lua_pushliteral(L, "character");
      lua_gettable(L, -2);
     
      if (lua_isfunction(L, -1)) { 
        lua_pushfstring(L, "%c", event->keyboardevent.character); nargs++;
      
        docall(L, nargs, 0);
        lua_pop(L, 1);
      }
      else {
        lua_pop(L, 2);
      }

      DBG_RETURN_VOID();
    }    

    case APP_EVENTKIND_CLIPBOARDCOPY:
    {
    
      lua_getglobal(L, "reactor");
      lua_pushliteral(L, "command");
      lua_gettable(L, -2);
     
      if (lua_isfunction(L, -1)) { 
        lua_pushliteral(L, "copy"); nargs++;
      
        docall(L, nargs, 0);
        lua_pop(L, 1);
      }
      else {
        lua_pop(L, 2);
      }

      DBG_RETURN_VOID();
    }

    case APP_EVENTKIND_CLIPBOARDCUT:
    {
    
      lua_getglobal(L, "reactor");
      lua_pushliteral(L, "command");
      lua_gettable(L, -2);
     
      if (lua_isfunction(L, -1)) { 
        lua_pushliteral(L, "cut"); nargs++;
      
        docall(L, nargs, 0);
        lua_pop(L, 1);
      }
      else {
        lua_pop(L, 2);
      }

      DBG_RETURN_VOID();
    }
    case APP_EVENTKIND_CLIPBOARDPASTE:
    {
      lua_getglobal(L, "reactor");
      lua_pushliteral(L, "command");
      lua_gettable(L, -2);
     
      if (lua_isfunction(L, -1)) { 
        lua_pushliteral(L, "paste"); nargs++;
      
        docall(L, nargs, 0);
        lua_pop(L, 1);
      }
      else {
        lua_pop(L, 2);
      }

      DBG_RETURN_VOID();
    }

    case APP_EVENTKIND_WINDOWCLOSE:
    {
      app_window_quit( event->windowevent.window );

      DBG_RETURN_VOID();
    }

    case APP_EVENTKIND_WINDOWCREATE:
    {
      app_window_setvisible( event->windowevent.window, BTRUE );

      //TODO should call reactor.load here, not in windowshow
      DBG_RETURN_VOID();
    }

    case APP_EVENTKIND_WINDOWPAINT:
    {
      reactor_render(L);
      DBG_RETURN_VOID();
    }

    case APP_EVENTKIND_WINDOWRESIZE:
    {
      reactor.w = event->windowevent.bounds.width;
      reactor.h = event->windowevent.bounds.height;
      //printf("reactor.w, reactor.h = (%d, %d)", reactor.w, reactor.h);
      resizeviewport(reactor.w, reactor.h);

      if (!reactor.loaded) {
        DBG_RETURN_VOID();
      }

      lua_getglobal(L, "reactor");
      lua_pushliteral(L, "resized");
      lua_gettable(L, -2);
     
      if (lua_isfunction(L, -1)) { 
        lua_pushinteger(L, reactor.w ); nargs++;
        lua_pushinteger(L, reactor.h ); nargs++;

        docall(L, nargs, 0);
        lua_pop(L, 1);
      }
      else {
        lua_pop(L, 2);
      }

      DBG_RETURN_VOID();
    }

    case APP_EVENTKIND_WINDOWSHOW:
    {
      reactor.w = event->windowevent.bounds.width;
      reactor.h = event->windowevent.bounds.height;
      resizeviewport(reactor.w, reactor.h);

      if (reactor.loaded) {
        DBG_RETURN_VOID();
      }
      //TODO should move this somewhere else
      lua_getglobal(L, "reactor");
      lua_pushliteral(L, "load");
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

      reactor.loaded = 1;

      DBG_RETURN_VOID();
    }
  }

  DBG_RETURN_VOID();
}

static void reactor_update(lua_State* L)
{
  DBG_ENTER();

  if (!reactor.loaded) {
    return;
  }

  //TODO store reference to reactor instead of using a string every time
  lua_getglobal(L, "reactor");
  lua_pushliteral(L, "update");
  lua_gettable(L, -2);

  if (lua_isfunction(L, -1)) { 
	  lua_pushnumber(L, reactor.fps);
    docall(L, 1, 0);
    lua_pop(L, 1);
  }
  else {
    lua_pop(L, 2);
  }

  //printf("from C %d\n", lua_gc(L, LUA_GCCOUNT, 0));

  DBG_RETURN_VOID();
}

static void reactor_render(lua_State* L)
{
  DBG_ENTER();

  if (!reactor.loaded) {
    return;
  }

  //glScissor(0, 0, reactor.w, reactor.h);
  //glClear( GL_COLOR_BUFFER_BIT );

  lua_getglobal(L, "reactor");
  lua_pushliteral(L, "draw");
  lua_gettable(L, -2);
     
  if (lua_isfunction(L, -1)) { 
    if (docall(L, 0, 0)) {
      reactor_quit(L);
    }
    lua_pop(L, 1);
  }
  else {
    lua_pop(L, 2);
  }

  //aka swap buffers
  app_window_present(reactor.window);

  DBG_RETURN_VOID();
}

static void resizeviewport( uint32_t width, uint32_t height )
{
  DBG_ENTER();

  glViewport( 0, 0, width, height );

  glMatrixMode( GL_PROJECTION );
  glLoadIdentity();
  glOrtho( 0.0f, (GLfloat)width, (GLfloat)height, 0.0f, -1.0f, 1.0f );

  glMatrixMode( GL_MODELVIEW );
  glLoadIdentity();

  DBG_RETURN_VOID();
}

static int reactor_timermillis(lua_State* L)
{
  DBG_ENTER();
  lua_pushnumber(L, timeGetTime());  
  DBG_RETURN(1);
}


static int reactor_quit(lua_State* L)
{
  DBG_ENTER();
  app_window_quit(reactor.window);
  DBG_RETURN(0);
}

static int reactor_localtime(lua_State* L) {
  SYSTEMTIME time;
  GetLocalTime(&time);

  lua_pushnumber(L, time.wHour);
  lua_pushnumber(L, time.wMinute);
  lua_pushnumber(L, time.wSecond);
  lua_pushnumber(L, time.wMilliseconds);
  return 4;
}


static int reactor_run(lua_State* L) 
{
  app_bounds_t bounds = {0, 0, 1280, 1024};
  app_pixelformat_t format = {8, 8, 8, 8, 32};
  size_t currtime = 0;
  size_t prevtime = 0;
  int frames = 0;

  int message = LUA_NOREF;
  int param = LUA_NOREF;

  DBG_ENTER();

  reactor.window = app_window_create( "reactor", APP_WINDOWSTYLE_RESIZEBORDER, &bounds, &format );
  reactor.context = app_context_create( reactor.window );  
  reactor.timer = sys_timer_create();

  app_window_addlistener( reactor.window, appeventreactor, &reactor );

  //rtk_pushstate2d(900, 600);
  //glDisable(GL_SCISSOR_TEST);
  //glScissor( 0, 0, 800, 600 );
  //glClearColor(1, 1, 1, 1);

  if (luaL_loadfile(L, luaL_checkstring(L, 1))) {
    printf("%s", lua_tostring(L, -1));
    lua_pop(L, 1);  
  }

  docall(L, 0, 0);

  while ( app_window_listen( reactor.window ) ) {
    if ( app_window_isactive( reactor.window ) ) {
      frames++;

      currtime = timeGetTime();

      if ( 1000 < ( currtime - prevtime ) ) {
        reactor.fps = frames / 1;
        frames = 0;
        prevtime = currtime;
      }

      reactor_update(L);
      reactor_render(L);
    }
    else {
      if ( !app_window_wait( reactor.window ) ) {
        break;
      }
    }    
  } 

  sys_timer_destroy(reactor.timer);  
  app_context_destroy( reactor.context );
  app_window_destroy( reactor.window );

  DBG_RETURN(0);
}

static int luaopen_reactor(lua_State* L) 
{
  static const luaL_reg reactor_L[] = {
    {"quit", reactor_quit},  
    {"timermillis", reactor_timermillis},
    {"localtime", reactor_localtime},    
    {0, 0}
  };

  DBG_ENTER();

  luaL_register(L, "reactor", reactor_L);
  
  lua_pushliteral(L, "graphics");
  luaopen_reactor_graphics(L);
  lua_settable(L, -3);

  lua_pushliteral(L, "clipboard");
  luaopen_reactor_clipboard(L);
  lua_settable(L, -3);

  luaopen_cairo(L);
 
  DBG_RETURN(0);
}

int main( int argc, char* argv[] )
{
  if (argc > 2) {
    DBG_PUSH(argv[2]);
  }

  DBG_ENTER();

  loadkeymap();

  L = lua_open(); 
  luaL_openlibs(L);

  lua_pushcfunction(L, traceback);
  lua_setglobal(L, "errorfunc");

  {
    lua_pushcfunction(L, luaopen_reactor);    
    docall(L, 0, 0);
  }
  
  {
    timeBeginPeriod(1);
    lua_pushcfunction(L, reactor_run);
    lua_pushstring(L, argv[1]);
    docall(L, 1, 0);
    timeEndPeriod(1);
  }

  lua_close(L);

  DBG_RETURN( EXIT_SUCCESS );
}
/*============================================================================================================================================================*/
/*                                                                                                                                                            */
/*============================================================================================================================================================*/
/*       1         2         3         4         5         6         7         8         9         0         1         2         3         4         5        */
/*345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678*/
/*============================================================================================================================================================*/
