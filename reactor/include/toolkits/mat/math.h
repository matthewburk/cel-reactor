
#ifndef MAT_MATH_H
#define MAT_MATH_H


/*============================================================================================================================================================*/
/*                                                                                                                                                            */
/*============================================================================================================================================================*/
/*       1         2         3         4         5         6         7         8         9         0         1         2         3         4         5        */
/*345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678*/
/*============================================================================================================================================================*/


#include <toolkits/sys/intrinsics.h>
#include <toolkits/sys/stdbool.h>


#ifdef __cplusplus
extern "C" {
#endif


#define MAT_NAMESPACE "mat"


#define MAT_PI      3.141592654f
#define MAT_2PI     6.283185307f
#define MAT_1DIVPI  0.318309886f
#define MAT_1DIV2PI 0.159154943f
#define MAT_PIDIV2  1.570796327f
#define MAT_PIDIV4  0.785398163f
#define MAT_3PIDIV2 4.712388981f
#define MAT_DEGTORAD( degree ) ((degree) * (MAT_PI / 180.0f))
#define MAT_RADTODEG( radian ) ((radian) * (180.0f / MAT_PI))


typedef struct mat_vector_t mat_vector_t;
typedef struct mat_matrix_t mat_matrix_t;


SYS_ALIGN16( struct mat_vector_t )
{
  float f[4];
};

SYS_ALIGN16( struct mat_matrix_t )
{
  float f[4][4];
};


float mat_sin( float x );
float mat_sinh( float x );
float mat_asin( float x );
float mat_cos( float x );
float mat_cosh( float x );
float mat_acos( float x );
float mat_tan( float x );
float mat_tanh( float x );
float mat_atan( float x );
float mat_abs( float x );
float mat_ceil( float x );
float mat_exp( float x );
float mat_floor( float x );
float mat_log( float x );
float mat_log10( float x );
float mat_mod( float x, float y );
float mat_pow( float x, float y );
float mat_sqrt( float x );


#include "math.inl"


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
