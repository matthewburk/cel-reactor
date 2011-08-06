
/*============================================================================================================================================================*/
/*                                                                                                                                                            */
/*============================================================================================================================================================*/
/*       1         2         3         4         5         6         7         8         9         0         1         2         3         4         5        */
/*345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678*/
/*============================================================================================================================================================*/


/**
 * 
 */
SYS_INLINE void mat_vector_zero( mat_vector_t* vector )
{
  (*vector).f[0] = 0.0f;
  (*vector).f[1] = 0.0f;
  (*vector).f[2] = 0.0f;
  (*vector).f[3] = 0.0f;
}

/**
 * 
 */
SYS_INLINE float mat_vector_getx( mat_vector_t* vector )
{
  return (*vector).f[0];
}

/**
 * 
 */
SYS_INLINE void mat_vector_setx( mat_vector_t* vector, float x )
{
  (*vector).f[0] = x;
}

/**
 * 
 */
SYS_INLINE float mat_vector_gety( mat_vector_t* vector )
{
  return (*vector).f[1];
}

/**
 * 
 */
SYS_INLINE void mat_vector_sety( mat_vector_t* vector, float y )
{
  (*vector).f[1] = y;
}

/**
 * 
 */
SYS_INLINE float mat_vector_getz( mat_vector_t* vector )
{
  return (*vector).f[2];
}

/**
 * 
 */
SYS_INLINE void mat_vector_setz( mat_vector_t* vector, float z )
{
  (*vector).f[2] = z;
}

/**
 * 
 */
SYS_INLINE float mat_vector_getw( mat_vector_t* vector )
{
  return (*vector).f[3];
}

/**
 * 
 */
SYS_INLINE void mat_vector_setw( mat_vector_t* vector, float w )
{
  (*vector).f[3] = w;
}

/**
 * 
 */
SYS_INLINE void mat_vector_getxyz( mat_vector_t* vector, float* x, float* y, float* z )
{
  *x = (*vector).f[0];
  *y = (*vector).f[1];
  *z = (*vector).f[2];
}

/**
 * 
 */
SYS_INLINE void mat_vector_setxyz( mat_vector_t* vector, float x, float y, float z )
{
  (*vector).f[0] = x;
  (*vector).f[1] = y;
  (*vector).f[2] = z;
}

/**
 * 
 */
SYS_INLINE void mat_vector_getxyzw( mat_vector_t* vector, float* x, float* y, float* z, float* w )
{
  *x = (*vector).f[0];
  *y = (*vector).f[1];
  *z = (*vector).f[2];
  *w = (*vector).f[3];
}

/**
 * 
 */
SYS_INLINE void mat_vector_setxyzw( mat_vector_t* vector, float x, float y, float z, float w )
{
  (*vector).f[0] = x;
  (*vector).f[1] = y;
  (*vector).f[2] = z;
  (*vector).f[3] = w;
}

/**
 * 
 */
SYS_INLINE bool_t mat_vector_equal( mat_vector_t* vector1, const mat_vector_t* vector2 )
{
  return ( ( (*vector1).f[0] == (*vector2).f[0] ) && ( (*vector1).f[1] == (*vector2).f[1] ) && ( (*vector1).f[2] == (*vector2).f[2] ) && ( (*vector1).f[3] == (*vector2).f[3] ) );
}

/**
 * 
 */
SYS_INLINE bool_t mat_vector_nequal( mat_vector_t* vector1, const mat_vector_t* vector2 )
{
  return !( ( (*vector1).f[0] == (*vector2).f[0] ) && ( (*vector1).f[1] == (*vector2).f[1] ) && ( (*vector1).f[2] == (*vector2).f[2] ) && ( (*vector1).f[3] == (*vector2).f[3] ) );
}

/**
 * 
 */
SYS_INLINE void mat_vector_add( mat_vector_t* vector1, const mat_vector_t* vector2 )
{
  (*vector1).f[0] += (*vector2).f[0];
  (*vector1).f[1] += (*vector2).f[1];
  (*vector1).f[2] += (*vector2).f[2];
}

/**
 * 
 */
SYS_INLINE void mat_vector_subtract( mat_vector_t* vector1, const mat_vector_t* vector2 )
{
  (*vector1).f[0] -= (*vector2).f[0];
  (*vector1).f[1] -= (*vector2).f[1];
  (*vector1).f[2] -= (*vector2).f[2];
}

/**
 * 
 */
SYS_INLINE void mat_vector_multiply( mat_vector_t* vector1, const mat_vector_t* vector2 )
{
  (*vector1).f[0] *= (*vector2).f[0];
  (*vector1).f[1] *= (*vector2).f[1];
  (*vector1).f[2] *= (*vector2).f[2];
}

/**
 * 
 */
SYS_INLINE void mat_vector_divide( mat_vector_t* vector1, const mat_vector_t* vector2 )
{
  (*vector1).f[0] /= (*vector2).f[0];
  (*vector1).f[1] /= (*vector2).f[1];
  (*vector1).f[2] /= (*vector2).f[2];
}

/**
 * 
 */
SYS_INLINE float mat_vector_dot( mat_vector_t* vector1, const mat_vector_t* vector2 )
{
  return ( (*vector1).f[0] * (*vector2).f[0] ) + ( (*vector1).f[1] * (*vector2).f[1] ) + ( (*vector1).f[2] * (*vector2).f[2] );
}


/*============================================================================================================================================================*/
/*                                                                                                                                                            */
/*============================================================================================================================================================*/
/*       1         2         3         4         5         6         7         8         9         0         1         2         3         4         5        */
/*345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678*/
/*============================================================================================================================================================*/
