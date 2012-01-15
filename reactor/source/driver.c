#include <windows.h>
#include <windowsx.h>
#include <stdio.h>
#include <debug.h>
#include "reactor.h"
#include "gl.h"

#define APP_WINDOW_CLASSNAME "app_window_t"
#define APP_WINDOW_CREATE ( WM_APP + 1 )
#define APP_WINDOW_QUIT ( WM_APP + 2 )

static struct window {
  HWND hwnd;
  HDC hdc;
  HGLRC hglrc;
  HCURSOR hcursor;
  int created;
  int fullscreen;
  int activated;
  int tracking;
  int x;
  int y;
  int w;
  int h;
  DWORD createtime;
} window;

int reactor_driver_quit(void) {
  PostQuitMessage(0);  
  return 1;
}

int reactor_driver_displaysetttings(void){
  DEVMODE devmode = {0};
  devmode.dmSize = sizeof( DEVMODE );
  EnumDisplaySettings( 0, ENUM_CURRENT_SETTINGS, &devmode );
  //todo return x, y, w, h
  return 1;
}

unsigned long reactor_driver_millis(void) {
  return timeGetTime() - window.createtime;
}

void reactor_driver_systemtime(int* hour, int* min, int* sec, int* milli) {
  SYSTEMTIME time;
  GetSystemTime(&time);
  *hour = time.wHour;
  *min = time.wMinute;
  *sec = time.wSecond;
  *milli = time.wMilliseconds;  
}

void reactor_driver_localtime(int* hour, int* min, int* sec, int* milli) {
  SYSTEMTIME time;
  GetSystemTime(&time);
  *hour = time.wHour;
  *min = time.wMinute;
  *sec = time.wSecond;
  *milli = time.wMilliseconds;  
}

void reactor_driver_get_windowrect(int* x, int* y, int* w, int* h) {
  *x = window.x;
  *y = window.y;
  *w = window.w;
  *h = window.h;
}


