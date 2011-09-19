#include <stdlib.h>
#include <toolkits/dbg/debug.h>
#include <toolkits/app/gl.h>
#include <toolkits/gfx/graphics.h>
#include <toolkits/gfx/texture.h>
#include "reactor.h"
#include <math.h>
#include "lua_cairo.h"

static char* drawmodes[] = {
  "fill",
  "fill",
  "line",
  0 
};

static int graphics_clip_xywh(lua_State *L) {  
  int x = (GLint)luaL_checknumber(L, 1);
  int y = (GLint)luaL_checknumber(L, 2);
  int w = (GLint)luaL_checknumber(L, 3);
  int h = (GLint)luaL_checknumber(L, 4);
  glScissor(x, reactor.h - (y + h), w, h);
  return 0;
}

static int graphics_clip_ltrb(lua_State *L) {  
  int l = (GLint)luaL_checknumber(L, 1);
  int t = (GLint)luaL_checknumber(L, 2);
  int r = (GLint)luaL_checknumber(L, 3);
  int b = (GLint)luaL_checknumber(L, 4);  
  glScissor(l, reactor.h - b, r - l, b - t);
  return 0;
}

static int graphics_setcolor(lua_State* L) {
  int argc = lua_gettop(L);
  GLdouble r = lua_tonumber(L, 1);
  GLdouble g = lua_tonumber(L, 2);
  GLdouble b = lua_tonumber(L, 3);
  GLdouble a = luaL_optnumber(L, 4, 1);

  glColor4d(r, g, b, a);

  return 0;
}

static int clamp(int v, int min, int max) {
  if (v < min) return min;
  if (v > max) return max;
  return v;    
}

#define M_PI 3.14159f

static void drawroundrect2d(int x,int y,int w,int h,int radius)
{
  glPushAttrib(GL_ENABLE_BIT|GL_CURRENT_BIT|GL_COLOR_BUFFER_BIT);
  glDisable(GL_TEXTURE_2D);
  glShadeModel(GL_SMOOTH);
  glEnable(GL_POLYGON_SMOOTH);
  glHint(GL_POLYGON_SMOOTH, GL_NICEST);

  glEnable(GL_BLEND);
  glBlendFunc(GL_SRC_ALPHA,GL_ONE_MINUS_SRC_ALPHA);
  //glColor4ub(clrColor.r,clrColor.g,clrColor.b,clrColor.a);

  glBegin(GL_POLYGON);
  glVertex2i(x+radius,y);
  glVertex2i(x+w-radius,y);

  {
    float i;
    for(i=(float)M_PI*1.5f; i<M_PI*2; i+=0.1f ) {
      glVertex2f(x+w-radius+cos(i)*radius,y+radius+sin(i)*radius);
    }
    glVertex2i(x+w,y+radius);
    glVertex2i(x+w,y+h-radius);
    for(i=0;i<(float)M_PI*0.5f;i+=0.1f)
      glVertex2f(x+w-radius+cos(i)*radius,y+h-radius+sin(i)*radius);
    glVertex2i(x+w-radius,y+h);
    glVertex2i(x+radius,y+h);
    for(i=(float)M_PI*0.5f;i<M_PI;i+=0.1f)
      glVertex2f(x+radius+cos(i)*radius,y+h-radius+sin(i)*radius);
    glVertex2i(x,y+h-radius);
    glVertex2i(x,y+radius);
    for(i=(float)M_PI;i<M_PI*1.5f;i+=0.1f)
      glVertex2f(x+radius+cos(i)*radius,y+radius+sin(i)*radius);
  }
  glEnd();

  glPopAttrib();
}

