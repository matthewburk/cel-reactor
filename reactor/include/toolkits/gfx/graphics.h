
#ifndef GFX_GRAPHICS_H
#define GFX_GRAPHICS_H


/*============================================================================================================================================================*/
/*                                                                                                                                                            */
/*============================================================================================================================================================*/
/*       1         2         3         4         5         6         7         8         9         0         1         2         3         4         5        */
/*345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678*/
/*============================================================================================================================================================*/


#include <toolkits/app/gl.h>


#ifdef __cplusplus
extern "C" {
#endif


#define GFX_NAMESPACE "gfx"


#define GFX_BUFFEROFFSET( s, m ) ((ubyte_t*)0 + offsetof( s, m ))


/* enumerated types */
typedef enum gfx_drawmode2d_t gfx_drawmode2d_t;
typedef enum gfx_imageformat_t gfx_imageformat_t;
typedef enum gfx_imagetype_t gfx_imagetype_t;
typedef enum gfx_texturemagfilter_t gfx_texturemagfilter_t;
typedef enum gfx_textureminfilter_t gfx_textureminfilter_t;
typedef enum gfx_texturewrap_t gfx_texturewrap_t;

/* opaque types */
//typedef struct gfx_font_t gfx_font_t;
typedef struct gfx_image_t gfx_image_t;
typedef struct gfx_texture_t gfx_texture_t;

/* transparent types */
//typedef struct gfx_extents2d_t gfx_extents2d_t;
//typedef struct gfx_fontmetrics_t gfx_fontmetrics_t;


enum gfx_drawmode2d_t
{
  GFX_DRAWMODE2D_UNKNOWN,
  GFX_DRAWMODE2D_FILL,
  GFX_DRAWMODE2D_LINE
};

enum gfx_imageformat_t
{
  GFX_IMAGEFORMAT_UNKNOWN        = 0,
  GFX_IMAGEFORMAT_RGB            = GL_RGB,
  GFX_IMAGEFORMAT_RGBALPHA       = GL_RGBA,
  GFX_IMAGEFORMAT_LUMINANCE      = GL_LUMINANCE,
  GFX_IMAGEFORMAT_LUMINANCEALPHA = GL_LUMINANCE_ALPHA
};

enum gfx_imagetype_t
{
  GFX_IMAGETYPE_UNKNOWN,
  GFX_IMAGETYPE_PNG
};

enum gfx_texturemagfilter_t
{
  GFX_TEXTUREMAGFILTER_UNKNOWN = 0,
  GFX_TEXTUREMAGFILTER_NEAREST = GL_NEAREST,
  GFX_TEXTUREMAGFILTER_LINEAR  = GL_LINEAR
};

enum gfx_textureminfilter_t
{
  GFX_TEXTUREMINFILTER_UNKNOWN              = 0,
  GFX_TEXTUREMINFILTER_NEAREST              = GL_NEAREST,
  GFX_TEXTUREMINFILTER_LINEAR               = GL_LINEAR,
  GFX_TEXTUREMINFILTER_NEARESTMIPMAPNEAREST = GL_NEAREST_MIPMAP_NEAREST,
  GFX_TEXTUREMINFILTER_LINEARMIPMAPNEAREST  = GL_LINEAR_MIPMAP_NEAREST,
  GFX_TEXTUREMINFILTER_NEARESTMIPMAPLINEAR  = GL_NEAREST_MIPMAP_LINEAR,
  GFX_TEXTUREMINFILTER_LINEARMIPMAPLINEAR   = GL_LINEAR_MIPMAP_LINEAR
};

enum gfx_texturewrap_t
{
  GFX_TEXTUREWRAP_UNKNOWN = 0,
  GFX_TEXTUREWRAP_CLAMP   = GL_CLAMP,
  GFX_TEXTUREWRAP_REPEAT  = GL_REPEAT
};

struct gfx_extents2d_t
{
  int32_t xmin;
  int32_t xmax;
  int32_t ymin;
  int32_t ymax;
};

//struct gfx_fontmetrics_t
//{
//  int32_t advance;
//  gfx_extents2d_t extents;
//};


SYS_API void gfx_pushstate2d( uint32_t width, uint32_t height );
SYS_API void gfx_pushstate3d( uint32_t width, uint32_t height, float fovy, uint32_t near, uint32_t far );
SYS_API void gfx_popstate();

SYS_API void gfx_drawarc2d( int32_t x, int32_t y, uint32_t radius, uint32_t segments, float angle, float length );
SYS_API void gfx_drawcircle2d( int32_t x, int32_t y, uint32_t radius, uint32_t segments, gfx_drawmode2d_t mode );
SYS_API void gfx_drawline2d( int32_t x1, int32_t y1, int32_t x2, int32_t y2 );
SYS_API void gfx_drawpoint2d( int32_t x, int32_t y );
SYS_API void gfx_drawrectangle2d( int32_t x, int32_t y, uint32_t width, uint32_t height, gfx_drawmode2d_t mode );
SYS_API void gfx_drawroundrect2d( int32_t x, int32_t y, uint32_t width, uint32_t height, uint32_t radius, uint32_t segments, gfx_drawmode2d_t mode );
SYS_API void gfx_drawtriangle2d( int32_t x1, int32_t y1, int32_t x2, int32_t y2, int32_t x3, int32_t y3, gfx_drawmode2d_t mode );


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