int reactor_driver_fullscreen(int fullscreen) {
  int visible = 0;
  RECT rect = {0}; 
  DEVMODE devmode = {0};
  int x, y, w, h; 

  devmode.dmSize = sizeof( DEVMODE );
  EnumDisplaySettings( 0, ENUM_CURRENT_SETTINGS, &devmode );

  x = devmode.dmPosition.x;
  y = devmode.dmPosition.y;
  w = devmode.dmPelsWidth;
  h = devmode.dmPelsHeight;

  if (fullscreen && !window.fullscreen) {
    window.fullscreen = 1;
    visible = IsWindowVisible( window.hwnd );   
    if ( visible ) {
      ShowWindow( window.hwnd, SW_HIDE );      
    }    
    SetRect( &rect, x, y, x+w, y+h);
    AdjustWindowRect( &rect, WS_POPUP, 0 );
    SetWindowLongPtr( window.hwnd, GWL_STYLE, WS_POPUP | WS_CLIPCHILDREN | WS_CLIPSIBLINGS );
    SetWindowPos( window.hwnd, HWND_TOP,
                  rect.left, rect.top, rect.right - rect.left, rect.bottom - rect.top,
                  SWP_NOACTIVATE | SWP_NOZORDER | SWP_NOCOPYBITS | SWP_FRAMECHANGED );
    if ( visible ) {
      ShowWindow( window.hwnd, SW_RESTORE );        
    }
  }
  else if (!fullscreen && window.fullscreen) {
    window.fullscreen = 0;
    visible = IsWindowVisible( window.hwnd );   
    if ( visible ) {
      ShowWindow( window.hwnd, SW_HIDE );      
    }
    SetRect( &rect, x, y, x+w, y+h);
    AdjustWindowRect( &rect, WS_OVERLAPPEDWINDOW, 0 );
    SetWindowLongPtr( window.hwnd, GWL_STYLE, WS_OVERLAPPEDWINDOW | WS_CLIPCHILDREN | WS_CLIPSIBLINGS );
    SetWindowPos( window.hwnd, HWND_TOP,
                  rect.left, rect.top, rect.right - rect.left, rect.bottom - rect.top,
                  SWP_NOACTIVATE | SWP_NOZORDER | SWP_NOCOPYBITS | SWP_FRAMECHANGED );
    if ( visible ) {
      ShowWindow( window.hwnd, SW_RESTORE );        
    }
  }
  return 1;
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
    case APP_WINDOW_CREATE:
      window.created = 1;
      reactor_winevent("create");      
      return 0;

    case WM_ACTIVATEAPP:
      if ( wparam ) {
        window.activated = 1;
        SetForegroundWindow(hwnd);
        LockSetForegroundWindow( LSFW_LOCK );
        InvalidateRect(hwnd, 0, 0);
        if (window.created) reactor_winevent("activate");
      }
      else {
        window.activated = 0;
        if (window.created) reactor_winevent("deactivate");
      }          
      return 0;

    case WM_DESTROY:      
      PostQuitMessage(0);
      return 0;

    case WM_SHOWWINDOW:
      if (wparam) {
        if (window.created) reactor_winevent("show");
      } 
      else {
        if (window.created) reactor_winevent("hide");
      }
      return 0;

    case WM_MOVE:
      if ( !IsIconic( hwnd ) ) {
        window.x = (int)(short)LOWORD( lparam );
        window.y = (int)(short)HIWORD( lparam );
        if (window.created) reactor_winevent("move");        
      }
      return 0;    

    case WM_SIZE:
      if ( SIZE_MAXIMIZED == wparam || SIZE_RESTORED == wparam ) {
        window.w = LOWORD( lparam );
        window.h = HIWORD( lparam );
        if (window.created) {
          reactor_winevent("resize");    
          reactor_update();
          reactor_paint();        
          SwapBuffers(window.hdc);  
        }
      }
      return 0;

    case WM_ERASEBKGND:
      return 1;

    case WM_PAINT:
      if ( GetUpdateRect(hwnd, 0, FALSE) ) {
        ValidateRect(hwnd, 0 );
        reactor_paint();        
        SwapBuffers(window.hdc);  
      }
      return 0;

    case WM_APPCOMMAND:
      switch ( GET_APPCOMMAND_LPARAM( lparam ) ) {
        case APPCOMMAND_COPY: 
          reactor_command("copy");
          break;
        case APPCOMMAND_CUT:   
          reactor_command("cut");
          break;
        case APPCOMMAND_PASTE: 
          reactor_command("paste");
          break;
        default:
          return DefWindowProc(hwnd, msg, wparam, lparam);
      }
      return 1;
    
    case WM_MBUTTONDBLCLK:
      reactor_mousedblclick(GET_X_LPARAM( lparam ), GET_Y_LPARAM( lparam ), "middle", 
        GetKeyState( VK_MENU ) & 0x8000, 
        GetKeyState( VK_CONTROL ) & 0x8000, 
        GetKeyState( VK_SHIFT ) & 0x8000);
      return 0;

    case WM_LBUTTONDBLCLK:
      reactor_mousedblclick(GET_X_LPARAM( lparam ), GET_Y_LPARAM( lparam ), "left", 
        GetKeyState( VK_MENU ) & 0x8000, 
        GetKeyState( VK_CONTROL ) & 0x8000, 
        GetKeyState( VK_SHIFT ) & 0x8000);
      return 0;

    case WM_RBUTTONDBLCLK:
      reactor_mousedblclick(GET_X_LPARAM( lparam ), GET_Y_LPARAM( lparam ), "right", 
        GetKeyState( VK_MENU ) & 0x8000, 
        GetKeyState( VK_CONTROL ) & 0x8000, 
        GetKeyState( VK_SHIFT ) & 0x8000);
      return 0;

    case WM_MBUTTONDOWN:
      SetCapture( hwnd );
      reactor_mousedown(GET_X_LPARAM( lparam ), GET_Y_LPARAM( lparam ), "middle", 
        GetKeyState( VK_MENU ) & 0x8000, 
        GetKeyState( VK_CONTROL ) & 0x8000, 
        GetKeyState( VK_SHIFT ) & 0x8000);
      return 0;

    case WM_LBUTTONDOWN:
      SetCapture( hwnd );
      reactor_mousedown(GET_X_LPARAM( lparam ), GET_Y_LPARAM( lparam ), "left", 
        GetKeyState( VK_MENU ) & 0x8000, 
        GetKeyState( VK_CONTROL ) & 0x8000, 
        GetKeyState( VK_SHIFT ) & 0x8000);
      return 0;

    case WM_RBUTTONDOWN:
      SetCapture( hwnd );
      reactor_mousedown(GET_X_LPARAM( lparam ), GET_Y_LPARAM( lparam ), "right", 
        GetKeyState( VK_MENU ) & 0x8000, 
        GetKeyState( VK_CONTROL ) & 0x8000, 
        GetKeyState( VK_SHIFT ) & 0x8000);
      return 0;

    case WM_MBUTTONUP:
      ReleaseCapture();
      reactor_mouseup(GET_X_LPARAM( lparam ), GET_Y_LPARAM( lparam ), "middle", 
        GetKeyState( VK_MENU ) & 0x8000, 
        GetKeyState( VK_CONTROL ) & 0x8000, 
        GetKeyState( VK_SHIFT ) & 0x8000);
      return 0;  

    case WM_LBUTTONUP:
      ReleaseCapture();
      reactor_mouseup(GET_X_LPARAM( lparam ), GET_Y_LPARAM( lparam ), "left", 
        GetKeyState( VK_MENU ) & 0x8000, 
        GetKeyState( VK_CONTROL ) & 0x8000, 
        GetKeyState( VK_SHIFT ) & 0x8000);
      return 0;  

    case WM_RBUTTONUP:    
      ReleaseCapture();
      reactor_mouseup(GET_X_LPARAM( lparam ), GET_Y_LPARAM( lparam ), "right", 
        GetKeyState( VK_MENU ) & 0x8000, 
        GetKeyState( VK_CONTROL ) & 0x8000, 
        GetKeyState( VK_SHIFT ) & 0x8000);
      return 0;    

    case WM_CHAR:
      if ( ( 32 <= ( wparam & 0xFF ) ) && ( 126 >= ( wparam & 0xFF ) ) ) {
        reactor_char(wparam & 0xFF);
      }
      return 0;    

    case WM_MOUSELEAVE:
      window.tracking = 0;
      reactor_mouseexit();
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

        reactor_mouseenter();
      }

      reactor_mousemove(GET_X_LPARAM(lparam ), GET_Y_LPARAM(lparam ), 
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
        reactor_mousewheel(pt.x, pt.y, 
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
        reactor_keypress(_translate_keyboard_key( wparam ),
          GetKeyState( VK_MENU ) & 0x8000, 
          GetKeyState( VK_CONTROL ) & 0x8000, 
          GetKeyState( VK_SHIFT ) & 0x8000);
      }
      else {
        reactor_keydown(_translate_keyboard_key( wparam ),
          GetKeyState( VK_MENU ) & 0x8000, 
          GetKeyState( VK_CONTROL ) & 0x8000, 
          GetKeyState( VK_SHIFT ) & 0x8000);
        reactor_keypress(_translate_keyboard_key( wparam ),
          GetKeyState( VK_MENU ) & 0x8000, 
          GetKeyState( VK_CONTROL ) & 0x8000, 
          GetKeyState( VK_SHIFT ) & 0x8000);
      }
      if ( GetKeyState( VK_CONTROL ) & 0x8000 ) {
        switch ( wparam ) {
          case 0x43:
            reactor_command("copy");
            break;
          case 0x58:
            reactor_command("cut");            
            break;
          case 0x56:
            reactor_command("paste");            
            break;         
        }        
      }
      return 0;

    case WM_KEYUP:
    case WM_SYSKEYUP:  
      reactor_keyup(_translate_keyboard_key( wparam ),
          GetKeyState( VK_MENU ) & 0x8000, 
          GetKeyState( VK_CONTROL ) & 0x8000, 
          GetKeyState( VK_SHIFT ) & 0x8000);
      return 0;
  }

  return DefWindowProc(hwnd, msg, wparam, lparam);
}

