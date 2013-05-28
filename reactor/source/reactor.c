#if 0

#endif

#include <stdlib.h>
#include <signal.h>
#include <math.h>
#include <lua.h>
#include <lauxlib.h>
#include <lualib.h>
#include <assert.h>
#include <windows.h>
#include <windowsx.h>
#include <stdio.h>
#include "reactor.h"
#include "gl.h"

#define APP_WINDOW_CLASSNAME "reactor_window"
#define APP_WINDOW_CREATE ( WM_APP + 1 )
#define APP_WINDOW_QUIT ( WM_APP + 2 )
#define APP_WINDOW_REDRAW (WM_APP + 3)
#define APP_TICK (WM_APP + 4)

struct window window = {0};
static DWORD createtime;

static lua_State* L = 0;
static int windowref;
static int appref;

static int reactor_traceback (lua_State *L) {
  if (!lua_isstring(L, 1))  {
    return 1;  
  }

  lua_getglobal(L, "debug");

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

static int reactor_pcall(lua_State *L, int narg, int nresults) {
  int status;
  int top = lua_gettop(L);
  int base = top - narg;  /* function index */
  lua_getglobal(L, "reactor_traceback");
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


void reactor_window_setclipboard( const char* text )
{
  HGLOBAL hglobal = 0;  
  void* data = 0;
  int size = 0;

  if ( !OpenClipboard( window.hwnd ) ) {
    return;
  }

  EmptyClipboard();

  size = MultiByteToWideChar(CP_UTF8, 0, text, -1, NULL, 0);

  if ( !( hglobal = GlobalAlloc( GHND, size*sizeof(WCHAR)) ) ) {
    return;
  }

  if ( !( data = GlobalLock( hglobal ) ) ) {
    return;
  }

  MultiByteToWideChar(CP_UTF8, 0, text, -1, data, size);

  GlobalUnlock( hglobal );
  
  SetClipboardData( CF_UNICODETEXT, hglobal );

  CloseClipboard();
}

static int reactor_window_setclipboard_L( lua_State* L )
{
  reactor_window_setclipboard( luaL_checkstring( L, 1 ) );
  return( 0 );
}

void reactor_window_getclipboard( char** text )
{
  HGLOBAL hglobal = 0;
  char* buffer = 0;
  void* data = 0;

  if ( !IsClipboardFormatAvailable( CF_UNICODETEXT ) ) {
    return;
  }

  if ( !OpenClipboard( window.hwnd ) ) {
    return;
  }

  if ( !( hglobal = GetClipboardData( CF_UNICODETEXT ) ) ) {
    return;
  }

  if ( !( data = GlobalLock( hglobal ) ) ) {
    return;
  }

  {
	int size_needed = WideCharToMultiByte(CP_UTF8, 0, data, -1, NULL, 0, NULL, NULL);

	*text = (char*)malloc(size_needed);

	WideCharToMultiByte(CP_UTF8, 0, data, -1, *text, size_needed, NULL, NULL);
  }
    
  GlobalUnlock( hglobal );

  CloseClipboard();
}

static int reactor_window_getclipboard_L( lua_State* L ) {
  char* text = 0;
  luaL_Buffer b;

  reactor_window_getclipboard( &text );

  if ( text ) {
    luaL_buffinit( L, &b );
    luaL_addstring( &b, text );
    luaL_pushresult( &b );

    free( text );

    return( 1 );
  }

  return( 0 );
}



static unsigned long reactor_getelapsedtime(void) {
  return timeGetTime() - createtime;
}

static int reactor_getelapsedtime_L(lua_State* L) {
  lua_pushnumber(L, reactor_getelapsedtime());  
  return 1;
}

static int reactor_quit_L(lua_State* L) {
  PostQuitMessage(0);  
  return 0;
}

extern int luaopen_reactor_graphics(lua_State* L);
extern int luaopen_reactor_clipboard(lua_State* L);
extern int luaopen_cairo(lua_State* L);

static int window_redraw_L(lua_State* L) {
  if (!window.redraw) {
    window.redraw=1;
    PostMessage( window.hwnd, APP_WINDOW_REDRAW, 0, 0 );
  }
  return 0;
}

static int window_getclientrect_L(lua_State* L) {
  RECT rect;
  POINT point;
  GetClientRect(window.hwnd, &rect);
  ClientToScreen(window.hwnd, &point);  
  lua_pushnumber(L, point.x);
  lua_pushnumber(L, point.y);
  lua_pushnumber(L, rect.right-rect.left);
  lua_pushnumber(L, rect.bottom-rect.top);
  return 4;
}


void pushL_windowevent(const char* name) {
  int nargs = 0;
  if ( !strcmp(name, "create") ) {          
    return;
  }
  else if (!strcmp(name, "resize")  ){    
    lua_rawgeti(L, LUA_REGISTRYINDEX, windowref);
    lua_getfield(L, -1, "onresize");    
   
    if (lua_isfunction(L, -1)) { 
      lua_pushinteger(L, window.w); nargs++;
      lua_pushinteger(L, window.h); nargs++;
      reactor_pcall(L, nargs, 0);
      lua_pop(L, 1);
    }
    else {
      lua_pop(L, 2);
    }
  }
  else if (!strcmp(name, "show") ) {
  } 
}

void pushL_command(const char* command) {
  int nargs = 0;
  lua_rawgeti(L, LUA_REGISTRYINDEX, windowref);
  lua_getfield(L, -1, "oncommand");

  if (lua_isfunction(L, -1)) { 
    lua_pushstring(L, command); nargs++;
    reactor_pcall(L, nargs, 0);
    lua_pop(L, 1);
  }
  else {
    lua_pop(L, 2);
  }
}

void pushL_mousedblclick(int x, int y, const char* button, int alt, int ctrl, int shift) {
  int nargs = 0;
  lua_rawgeti(L, LUA_REGISTRYINDEX, windowref);
  lua_getfield(L, -1, "onmousedoubleclick");
 
  if (lua_isfunction(L, -1)) { 
    lua_pushstring(L, button); nargs++;
    lua_pushinteger(L, x ); nargs++;
    lua_pushinteger(L, y ); nargs++;
    
    lua_pushboolean(L, alt); nargs++;
    lua_pushboolean(L, ctrl); nargs++;
    lua_pushboolean(L, shift); nargs++;
    reactor_pcall(L, nargs, 0);
    lua_pop(L, 1);
  }
  else {
    lua_pop(L, 2);
  }
}

void pushL_mousedown(int x, int y, const char* button, int alt, int ctrl, int shift) {
  int nargs = 0;
  lua_rawgeti(L, LUA_REGISTRYINDEX, windowref);
  lua_getfield(L, -1, "onmousedown");
 
  if (lua_isfunction(L, -1)) { 
    lua_pushstring(L, button); nargs++;
    lua_pushinteger(L, x ); nargs++;
    lua_pushinteger(L, y ); nargs++;
    
    lua_pushboolean(L, alt); nargs++;
    lua_pushboolean(L, ctrl); nargs++;
    lua_pushboolean(L, shift); nargs++;
    reactor_pcall(L, nargs, 0);
    lua_pop(L, 1);
  }
  else {
    lua_pop(L, 2);
  }
}

void pushL_mouseup(int x, int y, const char* button, int alt, int ctrl, int shift) {
  int nargs = 0;
  lua_rawgeti(L, LUA_REGISTRYINDEX, windowref);
  lua_getfield(L, -1, "onmouseup");
 
  if (lua_isfunction(L, -1)) { 
    lua_pushstring(L, button); nargs++;
    lua_pushinteger(L, x ); nargs++;
    lua_pushinteger(L, y ); nargs++;
    
    lua_pushboolean(L, alt); nargs++;
    lua_pushboolean(L, ctrl); nargs++;
    lua_pushboolean(L, shift); nargs++;
    reactor_pcall(L, nargs, 0);
    lua_pop(L, 1);
  }
  else {
    lua_pop(L, 2);
  }
}

void pushL_mousewheel(int x, int y, int delta, int step, int alt, int ctrl, int shift) {
  int nargs = 0;
  lua_rawgeti(L, LUA_REGISTRYINDEX, windowref);
  lua_getfield(L, -1, "onmousewheel");

  if (lua_isfunction(L, -1)) { 
    lua_pushinteger(L, delta); nargs++;
    lua_pushinteger(L, step); nargs++;
    lua_pushinteger(L, x); nargs++;
    lua_pushinteger(L, y); nargs++;
    
    lua_pushboolean(L, alt); nargs++;
    lua_pushboolean(L, ctrl); nargs++;
    lua_pushboolean(L, shift); nargs++;

    reactor_pcall(L, nargs, 0);
    lua_pop(L, 1);
  }
  else {
    lua_pop(L, 2);
  }
}

void pushL_mousemove(int x, int y, int alt, int ctrl, int shift) {
  int nargs = 0;
  lua_rawgeti(L, LUA_REGISTRYINDEX, windowref);
  lua_getfield(L, -1, "onmousemove");

  if (lua_isfunction(L, -1)) { 
    lua_pushinteger(L, x ); nargs++;
    lua_pushinteger(L, y ); nargs++;

    reactor_pcall(L, nargs, 0);
    lua_pop(L, 1);
  }
  else {
    lua_pop(L, 2);
  }
}

void pushL_char(int c) {
  int nargs = 0;
  char buffer[8] = {0};
  lua_rawgeti(L, LUA_REGISTRYINDEX, windowref);
  lua_getfield(L, -1, "onchar");
  
  {
	  WideCharToMultiByte(CP_UTF8, 0, &(WCHAR)c, 1, buffer, sizeof(buffer), NULL, NULL);
  }

  if (lua_isfunction(L, -1)) { 
    //lua_pushfstring(L, "%c", c); nargs++;
	lua_pushstring(L, buffer); nargs++;

    reactor_pcall(L, nargs, 0);
    lua_pop(L, 1);
  }
  else {
    lua_pop(L, 2);
  }
}

void pushL_mouseexit(void) {
}

void pushL_mouseenter(void) {
}

void pushL_keydown(const char* key, int alt, int ctrl, int shift) {
  int nargs = 0;
  lua_rawgeti(L, LUA_REGISTRYINDEX, windowref);
  lua_getfield(L, -1, "onkeydown");

  if (lua_isfunction(L, -1)) { 
    lua_pushstring(L, key); nargs++;        
    lua_pushboolean(L, 0); nargs++;
    lua_pushboolean(L, alt); nargs++;
    lua_pushboolean(L, ctrl); nargs++;
    lua_pushboolean(L, shift); nargs++;
    reactor_pcall(L, nargs, 0);
    lua_pop(L, 1);
  }
  else {
    lua_pop(L, 2);
  }     
}

void pushL_keypress(const char* key, int alt, int ctrl, int shift) {
  int nargs = 0;
  lua_rawgeti(L, LUA_REGISTRYINDEX, windowref);
  lua_getfield(L, -1, "onkeydown");

  if (lua_isfunction(L, -1)) { 
    lua_pushstring(L, key); nargs++;        
    lua_pushboolean(L, 1); nargs++;
    lua_pushboolean(L, alt); nargs++;
    lua_pushboolean(L, ctrl); nargs++;
    lua_pushboolean(L, shift); nargs++;
    reactor_pcall(L, nargs, 0);
    lua_pop(L, 1);
  }
  else {
    lua_pop(L, 2);
  }     
}

void pushL_keyup(const char* key, int alt, int ctrl, int shift) {
  int nargs = 0;
  lua_rawgeti(L, LUA_REGISTRYINDEX, windowref);
  lua_getfield(L, -1, "onkeyup");

  if (lua_isfunction(L, -1)) { 
    lua_pushstring(L, key); nargs++;        
    lua_pushboolean(L, alt); nargs++;
    lua_pushboolean(L, ctrl); nargs++;
    lua_pushboolean(L, shift); nargs++;
    reactor_pcall(L, nargs, 0);
    lua_pop(L, 1);
  }
  else {
    lua_pop(L, 2);
  }     
}

void pushL_draw(void) {
  assert(L);
  lua_rawgeti(L, LUA_REGISTRYINDEX, windowref);
  lua_getfield(L, -1, "draw");
     
  if (lua_isfunction(L, -1)) { 
    if (reactor_pcall(L, 0, 0)) {
      PostQuitMessage(0);  
    }
    lua_pop(L, 1);
  }
  else {
    lua_pop(L, 2);
  }
}

int pushL_update(int currentmillis) {
  int ret = 0;
  lua_rawgeti(L, LUA_REGISTRYINDEX, appref);
  lua_getfield(L, -1, "update");

  if (lua_isfunction(L, -1)) { 	
    lua_pushnumber(L, currentmillis);
    reactor_pcall(L, 1, 1);
    ret = lua_tointeger(L, -1);
    lua_pop(L, 2);
  }
  else {
    lua_pop(L, 2);
  }
  
  return currentmillis-reactor_getelapsedtime() + ret;
}

void pushL_tick(void) {
  int ret = 0;
  lua_rawgeti(L, LUA_REGISTRYINDEX, appref);
  lua_getfield(L, -1, "ontick");  

  if (lua_isfunction(L, -1)) { 	    
    lua_pushnumber(L, reactor_getelapsedtime()); 
    reactor_pcall(L, 1, 0);
    lua_pop(L, 1);
  }
  else {
    lua_pop(L, 2);
  }  
}

static int open_window_L(lua_State* L) {
  { //window
    static const luaL_reg app_window_functions_L[] = {    
      {"getclientrect", window_getclientrect_L},
      {"redraw", window_redraw_L},
	  {"getclipboardtext", reactor_window_getclipboard_L},
	  {"setclipboardtext", reactor_window_setclipboard_L},
      {0, 0}
    };

    lua_rawgeti(L, LUA_REGISTRYINDEX, windowref);
    luaL_register(L, 0, app_window_functions_L);

    //set window.graphics
    lua_pushliteral(L, "graphics");
    luaopen_reactor_graphics(L);
    lua_settable(L, -3);
  }
  return 0;
}

//1 - app name
//2 - app full path
//3 - app args table 
//4 - reactor path
static int open_reactor_L(lua_State* L) {

  //package.preload.cairo = luaopen_cairo
  lua_getglobal(L, "package");
  lua_getfield(L, -1, "preload");
  lua_pushcfunction(L, luaopen_cairo);
  lua_setfield(L, -2, "cairo");

  lua_settop(L, 4);

  //reactor
  lua_newtable(L);
  lua_setglobal(L, "reactor");

  //set reactor.path
  lua_getglobal(L, "reactor");
  lua_pushvalue(L, 4);
  lua_setfield(L, -2, "path");
  
  { //app
    static const luaL_reg app_functions_L[] = {
      {"quit", reactor_quit_L},  //required
      {"getelapsedtime", reactor_getelapsedtime_L}, //required
      {0, 0}
    };

    //app
    luaL_register(L, "app", app_functions_L);
    lua_pushvalue(L, -1);
    appref = luaL_ref(L, LUA_REGISTRYINDEX);

    //app.name 
    lua_pushvalue(L, 1);
    lua_setfield(L, -2, "name");

    //app.path
    lua_pushvalue(L, 2);
    lua_setfield(L, -2, "path");

    //app.args
    lua_pushvalue(L, 3);
    lua_setfield(L, -2, "args");
  }

  lua_settop(L, 0);

  lua_pushcfunction(L, open_window_L);
  lua_call(L, 0, 0);

  lua_getglobal(L, "require");
  lua_pushliteral(L, "reactor");
  lua_call(L, 1, 1);

  lua_call(L, 0, 0); //call function returned from require 'reactor'

  return(0);
}

static const char* _translate_keyboard_key( WPARAM wparam ) {
  switch ( wparam )  {
    case VK_BACK:       return "backspace";
    case VK_TAB:        return "tab";
    case VK_RETURN:     return "enter";
    case VK_SHIFT:      return "shift";
    case VK_CONTROL:    return "ctrl";
    case VK_MENU:       return "alt";
    case VK_PAUSE:      return "pause";
    case VK_CAPITAL:    return "capslock";
    case VK_ESCAPE:     return "escape";
    case VK_SPACE:      return "space";
    case VK_PRIOR:      return "pageup";
    case VK_NEXT:       return "pagedown";
    case VK_END:        return "end";
    case VK_HOME:       return "home";
    case VK_LEFT:       return "left";
    case VK_UP:         return "up";
    case VK_RIGHT:      return "right";
    case VK_DOWN:       return "down";
    case VK_SNAPSHOT:   return "printscreen";
    case VK_INSERT:     return "insert";
    case VK_DELETE:     return "delete";
    case 0x30:          return "0";
    case 0x31:          return "1";
    case 0x32:          return "2";
    case 0x33:          return "3";
    case 0x34:          return "4";
    case 0x35:          return "5";
    case 0x36:          return "6";
    case 0x37:          return "7";
    case 0x38:          return "8";
    case 0x39:          return "9";
    case 0x41:          return "a";
    case 0x42:          return "b";
    case 0x43:          return "c";
    case 0x44:          return "d";
    case 0x45:          return "e";
    case 0x46:          return "f";
    case 0x47:          return "g";
    case 0x48:          return "h";
    case 0x49:          return "i";
    case 0x4A:          return "j";
    case 0x4B:          return "k";
    case 0x4C:          return "l";
    case 0x4D:          return "m";
    case 0x4E:          return "n";
    case 0x4F:          return "o";
    case 0x50:          return "p";
    case 0x51:          return "q";
    case 0x52:          return "r";
    case 0x53:          return "s";
    case 0x54:          return "t";
    case 0x55:          return "u";
    case 0x56:          return "v";
    case 0x57:          return "w";
    case 0x58:          return "x";
    case 0x59:          return "y";
    case 0x5A:          return "z";
    case VK_NUMPAD0:    return "numpad0";
    case VK_NUMPAD1:    return "numpad1";
    case VK_NUMPAD2:    return "numpad2";
    case VK_NUMPAD3:    return "numpad3";
    case VK_NUMPAD4:    return "numpad4";
    case VK_NUMPAD5:    return "numpad5";
    case VK_NUMPAD6:    return "numpad6";
    case VK_NUMPAD7:    return "numpad7";
    case VK_NUMPAD8:    return "numpad8";
    case VK_NUMPAD9:    return "numpad9";
    case VK_MULTIPLY:   return "multiply";
    case VK_ADD:        return "add";
    case VK_SUBTRACT:   return "subtract";
    case VK_DECIMAL:    return "decimal";
    case VK_DIVIDE:     return "divide";
    case VK_F1:         return "f1";
    case VK_F2:         return "f2";
    case VK_F3:         return "f3";
    case VK_F4:         return "f4";
    case VK_F5:         return "f5";
    case VK_F6:         return "f6";
    case VK_F7:         return "f7";
    case VK_F8:         return "f8";
    case VK_F9:         return "f9";
    case VK_F10:        return "f10";
    case VK_F11:        return "f11";
    case VK_F12:        return "f12";
    case VK_NUMLOCK:    return "numlock";
    case VK_SCROLL:     return "scrolllock";
    case VK_OEM_PLUS:   return "equal";
    case VK_OEM_COMMA:  return "comma";
    case VK_OEM_MINUS:  return "minus";
    case VK_OEM_PERIOD: return "period";
    case VK_OEM_1:      return "semicolon";
    case VK_OEM_2:      return "slash";
    case VK_OEM_3:      return "graveaccent";
    case VK_OEM_4:      return "openbracket";
    case VK_OEM_5:      return "backslash";
    case VK_OEM_6:      return "closebracket";
    case VK_OEM_7:      return "apostrophe";
  }
  return 0;
}

static LRESULT CALLBACK _window_proc( HWND hwnd, UINT msg, WPARAM wparam, LPARAM lparam ) {    
  TRACKMOUSEEVENT tme = {0};

  switch ( msg ) {
    case APP_WINDOW_CREATE: {
      RECT rect;
      GetClientRect(hwnd, &rect);
      window.w = rect.right-rect.left;
      window.h = rect.bottom-rect.top;
      window.created = 1;
      pushL_windowevent("create");      
      return 0;
                            }

    case WM_ACTIVATEAPP:
      if ( wparam ) {
        window.activated = 1;
        SetForegroundWindow(hwnd);
        LockSetForegroundWindow( LSFW_LOCK );
        InvalidateRect(hwnd, 0, 0);
        if (window.created) pushL_windowevent("activate");
      }
      else {
        window.activated = 0;
        if (window.created) pushL_windowevent("deactivate");
      }          
      return 0;

    case APP_TICK:  
	  window.timerposted = 0;
      pushL_tick();      
      return 0;

    case WM_DESTROY:      
      PostQuitMessage(0);
      return 0;

    case WM_SHOWWINDOW:
      if (wparam) {
        if (window.created) pushL_windowevent("show");
      } 
      else {
        if (window.created) pushL_windowevent("hide");
      }
      return 0;

    case WM_MOVE:
      if ( !IsIconic( hwnd ) ) {
        window.x = (int)(short)LOWORD( lparam );
        window.y = (int)(short)HIWORD( lparam );
        if (window.created) pushL_windowevent("move");        
      }
      return 0;    

    case WM_SIZE:
      if ( SIZE_MAXIMIZED == wparam || SIZE_RESTORED == wparam ) {
        window.w = LOWORD( lparam );
        window.h = HIWORD( lparam );
        if (window.created) {
          pushL_windowevent("resize");              
          pushL_draw();        
          SwapBuffers(window.hdc);  
        }
      }
      return 0;

    case WM_ERASEBKGND:
      return 1;

    case WM_PAINT:
      if ( GetUpdateRect(hwnd, 0, FALSE) ) {
        ValidateRect(hwnd, 0 );
        pushL_draw();        
        SwapBuffers(window.hdc);  
      }
      return 0;

    case WM_APPCOMMAND:
      switch ( GET_APPCOMMAND_LPARAM( lparam ) ) {
        case APPCOMMAND_COPY: 
          pushL_command("copy");
          break;
        case APPCOMMAND_CUT:   
          pushL_command("cut");
          break;
        case APPCOMMAND_PASTE: 
          pushL_command("paste");
          break;
        default:
          return DefWindowProc(hwnd, msg, wparam, lparam);
      }
      return 1;
    
    case WM_MBUTTONDBLCLK:
      pushL_mousedblclick(GET_X_LPARAM( lparam ), GET_Y_LPARAM( lparam ), "middle", 
        GetKeyState( VK_MENU ) & 0x8000, 
        GetKeyState( VK_CONTROL ) & 0x8000, 
        GetKeyState( VK_SHIFT ) & 0x8000);
      return 0;

    case WM_LBUTTONDBLCLK:
      pushL_mousedblclick(GET_X_LPARAM( lparam ), GET_Y_LPARAM( lparam ), "left", 
        GetKeyState( VK_MENU ) & 0x8000, 
        GetKeyState( VK_CONTROL ) & 0x8000, 
        GetKeyState( VK_SHIFT ) & 0x8000);
      return 0;

    case WM_RBUTTONDBLCLK:
      pushL_mousedblclick(GET_X_LPARAM( lparam ), GET_Y_LPARAM( lparam ), "right", 
        GetKeyState( VK_MENU ) & 0x8000, 
        GetKeyState( VK_CONTROL ) & 0x8000, 
        GetKeyState( VK_SHIFT ) & 0x8000);
      return 0;

    case WM_MBUTTONDOWN:
      SetCapture( hwnd );
      pushL_mousedown(GET_X_LPARAM( lparam ), GET_Y_LPARAM( lparam ), "middle", 
        GetKeyState( VK_MENU ) & 0x8000, 
        GetKeyState( VK_CONTROL ) & 0x8000, 
        GetKeyState( VK_SHIFT ) & 0x8000);
      return 0;

    case WM_LBUTTONDOWN:
      SetCapture( hwnd );
      pushL_mousedown(GET_X_LPARAM( lparam ), GET_Y_LPARAM( lparam ), "left", 
        GetKeyState( VK_MENU ) & 0x8000, 
        GetKeyState( VK_CONTROL ) & 0x8000, 
        GetKeyState( VK_SHIFT ) & 0x8000);
      return 0;

    case WM_RBUTTONDOWN:
      SetCapture( hwnd );
      pushL_mousedown(GET_X_LPARAM( lparam ), GET_Y_LPARAM( lparam ), "right", 
        GetKeyState( VK_MENU ) & 0x8000, 
        GetKeyState( VK_CONTROL ) & 0x8000, 
        GetKeyState( VK_SHIFT ) & 0x8000);
      return 0;

    case WM_MBUTTONUP:
      ReleaseCapture();
      pushL_mouseup(GET_X_LPARAM( lparam ), GET_Y_LPARAM( lparam ), "middle", 
        GetKeyState( VK_MENU ) & 0x8000, 
        GetKeyState( VK_CONTROL ) & 0x8000, 
        GetKeyState( VK_SHIFT ) & 0x8000);
      return 0;  

    case WM_LBUTTONUP:
      ReleaseCapture();
      pushL_mouseup(GET_X_LPARAM( lparam ), GET_Y_LPARAM( lparam ), "left", 
        GetKeyState( VK_MENU ) & 0x8000, 
        GetKeyState( VK_CONTROL ) & 0x8000, 
        GetKeyState( VK_SHIFT ) & 0x8000);
      return 0;  

    case WM_RBUTTONUP:    
      ReleaseCapture();
      pushL_mouseup(GET_X_LPARAM( lparam ), GET_Y_LPARAM( lparam ), "right", 
        GetKeyState( VK_MENU ) & 0x8000, 
        GetKeyState( VK_CONTROL ) & 0x8000, 
        GetKeyState( VK_SHIFT ) & 0x8000);
      return 0;    

    case WM_CHAR:
	
      if ( ( 32 <= ( wparam & 0xFF ) )) {
		pushL_char(wparam);  
      }	  
      return 0;    

    case WM_MOUSELEAVE:
      window.tracking = 0;
      pushL_mouseexit();
      return 0;

    case WM_MOUSEMOVE:
      SetCursor( window.hcursor );
      if ( !window.tracking ) {
        window.tracking = 1;

        tme.cbSize = sizeof( TRACKMOUSEEVENT );
        tme.dwFlags = TME_LEAVE;
        tme.hwndTrack = hwnd;
        tme.dwHoverTime = HOVER_DEFAULT;

        TrackMouseEvent( &tme );

        pushL_mouseenter();
      }

      pushL_mousemove(GET_X_LPARAM(lparam ), GET_Y_LPARAM(lparam ), 
        GetKeyState( VK_MENU ) & 0x8000,
        GetKeyState( VK_CONTROL ) & 0x8000,
        GetKeyState( VK_SHIFT ) & 0x8000);      
      return 0;

    case WM_MOUSEWHEEL:
      {
        POINT pt;
        UINT step;
        SystemParametersInfo( SPI_GETWHEELSCROLLLINES, 0, &step, 0 );

        pt.x = GET_X_LPARAM( lparam );
        pt.y = GET_Y_LPARAM( lparam );
        ScreenToClient(hwnd, &pt);
        pushL_mousewheel(pt.x, pt.y, 
          GET_WHEEL_DELTA_WPARAM( wparam ) / WHEEL_DELTA,
          step,
          GetKeyState( VK_MENU ) & 0x8000,
          GetKeyState( VK_CONTROL ) & 0x8000,
          GetKeyState( VK_SHIFT ) & 0x8000);        
      }  
      return 0;

    case WM_KEYDOWN:
    case WM_SYSKEYDOWN:
      if ( KF_REPEAT & HIWORD( lparam ) ) {
        pushL_keypress(_translate_keyboard_key( wparam ),
          GetKeyState( VK_MENU ) & 0x8000, 
          GetKeyState( VK_CONTROL ) & 0x8000, 
          GetKeyState( VK_SHIFT ) & 0x8000);
      }
      else {
        pushL_keydown(_translate_keyboard_key( wparam ),
          GetKeyState( VK_MENU ) & 0x8000, 
          GetKeyState( VK_CONTROL ) & 0x8000, 
          GetKeyState( VK_SHIFT ) & 0x8000);
      }
      if ( GetKeyState( VK_CONTROL ) & 0x8000 ) {
        switch ( wparam ) {
          case 0x43:
            pushL_command("copy");
            break;
          case 0x58:
            pushL_command("cut");            
            break;
          case 0x56:
            pushL_command("paste");            
            break;         
        }        
      }
      return 0;

    case WM_KEYUP:
    case WM_SYSKEYUP:  
      pushL_keyup(_translate_keyboard_key( wparam ),
          GetKeyState( VK_MENU ) & 0x8000, 
          GetKeyState( VK_CONTROL ) & 0x8000, 
          GetKeyState( VK_SHIFT ) & 0x8000);
      return 0;
  }

  return DefWindowProc(hwnd, msg, wparam, lparam);
}

static void CALLBACK timecallback(UINT uTimerID, UINT uMsg, DWORD_PTR dwUser, DWORD_PTR dw1, DWORD_PTR dw2) {
	if (window.timerposted) {
		return;
	}
	window.timerposted = 1;
  PostMessage(window.hwnd, APP_TICK, 0, 0);
}

static int _poll_nowait(void) {
  MSG msg = {0};
  while ( PeekMessage( &msg, 0, WM_KEYFIRST, WM_MOUSELAST, PM_REMOVE ) ) {  
    if ( WM_QUIT == msg.message ) {
      return 0;
    }
    TranslateMessage( &msg );
    DispatchMessage( &msg );
  } 
  if ( PeekMessage( &msg, 0, 0, 0, PM_REMOVE ) ) {  
    if ( WM_QUIT == msg.message ) {
      return 0;
    }
    TranslateMessage( &msg );
    DispatchMessage( &msg );
  } 
  return 1;
}

static void _create_glwindow( const char* title, int cw, int ch ) {
  WNDCLASS wndclass = {0};
  DWORD wndstyle = 0;
  RECT rect = {0};
  HWND hwnd = 0;
  HDC hdc = 0;  
  HGLRC hglrc = 0;

  if ( !GetClassInfo( GetModuleHandle( 0 ), APP_WINDOW_CLASSNAME, &wndclass ) ) {
    wndclass.style = CS_OWNDC | CS_DBLCLKS;
    wndclass.lpfnWndProc = _window_proc;
    wndclass.hInstance = GetModuleHandle( 0 );
    wndclass.hIcon = LoadIcon( 0, IDI_APPLICATION );
    wndclass.hbrBackground = (HBRUSH)NULL;
    wndclass.lpszClassName = APP_WINDOW_CLASSNAME;

    if ( !RegisterClass( &wndclass ) ) {
      assert(!"RegisterClass() failed");
    }
  }

  SetRect( &rect, 0, 0, cw, ch );
  AdjustWindowRect( &rect, WS_OVERLAPPEDWINDOW, 0 );

  if ( !( hwnd = CreateWindow( APP_WINDOW_CLASSNAME, title, WS_OVERLAPPEDWINDOW | WS_CLIPCHILDREN | WS_CLIPSIBLINGS,
                               CW_USEDEFAULT, CW_USEDEFAULT, rect.right - rect.left, rect.bottom - rect.top,
                               0, 0, wndclass.hInstance, 0 ) ) ) {
    assert( !"CreateWindow() failed" );
  }

  if ( !( hdc = GetDC( hwnd ) ) ) {
    assert( !"GetDC() failed" );
  }  

  window.hwnd = hwnd;
  window.hdc = hdc;
  window.fullscreen = 0;
  window.x = rect.left;
  window.y = rect.top;
  window.w = cw;
  window.h = ch;
  window.hcursor = LoadCursor( 0, IDC_ARROW );

  //app_window_setcursor( window, APP_MOUSECURSOR_ARROW );
  {
    int pixelformat = 0;
    PIXELFORMATDESCRIPTOR pfd = {0};

    pfd.nSize = sizeof( PIXELFORMATDESCRIPTOR );
    pfd.nVersion = 1;
    pfd.dwFlags = PFD_DRAW_TO_WINDOW | PFD_SUPPORT_OPENGL | PFD_DOUBLEBUFFER;
    pfd.iPixelType = PFD_TYPE_RGBA;
    pfd.cRedBits = 8;
    pfd.cGreenBits = 8;
    pfd.cBlueBits = 8;
    pfd.cAlphaBits = 8;
    pfd.cDepthBits = 0;
    pfd.iLayerType = PFD_MAIN_PLANE;

    if ( !( pixelformat = ChoosePixelFormat( window.hdc, &pfd ) ) ) {
      assert( !"ChoosePixelFormat() failed" );
    }

    if ( !SetPixelFormat( window.hdc, pixelformat, &pfd ) ) {
      assert( !"SetPixelFormat() failed" );
    } 
  }

  if ( !( hglrc = wglCreateContext( window.hdc ) ) ) {
    assert( !"wglCreateContext() failed" );
  }

  wglMakeCurrent(window.hdc, hglrc );
  window.hglrc = hglrc;
  
  EGL_loadextensions();  
  
  ShowWindow( window.hwnd, SW_RESTORE );  
  SendMessage( window.hwnd, APP_WINDOW_CREATE, 0, 0 );    
}

static void _destroy_glwindow() {
  wglDeleteContext(window.hglrc);
  DestroyWindow(window.hwnd);
}

int main( int argc, char* argv[] ) {
  int i = 0;
  char* appname=0;
  static char reactorname[MAX_PATH] = {0};
  static char reactordir[MAX_PATH] = {0};
  static char app_path[MAX_PATH] = {0};

  GetModuleFileName(0, reactorname, sizeof(reactorname));
  strncpy(reactordir, reactorname, strrchr(reactorname, '\\') - reactorname);

  timeBeginPeriod( 1 );

  createtime = timeGetTime();

  L = lua_open();
  luaL_openlibs(L);
  
  lua_pushcfunction(L, reactor_traceback);
  lua_setglobal(L, "reactor_traceback");
  
  if (argv[2]) {
    char* title = argv[1];
    int w, h;    
    luaL_dostring(L, argv[2]);
    lua_getglobal(L, "window");

    lua_getfield(L, -1, "w");
    w = lua_tointeger(L, -1);
    lua_pop(L, 1);

    lua_getfield(L, -1, "h");
    h = lua_tointeger(L, -1);
    lua_pop(L, 1);

    windowref = luaL_ref(L, LUA_REGISTRYINDEX);

    _create_glwindow(title, w, h);
  }
  else {
    _create_glwindow(argv[1], 800, 600);  
  }

  GetFullPathName(argv[1], sizeof(app_path), app_path, NULL);

  lua_pushcfunction(L, open_reactor_L);
  lua_pushstring(L, argv[1]); //1 app name
  lua_pushstring(L, app_path); //2 app full path 
  lua_newtable(L);//3 app args

  for (i=2; i<argc; i++) {
    lua_pushstring(L, argv[i]);
    lua_rawseti(L, -2, i-1);
  }

  lua_pushstring(L, reactordir); //4 reactor dir

  if (!reactor_pcall(L, 4, 0)) {
    int millis = 0;

    timeSetEvent(15, 0, timecallback, 0, TIME_PERIODIC);

    while ( _poll_nowait() ) {
      int currentmillis = reactor_getelapsedtime();

      if (millis <= 0) {          
        millis = pushL_update(currentmillis);   
      }

      if (window.redraw) {            
        window.redraw = 0;
        RedrawWindow(window.hwnd, NULL, NULL, RDW_INVALIDATE|RDW_INTERNALPAINT); 
      }
      
      if (!_poll_nowait()) {
        break; //quit app
      }

      if (millis > 0 ) {
        int endmillis = currentmillis + millis;
        DWORD waitret;            
        waitret = MsgWaitForMultipleObjectsEx(0, 0, millis, QS_ALLEVENTS, MWMO_ALERTABLE|MWMO_INPUTAVAILABLE);
        if (WAIT_TIMEOUT == waitret) {              
          millis=0;      
        }
        else {              
          currentmillis = reactor_getelapsedtime();
          millis=endmillis-currentmillis;              
        }            
      }
    }
  }   
  
  _destroy_glwindow();
  lua_close(L);
  timeEndPeriod( 1 );

  return 0;
}
