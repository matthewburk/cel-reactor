#ifndef reactor_H
#define reactor_H

#include <windows.h>

#ifdef __cplusplus
extern "C" {
#endif

extern struct window {
  HWND hwnd;
  HDC hdc;
  HGLRC hglrc;
  HCURSOR hcursor;
  int created;
  int fullscreen;
  int activated;
  int tracking;
  int redraw;
  int x;
  int y;
  int w;
  int h;
  UINT_PTR timerid;
} window;

#ifdef __cplusplus
}
#endif

#endif
