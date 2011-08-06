
#ifndef APP_APPLICATION_H
#define APP_APPLICATION_H


/*============================================================================================================================================================*/
/*                                                                                                                                                            */
/*============================================================================================================================================================*/
/*       1         2         3         4         5         6         7         8         9         0         1         2         3         4         5        */
/*345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678*/
/*============================================================================================================================================================*/


#include <stddef.h>
#include <toolkits/sys/intrinsics.h>
#include <toolkits/sys/stdbool.h>
#include <toolkits/sys/stdint.h>


#ifdef __cplusplus
extern "C" {
#endif


#define APP_NAMESPACE "app"


#define APP_DISPLAYMODE_CURRENT ((size_t) - 1)


/* enumerated types */
typedef enum app_eventkind_t app_eventkind_t;
typedef enum app_glversion_t app_glversion_t;
typedef enum app_keyboardkey_t app_keyboardkey_t;
typedef enum app_mousebutton_t app_mousebutton_t;
typedef enum app_mousecursor_t app_mousecursor_t;
typedef enum app_windowstate_t app_windowstate_t;
typedef enum app_windowstyle_t app_windowstyle_t;

/* opaque types */
typedef struct app_context_t app_context_t;
typedef struct app_display_t app_display_t;
typedef struct app_window_t app_window_t;

/* transparent types */
typedef struct app_bounds_t app_bounds_t;
typedef struct app_dimension_t app_dimension_t;
typedef struct app_displaymode_t app_displaymode_t;
typedef struct app_eventlisteners_t app_eventlisteners_t;
typedef struct app_mousewheel_t app_mousewheel_t;
typedef struct app_pixelformat_t app_pixelformat_t;
typedef struct app_point_t app_point_t;

/* event types */
typedef struct app_clipboardevent_t app_clipboardevent_t;
typedef struct app_displayevent_t app_displayevent_t;
typedef struct app_keyboardevent_t app_keyboardevent_t;
typedef struct app_mouseevent_t app_mouseevent_t;
typedef struct app_windowevent_t app_windowevent_t;
typedef union app_event_t app_event_t;

/* function pointer types */
typedef void (*app_eventlistener_t)( const app_event_t* event, void* userdata );


enum app_eventkind_t
{
  APP_EVENTKIND_UNKNOWN,
  APP_EVENTKIND_CLIPBOARDCOPY,
  APP_EVENTKIND_CLIPBOARDCUT,
  APP_EVENTKIND_CLIPBOARDPASTE,
  APP_EVENTKIND_DISPLAYCHANGE,
  APP_EVENTKIND_KEYBOARDCHARACTER,
  APP_EVENTKIND_KEYBOARDPRESS,
  APP_EVENTKIND_KEYBOARDRELEASE,
  APP_EVENTKIND_MOUSEDOUBLECLICK,
  APP_EVENTKIND_MOUSEENTER,
  APP_EVENTKIND_MOUSEEXIT,
  APP_EVENTKIND_MOUSEMOVE,
  APP_EVENTKIND_MOUSEPRESS,
  APP_EVENTKIND_MOUSERELEASE,
  APP_EVENTKIND_MOUSEWHEEL,
  APP_EVENTKIND_WINDOWACTIVATE,
  APP_EVENTKIND_WINDOWCLOSE,
  APP_EVENTKIND_WINDOWCREATE,
  APP_EVENTKIND_WINDOWDEACTIVATE,
  APP_EVENTKIND_WINDOWDESTROY,
  APP_EVENTKIND_WINDOWHIDE,
  APP_EVENTKIND_WINDOWMAXIMIZE,
  APP_EVENTKIND_WINDOWMINIMIZE,
  APP_EVENTKIND_WINDOWMOVE,
  APP_EVENTKIND_WINDOWPAINT,
  APP_EVENTKIND_WINDOWRESIZE,
  APP_EVENTKIND_WINDOWSHOW
};

enum app_glversion_t
{
  APP_GLVERSION_UNKNOWN = 0,
  APP_GLVERSION_11      = 11,
  APP_GLVERSION_12      = 12,
  APP_GLVERSION_13      = 13,
  APP_GLVERSION_14      = 14,
  APP_GLVERSION_15      = 15,
  APP_GLVERSION_20      = 20,
  APP_GLVERSION_21      = 21,
  APP_GLVERSION_PLUS    = 99
};

enum app_keyboardkey_t
{
  APP_KEYBOARDKEY_UNKNOWN       = 0,
  APP_KEYBOARDKEY_BACKSPACE     = 8,
  APP_KEYBOARDKEY_TAB           = 9,
  APP_KEYBOARDKEY_ENTER         = 13,
  APP_KEYBOARDKEY_PAUSE         = 19,
  APP_KEYBOARDKEY_ESCAPE        = 27,
  APP_KEYBOARDKEY_SPACE         = 32,
  APP_KEYBOARDKEY_APOSTROPHE    = 39,
  APP_KEYBOARDKEY_COMMA         = 44,
  APP_KEYBOARDKEY_MINUS         = 45,
  APP_KEYBOARDKEY_PERIOD        = 46,
  APP_KEYBOARDKEY_SLASH         = 47,
  APP_KEYBOARDKEY_0             = 48,
  APP_KEYBOARDKEY_1             = 49,
  APP_KEYBOARDKEY_2             = 50,
  APP_KEYBOARDKEY_3             = 51,
  APP_KEYBOARDKEY_4             = 52,
  APP_KEYBOARDKEY_5             = 53,
  APP_KEYBOARDKEY_6             = 54,
  APP_KEYBOARDKEY_7             = 55,
  APP_KEYBOARDKEY_8             = 56,
  APP_KEYBOARDKEY_9             = 57,
  APP_KEYBOARDKEY_SEMICOLON     = 59,
  APP_KEYBOARDKEY_EQUAL         = 61,
  APP_KEYBOARDKEY_A             = 65,
  APP_KEYBOARDKEY_B             = 66,
  APP_KEYBOARDKEY_C             = 67,
  APP_KEYBOARDKEY_D             = 68,
  APP_KEYBOARDKEY_E             = 69,
  APP_KEYBOARDKEY_F             = 70,
  APP_KEYBOARDKEY_G             = 71,
  APP_KEYBOARDKEY_H             = 72,
  APP_KEYBOARDKEY_I             = 73,
  APP_KEYBOARDKEY_J             = 74,
  APP_KEYBOARDKEY_K             = 75,
  APP_KEYBOARDKEY_L             = 76,
  APP_KEYBOARDKEY_M             = 77,
  APP_KEYBOARDKEY_N             = 78,
  APP_KEYBOARDKEY_O             = 79,
  APP_KEYBOARDKEY_P             = 80,
  APP_KEYBOARDKEY_Q             = 81,
  APP_KEYBOARDKEY_R             = 82,
  APP_KEYBOARDKEY_S             = 83,
  APP_KEYBOARDKEY_T             = 84,
  APP_KEYBOARDKEY_U             = 85,
  APP_KEYBOARDKEY_V             = 86,
  APP_KEYBOARDKEY_W             = 87,
  APP_KEYBOARDKEY_X             = 88,
  APP_KEYBOARDKEY_Y             = 89,
  APP_KEYBOARDKEY_Z             = 90,
  APP_KEYBOARDKEY_OPENBRACKET   = 91,
  APP_KEYBOARDKEY_BACKSLASH     = 92,
  APP_KEYBOARDKEY_CLOSEBRACKET  = 93,
  APP_KEYBOARDKEY_GRAVEACCENT   = 96,
  APP_KEYBOARDKEY_DELETE        = 127,
  APP_KEYBOARDKEY_INSERT        = 256,
  APP_KEYBOARDKEY_HOME          = 257,
  APP_KEYBOARDKEY_END           = 258,
  APP_KEYBOARDKEY_PAGEUP        = 259,
  APP_KEYBOARDKEY_PAGEDOWN      = 260,
  APP_KEYBOARDKEY_UPARROW       = 261,
  APP_KEYBOARDKEY_DOWNARROW     = 262,
  APP_KEYBOARDKEY_LEFTARROW     = 263,
  APP_KEYBOARDKEY_RIGHTARROW    = 264,
  APP_KEYBOARDKEY_F1            = 265,
  APP_KEYBOARDKEY_F2            = 266,
  APP_KEYBOARDKEY_F3            = 267,
  APP_KEYBOARDKEY_F4            = 268,
  APP_KEYBOARDKEY_F5            = 269,
  APP_KEYBOARDKEY_F6            = 270,
  APP_KEYBOARDKEY_F7            = 271,
  APP_KEYBOARDKEY_F8            = 272,
  APP_KEYBOARDKEY_F9            = 273,
  APP_KEYBOARDKEY_F10           = 274,
  APP_KEYBOARDKEY_F11           = 275,
  APP_KEYBOARDKEY_F12           = 276,
  APP_KEYBOARDKEY_PRINTSCREEN   = 277,
  APP_KEYBOARDKEY_SCROLLLOCK    = 278,
  APP_KEYBOARDKEY_NP0           = 279,
  APP_KEYBOARDKEY_NP1           = 280,
  APP_KEYBOARDKEY_NP2           = 281,
  APP_KEYBOARDKEY_NP3           = 282,
  APP_KEYBOARDKEY_NP4           = 283,
  APP_KEYBOARDKEY_NP5           = 284,
  APP_KEYBOARDKEY_NP6           = 285,
  APP_KEYBOARDKEY_NP7           = 286,
  APP_KEYBOARDKEY_NP8           = 287,
  APP_KEYBOARDKEY_NP9           = 288,
  APP_KEYBOARDKEY_DECIMAL       = 289,
  APP_KEYBOARDKEY_ADD           = 290,
  APP_KEYBOARDKEY_SUBTRACT      = 291,
  APP_KEYBOARDKEY_MULTIPLY      = 292,
  APP_KEYBOARDKEY_DIVIDE        = 293,
  APP_KEYBOARDKEY_CAPSLOCK      = 294,
  APP_KEYBOARDKEY_NUMLOCK       = 295,
  APP_KEYBOARDKEY_SHIFT         = 296,
  APP_KEYBOARDKEY_CTRL          = 297,
  APP_KEYBOARDKEY_ALT           = 298
};

enum app_mousebutton_t
{
  APP_MOUSEBUTTON_UNKNOWN,
  APP_MOUSEBUTTON_LEFT,
  APP_MOUSEBUTTON_MIDDLE,
  APP_MOUSEBUTTON_RIGHT
};

enum app_mousecursor_t
{
  APP_MOUSECURSOR_UNKNOWN,
  APP_MOUSECURSOR_ARROW,
  APP_MOUSECURSOR_CROSS,
  APP_MOUSECURSOR_HAND,
  APP_MOUSECURSOR_IBEAM,
  APP_MOUSECURSOR_SIZENESW,
  APP_MOUSECURSOR_SIZENS,
  APP_MOUSECURSOR_SIZENWSE,
  APP_MOUSECURSOR_SIZEWE,
  APP_MOUSECURSOR_WAIT
};

enum app_windowstate_t
{
  APP_WINDOWSTATE_UNKNOWN,
  APP_WINDOWSTATE_MAXIMIZE,
  APP_WINDOWSTATE_MINIMIZE,
  APP_WINDOWSTATE_RESTORE
};

enum app_windowstyle_t
{
  APP_WINDOWSTYLE_UNKNOWN,
  APP_WINDOWSTYLE_NOBORDER,
  APP_WINDOWSTYLE_FIXEDBORDER,
  APP_WINDOWSTYLE_RESIZEBORDER
};

struct app_bounds_t
{
  int32_t x;
  int32_t y;
  uint32_t width;
  uint32_t height;
};

struct app_dimension_t
{
  uint32_t width;
  uint32_t height;
};

struct app_displaymode_t
{
  uint32_t refreshrate;
  uint32_t colordepth;
  uint32_t width;
  uint32_t height;
};

struct app_eventlisteners_t
{
  app_eventlistener_t listener;
  void* userdata;
  app_eventlisteners_t* next;
};

struct app_mousewheel_t
{
  int32_t delta;
  uint32_t step;
};

struct app_pixelformat_t
{
  uint32_t redsize;
  uint32_t greensize;
  uint32_t bluesize;
  uint32_t alphasize;
  uint32_t depthsize;
};

struct app_point_t
{
  int32_t x;
  int32_t y;
};

struct app_clipboardevent_t
{
  app_eventkind_t kind;
  app_window_t* window;
};

struct app_displayevent_t
{
  app_eventkind_t kind;
  app_window_t* window;
  app_display_t* display;
};

struct app_keyboardevent_t
{
  app_eventkind_t kind;
  app_window_t* window;
  app_keyboardkey_t key;
  char character;
  bool_t repeat;
  bool_t alt;
  bool_t ctrl;
  bool_t shift;
};

struct app_mouseevent_t
{
  app_eventkind_t kind;
  app_window_t* window;
  app_mousebutton_t button;
  app_point_t point;
  app_mousewheel_t wheel;
  bool_t alt;
  bool_t ctrl;
  bool_t shift;
};

struct app_windowevent_t
{
  app_eventkind_t kind;
  app_window_t* window;
  app_bounds_t bounds;
};

union app_event_t
{
  app_eventkind_t kind;
  app_clipboardevent_t clipboardevent;
  app_displayevent_t displayevent;
  app_keyboardevent_t keyboardevent;
  app_mouseevent_t mouseevent;
  app_windowevent_t windowevent;
};


#ifdef __cplusplus
}
#endif


/*============================================================================================================================================================*/
/*                                                                                                                                                            */
/*============================================================================================================================================================*/
/*       1         2         3         4         5         6         7         8         9         0         1         2         3         4         5        */
/*345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678*/
/*============================================================================================================================================================*/


#endif
