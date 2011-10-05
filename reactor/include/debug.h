
#ifndef DBG_DEBUG_H
#define DBG_DEBUG_H


/*============================================================================================================================================================*/
/*                                                                                                                                                            */
/*============================================================================================================================================================*/
/*       1         2         3         4         5         6         7         8         9         0         1         2         3         4         5        */
/*345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678*/
/*============================================================================================================================================================*/


#include <stddef.h>


#ifdef __cplusplus
extern "C" {
#endif


#ifdef _WIN32
  #ifdef DBG_APIEXPORT
    #define DBG_API __declspec(dllexport)
  #else
    #define DBG_API __declspec(dllimport)
  #endif
#else
  #define DBG_API
#endif


#define DBG_NAMESPACE "dbg"


#ifdef NDEBUG

  #define DBG_ASSERT( expression ) ((void)0)

#else

  #define DBG_ASSERT( expression ) (!!(expression) || (dbg_assert( __FUNCTION__, __FILE__, __LINE__, #expression ), 0))

  DBG_API void dbg_assert( const char* function, const char* file, size_t line, const char* expression );

#endif

#ifdef NDBG

  #define DBG_DUMP( keyword, address, size ) ((void)0)
  #define DBG_ENTER() ((void)0)
  #define DBG_POP() ((void)0)
  #define DBG_PRINT( keyword, ... ) ((void)0)
  #define DBG_PUSH( options ) ((void)0)
  #define DBG_RETURN( value ) return( value )
  #define DBG_RETURN_VOID() return

#else

  #define DBG_DUMP( keyword, address, size ) dbg_dump( __FUNCTION__, __FILE__, __LINE__, keyword, #address, address, size )
  #define DBG_ENTER() dbg_enter( __FUNCTION__, __FILE__, __LINE__ )
  #define DBG_POP() dbg_pop( __FUNCTION__, __FILE__, __LINE__ )
  #define DBG_PRINT( keyword, ... ) dbg_print( __FUNCTION__, __FILE__, __LINE__, keyword, __VA_ARGS__ )
  #define DBG_PUSH( options ) dbg_push( __FUNCTION__, __FILE__, __LINE__, options )
  #define DBG_RETURN( value ) dbg_return( __FUNCTION__, __FILE__, __LINE__ ); return( value )
  #define DBG_RETURN_VOID() dbg_return( __FUNCTION__, __FILE__, __LINE__ ); return

  DBG_API void dbg_dump( const char* function, const char* file, size_t line, const char* keyword, const char* expression, const void* address, size_t size );
  DBG_API void dbg_enter( const char* function, const char* file, size_t line );
  DBG_API void dbg_pop( const char* function, const char* file, size_t line );
  DBG_API void dbg_print( const char* function, const char* file, size_t line, const char* keyword, const char* format, ... );
  DBG_API void dbg_push( const char* function, const char* file, size_t line, const char* options );
  DBG_API void dbg_return( const char* function, const char* file, size_t line );

#endif


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