static void strokeroundrect2d(int x,int y,int w,int h,int radius) 
{  
  glPushAttrib(GL_ENABLE_BIT|GL_CURRENT_BIT|GL_COLOR_BUFFER_BIT);
  glDisable(GL_TEXTURE_2D);
  glShadeModel(GL_SMOOTH);
  glHint(GL_LINE_SMOOTH, GL_NICEST);
  glEnable(GL_LINE_SMOOTH);
  glEnable(GL_BLEND);
  glBlendFunc(GL_SRC_ALPHA,GL_ONE_MINUS_SRC_ALPHA);	
  glLineWidth((GLfloat)1);

  w--;
  h--;
  glBegin(GL_LINE_STRIP);
  {
    float i;
    for(i=(float)M_PI;i<=1.5f*M_PI;i+=0.1f)
      glVertex2f(radius*cos(i)+x+radius,radius*sin(i)+y+radius);
    for(i=1.5f*(float)M_PI;i<=2*M_PI; i+=0.1f)
      glVertex2f(radius*cos(i)+x+w-radius,radius*sin(i)+y+radius);
    for(i=0;i<=0.5f*M_PI; i+=0.1f)
      glVertex2f(radius*cos(i)+x+w-radius,radius*sin(i)+y+h-radius);
    for(i=0.5f*(float)M_PI;i<=M_PI;i+=0.1f) 
      glVertex2f(radius*cos(i)+x+radius,radius*sin(i)+y+h-radius);
    glVertex2i(x,y+radius);
  }
  glEnd();

  glPopAttrib();
}

static int graphics_rect(lua_State* L, gfx_drawmode2d_t mode) {
  int32_t x = luaL_checkint(L, 1);
  int32_t y = luaL_checkint(L, 2);
  int32_t w = clamp(luaL_checkint(L, 3), 0, 0x7fffffff);
  int32_t h = clamp(luaL_checkint(L, 4), 0, 0x7fffffff);
  uint32_t radius = luaL_optint(L, 5, 0);

  if (radius > 0) {
    if (mode == GFX_DRAWMODE2D_FILL) {
      drawroundrect2d(x, y, w, h, radius);  
    }
    else {
      strokeroundrect2d(x, y, w, h, radius);
    }
  }
  else {
    gfx_drawrectangle2d(x, y, w, h, mode);
  }   
  return 0;
}

static int graphics_strokerect(lua_State* L) {
  return graphics_rect(L, GFX_DRAWMODE2D_LINE);
}

static int graphics_fillrect(lua_State* L) {
  return graphics_rect(L, GFX_DRAWMODE2D_FILL);
}

static int graphics_pushstate2d(lua_State* L) {
  gfx_pushstate2d(luaL_checkint(L, 1),luaL_checkint(L, 2));
  return 0;
}

static int graphics_pushstate3d(lua_State* L) {
  gfx_pushstate3d(luaL_checknumber(L, 1),luaL_checknumber(L, 2),luaL_checknumber(L, 3),luaL_checknumber(L, 4), luaL_checknumber(L, 5));
  return 0;
}

static int graphics_popstate(lua_State* L) {
  gfx_popstate();
  return 0;
}

static int graphics_getwidth(lua_State* L) {
  lua_pushinteger(L, reactor.w);
  return 1;
}

static int graphics_getheight(lua_State* L) {
  lua_pushinteger(L, reactor.h);
  return 1;
}

static int graphics_clear(lua_State* L) {
  glClear( GL_COLOR_BUFFER_BIT );
  return 0;
}

static GLuint lastid = -1;

//texture or texturerect
//x -] destination rect
//y
//w
//h -]
//x position in texture, from topleft
//y position in texture, from topleft
static int graphics_draw_texture(lua_State* L) {
  texture_t* texture = check_texture(L, 1);
  int x = luaL_checkint(L, 2);
  int y = luaL_checkint(L, 3);
  int w = luaL_checkint(L, 4);
  int h = luaL_checkint(L, 5);
  int tx = luaL_optint(L, 6, 0);
  int ty = luaL_optint(L, 7, 0);
  
  glMatrixMode (GL_MODELVIEW);
  glLoadIdentity ();
  glPushMatrix ();

  if (texture->id != lastid) {
    glBindTexture (GL_TEXTURE_2D, texture->id);
  }

  lastid = texture->id;

  glBegin( GL_QUADS ); {
    float x1, y1, x2, y2;
    x1 = (float)tx/texture->w;
    y1 = (float)ty/texture->h;
    x2 = ((float)(tx + w))/texture->w;
    y2 = (float)(ty + h)/texture->h;

    glTexCoord2f (x1, y1);
    glVertex2i( x, y );

    glTexCoord2f (x1, y2);
    glVertex2i( x, y + h );

    glTexCoord2f (x2, y2);
    glVertex2i( x + w, y + h );

    glTexCoord2f (x2, y1);
    glVertex2i( x + w, y );	
  } glEnd();

  glPopMatrix();
  return 0;
}

