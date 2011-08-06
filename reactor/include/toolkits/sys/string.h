
#ifndef SYS_STRING_H
#define SYS_STRING_H


/*============================================================================================================================================================*/
/*                                                                                                                                                            */
/*============================================================================================================================================================*/
/*       1         2         3         4         5         6         7         8         9         0         1         2         3         4         5        */
/*345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678*/
/*============================================================================================================================================================*/


#include <toolkits/sys/system.h>


#ifdef __cplusplus
extern "C" {
#endif


SYS_API char* sys_string_create( size_t size );
SYS_API void sys_string_destroy( char* str );

SYS_API char* sys_string_duplicate( const char* str );

SYS_API int sys_string_compare( const char* str1, const char* str2 );
SYS_API int sys_string_ncompare( const char* str1, const char* str2, size_t number );

SYS_API char* sys_string_concatenate( char* dst, const char* src );
SYS_API char* sys_string_nconcatenate( char* dst, const char* src, size_t number );

SYS_API char* sys_string_copy( char* dst, const char* src );
SYS_API char* sys_string_ncopy( char* dst, const char* src, size_t number );

SYS_API const char* sys_string_substring( const char* str, const char* substr );

SYS_API size_t sys_string_length( const char* str );
SYS_API size_t sys_string_nlength( const char* str, size_t number );

SYS_API int sys_string_store( char* dst, const char* format, ... );
SYS_API int sys_string_nstore( char* dst, size_t number, const char* format, ... );


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
