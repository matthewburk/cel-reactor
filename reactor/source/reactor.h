#ifndef reactor_H
#define reactor_H

#ifdef __cplusplus
extern "C" {
#endif

extern void reactor_driver_get_windowrect(int* x, int* y, int* w, int* h);
extern int reactor_driver_quit(void);
extern int reactor_driver_fullscreen(int fullscreen);
extern unsigned long reactor_driver_millis(void);
extern void reactor_driver_systemtime(int* hour, int* min, int* sec, int* milli);
extern void reactor_driver_localtime(int* hour, int* min, int* sec, int* milli);

void reactor_winevent(const char* name);
void reactor_command(const char* command);
void reactor_mousedblclick(int x, int y, const char* button, int alt, int ctrl, int shift);
void reactor_mousedown(int x, int y, const char* button, int alt, int ctrl, int shift);
void reactor_mouseup(int x, int y, const char* button, int alt, int ctrl, int shift);
void reactor_mousewheel(int x, int y, int delta, int step, int alt, int ctrl, int shift);
void reactor_mousemove(int x, int y, int alt, int ctrl, int shift);
void reactor_char(int c);
void reactor_mouseexit(void);
void reactor_mouseenter(void);
void reactor_keydown(const char* key, int alt, int ctrl, int shift);
void reactor_keypress(const char* key, int alt, int ctrl, int shift);
void reactor_keyup(const char* key, int alt, int ctrl, int shift);
void reactor_init(int argc, char* argv[]);
void reactor_exit(void);
void reactor_paint(void);
void reactor_update(void);

extern struct reactor {
  int x;
  int y;
  int w;
  int h;
} reactor;

#ifdef __cplusplus
}
#endif

#endif
