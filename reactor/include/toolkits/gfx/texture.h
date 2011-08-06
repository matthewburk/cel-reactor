
#ifndef GFX_TEXTURE_H
#define GFX_TEXTURE_H


/*============================================================================================================================================================*/
/*                                                                                                                                                            */
/*============================================================================================================================================================*/
/*       1         2         3         4         5         6         7         8         9         0         1         2         3         4         5        */
/*345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678*/
/*============================================================================================================================================================*/


#include <toolkits/gfx/graphics.h>


#ifdef __cplusplus
extern "C" {
#endif


SYS_API gfx_texture_t* gfx_texture_create( gfx_image_t* image );
SYS_API void gfx_texture_destroy( gfx_texture_t* texture );

SYS_API void gfx_texture_bind( gfx_texture_t* texture );

SYS_API void gfx_texture_getdimension( gfx_texture_t* texture, app_dimension_t* dimension );
SYS_API void gfx_texture_getimagedimension( gfx_texture_t* texture, app_dimension_t* dimension );

SYS_API gfx_texturewrap_t gfx_texture_getwraps( gfx_texture_t* texture );
SYS_API void gfx_texture_setwraps( gfx_texture_t* texture, gfx_texturewrap_t wraps );

SYS_API gfx_texturewrap_t gfx_texture_getwrapt( gfx_texture_t* texture );
SYS_API void gfx_texture_setwrapt( gfx_texture_t* texture, gfx_texturewrap_t wrapt );

SYS_API gfx_texturemagfilter_t gfx_texture_getmagfilter( gfx_texture_t* texture );
SYS_API void gfx_texture_setmagfilter( gfx_texture_t* texture, gfx_texturemagfilter_t magfilter );

SYS_API gfx_textureminfilter_t gfx_texture_getminfilter( gfx_texture_t* texture );
SYS_API void gfx_texture_setminfilter( gfx_texture_t* texture, gfx_textureminfilter_t minfilter );

SYS_API bool_t gfx_texture_hasmipmap( gfx_texture_t* texture );
SYS_API void gfx_texture_generatemipmap( gfx_texture_t* texture, bool_t mipmap );


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
