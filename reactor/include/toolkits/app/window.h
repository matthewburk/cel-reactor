
#ifndef APP_WINDOW_H
#define APP_WINDOW_H


/*============================================================================================================================================================*/
/*                                                                                                                                                            */
/*============================================================================================================================================================*/
/*       1         2         3         4         5         6         7         8         9         0         1         2         3         4         5        */
/*345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678*/
/*============================================================================================================================================================*/


#include <toolkits/app/application.h>


#ifdef __cplusplus
extern "C" {
#endif


SYS_API app_window_t* app_window_create( const char* title, app_windowstyle_t style, const app_bounds_t* bounds, app_pixelformat_t* format );
SYS_API void app_window_destroy( app_window_t* window );

SYS_API void app_window_addlistener( app_window_t* window, app_eventlistener_t listener, void* userdata );
SYS_API void app_window_removelistener( app_window_t* window, app_eventlistener_t listener, void* userdata );

SYS_API bool_t app_window_listen( app_window_t* window );
SYS_API bool_t app_window_wait( app_window_t* window );
SYS_API void app_window_quit( app_window_t* window );

SYS_API void app_window_present( app_window_t* window );

SYS_API bool_t app_window_isactive( app_window_t* window );

SYS_API bool_t app_window_isvisible( app_window_t* window );
SYS_API void app_window_setvisible( app_window_t* window, bool_t visible );

SYS_API app_windowstate_t app_window_getstate( app_window_t* window );
SYS_API void app_window_setstate( app_window_t* window, app_windowstate_t state );

SYS_API app_windowstyle_t app_window_getstyle( app_window_t* window );
SYS_API void app_window_setstyle( app_window_t* window, app_windowstyle_t style, const app_bounds_t* bounds );

SYS_API void app_window_getbounds( app_window_t* window, app_bounds_t* bounds );
SYS_API void app_window_setbounds( app_window_t* window, const app_bounds_t* bounds );

SYS_API void app_window_getclipboard( app_window_t* window, char** text );
SYS_API void app_window_setclipboard( app_window_t* window, const char* text );

SYS_API app_mousecursor_t app_window_getcursor( app_window_t* window );
SYS_API void app_window_setcursor( app_window_t* window, app_mousecursor_t cursor );


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
