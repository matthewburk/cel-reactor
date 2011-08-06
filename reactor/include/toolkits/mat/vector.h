
#ifndef MAT_VECTOR_H
#define MAT_VECTOR_H


/*============================================================================================================================================================*/
/*                                                                                                                                                            */
/*============================================================================================================================================================*/
/*       1         2         3         4         5         6         7         8         9         0         1         2         3         4         5        */
/*345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678*/
/*============================================================================================================================================================*/


#include <toolkits/mat/math.h>


#ifdef __cplusplus
extern "C" {
#endif


SYS_API mat_vector_t* mat_vector_create();
SYS_API void mat_vector_destroy( mat_vector_t* vector );

void mat_vector_zero( mat_vector_t* vector );

float mat_vector_getx( mat_vector_t* vector );
void mat_vector_setx( mat_vector_t* vector, float x );

float mat_vector_gety( mat_vector_t* vector );
void mat_vector_sety( mat_vector_t* vector, float y );

float mat_vector_getz( mat_vector_t* vector );
void mat_vector_setz( mat_vector_t* vector, float z );

float mat_vector_getw( mat_vector_t* vector );
void mat_vector_setw( mat_vector_t* vector, float w );

void mat_vector_getxyz( mat_vector_t* vector, float* x, float* y, float* z );
void mat_vector_setxyz( mat_vector_t* vector, float x, float y, float z );

void mat_vector_getxyzw( mat_vector_t* vector, float* x, float* y, float* z, float* w );
void mat_vector_setxyzw( mat_vector_t* vector, float x, float y, float z, float w );

bool_t mat_vector_equal( mat_vector_t* vector1, const mat_vector_t* vector2 );
bool_t mat_vector_nequal( mat_vector_t* vector1, const mat_vector_t* vector2 );

void mat_vector_add( mat_vector_t* vector1, const mat_vector_t* vector2 );
void mat_vector_subtract( mat_vector_t* vector1, const mat_vector_t* vector2 );
void mat_vector_multiply( mat_vector_t* vector1, const mat_vector_t* vector2 );
void mat_vector_divide( mat_vector_t* vector1, const mat_vector_t* vector2 );

float mat_vector_dot( mat_vector_t* vector1, const mat_vector_t* vector2 );


#include "vector.inl"


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