typedef struct image {
  int w;
  int h;
  unsigned char* data;
  cairo_surface_t* surface;
  cairo_t* cr;
} image_t;


//* size is the size of the area you would like to update
//* sourceRes is the resolution of the entire source image (can be larger, but not smaller than size)
//* sourceOfs is the offset into the source image
//* destOfs is the offset into the destination texture

//glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
//glPixelStorei(GL_UNPACK_ROW_LENGTH, sourceRes.width);
//pixel_type *Source = SourceImage + sourceOfs.x + sourceOfs.y * sourceRes.width;
//glTexSubImage2D(GL_TEXTURE_2D, 0, destOfs.x, destOfs.y, size.x, size.y, ..., Source);


//upload surface data to texture
static int graphics_update_texture(lua_State* L) {
  texture_t* texture = check_texture(L, 1);
  reactor_cairo_surface_t* surface = check_reactor_cairo_surface(L, 2);

  if (texture->id != lastid) {
    glBindTexture (GL_TEXTURE_2D, texture->id);
  }

  lastid = texture->id;

  if lua_isnoneornil(L, 3) {
    glTexSubImage2D(GL_TEXTURE_2D, 0, 0, 0, surface->w, surface->h, GL_BGRA, GL_UNSIGNED_BYTE, surface->data);
  }
  else{
    int imagex, imagey, w, h, texturex, texturey;
    unsigned char* data;

    imagex = luaL_checkint(L, 3);
    imagey = luaL_checkint(L, 4);
    w = luaL_checkint(L, 5);
    h = luaL_checkint(L, 6);
    texturex = luaL_optint(L, 7, imagex);
    texturey = luaL_optint(L, 8, imagey);

    if ( w < 1 || h < 1 ) {
      return 0;
    }

    //glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
    glPixelStorei(GL_UNPACK_ROW_LENGTH, surface->w);
    data = surface->data + (imagex + (imagey * surface->w))*4;

    glTexSubImage2D(GL_TEXTURE_2D, 0, texturex, texturey, w, h, GL_BGRA, GL_UNSIGNED_BYTE, data);

    //glPixelStorei(GL_UNPACK_ALIGNMENT, 4);
    glPixelStorei( GL_UNPACK_ROW_LENGTH, 0 );
  }

  return 0;
}


int luaopen_reactor_graphics(lua_State* L) {
  DBG_ENTER();
  { 
    static const luaL_reg module_functions[] = {
      {"getwidth", graphics_getwidth},
      {"getheight", graphics_getheight},
      {"setcolor", graphics_setcolor},    
      {"clipxywh", graphics_clip_xywh},
      {"clipltrb", graphics_clip_ltrb},    
      {"fillrect", graphics_fillrect},
      {"strokerect", graphics_strokerect},
      {"pushstate2d", graphics_pushstate2d},
      {"pushstate3d", graphics_pushstate3d},
      {"popstate", graphics_popstate},
      {"clear", graphics_clear},        
      {"drawtexture", graphics_draw_texture},
      {"updatetexture", graphics_update_texture},
      {NULL, NULL}
    };

    lua_newtable(L); 
    luaL_register(L, 0, module_functions);

    lua_pushliteral(L, "texture");
    luaopen_reactor_graphics_texture(L);
    lua_settable(L, -3);
  }
  DBG_RETURN(1);
}