static int _poll_nowait(void) {
  MSG msg = {0};
  while ( PeekMessage( &msg, 0, 0, 0, PM_REMOVE ) ) {
    if ( WM_QUIT == msg.message ) {
      return 0;
    }
    TranslateMessage( &msg );
    DispatchMessage( &msg );
  } 
  return 1;
}

static int _poll_wait(void) {
  MSG msg = {0};
  while ( 0 < GetMessage( &msg, 0, 0, 0 ) ) {
    TranslateMessage( &msg );
    DispatchMessage( &msg );
    return _poll_nowait();
  }
  return 0;
}

static void _destroy_window() {
  wglDeleteContext(window.hglrc);
  DestroyWindow(window.hwnd);
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
      DBG_ASSERT( !"RegisterClass() failed" );
    }
  }

  SetRect( &rect, 0, 0, cw, ch );
  AdjustWindowRect( &rect, WS_OVERLAPPEDWINDOW, 0 );

  if ( !( hwnd = CreateWindow( APP_WINDOW_CLASSNAME, title, WS_OVERLAPPEDWINDOW | WS_CLIPCHILDREN | WS_CLIPSIBLINGS,
                               CW_USEDEFAULT, CW_USEDEFAULT, rect.right - rect.left, rect.bottom - rect.top,
                               0, 0, wndclass.hInstance, 0 ) ) ) {
    DBG_ASSERT( !"CreateWindow() failed" );
  }

  if ( !( hdc = GetDC( hwnd ) ) ) {
    DBG_ASSERT( !"GetDC() failed" );
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
    pfd.dwFlags = PFD_DRAW_TO_WINDOW | PFD_SUPPORT_OPENGL;// | PFD_DOUBLEBUFFER;
    pfd.iPixelType = PFD_TYPE_RGBA;
    pfd.cRedBits = 8;
    pfd.cGreenBits = 8;
    pfd.cBlueBits = 8;
    pfd.cAlphaBits = 8;
    pfd.cDepthBits = 0;
    pfd.iLayerType = PFD_MAIN_PLANE;

    if ( !( pixelformat = ChoosePixelFormat( window.hdc, &pfd ) ) ) {
      DBG_ASSERT( !"ChoosePixelFormat() failed" );
    }

    if ( !SetPixelFormat( window.hdc, pixelformat, &pfd ) ) {
      DBG_ASSERT( !"SetPixelFormat() failed" );
    } 
  }

  if ( !( hglrc = wglCreateContext( window.hdc ) ) ) {
    DBG_ASSERT( !"wglCreateContext() failed" );
  }

  wglMakeCurrent(window.hdc, hglrc );
  window.hglrc = hglrc;
  
  EGL_loadextensions();  
  
  ShowWindow( window.hwnd, SW_RESTORE );  
  SendMessage( window.hwnd, APP_WINDOW_CREATE, 0, 0 );    
}

int main( int argc, char* argv[] ) {
  if (argc > 2) {
    DBG_PUSH(argv[2]);
  }

  DBG_ENTER();
  timeBeginPeriod(1);
  window.createtime = timeGetTime();  
  _create_glwindow("reactor", 800, 600);      
  reactor_init(argc, argv);
  while ( _poll_nowait() ) {
    reactor_update();
    RedrawWindow(window.hwnd, NULL, NULL, RDW_INVALIDATE);
  }   
  reactor_exit();  
  _destroy_window();
  timeEndPeriod(1);
  DBG_RETURN(0);
}
