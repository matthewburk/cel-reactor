#include <stdlib.h>
#include <math.h>
#include "reactor_graphics.h"

extern GLuint texobj;

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
  glScissor(x, window.h - (y + h), w, h);
  if (glGetError()) return luaL_error(L, "%d", glGetError());
  return 0;
}

static int graphics_clip_ltrb(lua_State *L) {  
  int l = (GLint)luaL_checknumber(L, 1);
  int t = (GLint)luaL_checknumber(L, 2);
  int r = (GLint)luaL_checknumber(L, 3);
  int b = (GLint)luaL_checknumber(L, 4);  
  glScissor(l, window.h - b, r - l, b - t);
  if (glGetError()) return luaL_error(L, "%d", glGetError());
  return 0;
}

static int graphics_setcolor(lua_State* L) {  
  const char* s = lua_tostring(L, 1);
  glColor4ub(s[0], s[1], s[2], s[3]);
  return 0;
}

static int graphics_setcolorf(lua_State* L) {
  int argc = lua_gettop(L);
  GLdouble r = lua_tonumber(L, 1);
  GLdouble g = lua_tonumber(L, 2);
  GLdouble b = lua_tonumber(L, 3);
  GLdouble a = luaL_optnumber(L, 4, 1);

  glColor4d(r, g, b, a);
  if (glGetError()) return luaL_error(L, "%d", glGetError());

  return 0;
}

static int clamp(int v, int min, int max) {
  if (v < min) return min;
  if (v > max) return max;
  return v;    
}

#define M_PI 3.14159f

//static void drawroundrect2d(int x,int y,int w,int h,int radius)
//{
//  glPushAttrib(GL_ENABLE_BIT|GL_CURRENT_BIT|GL_COLOR_BUFFER_BIT);
//  glDisable(GL_TEXTURE_2D);
//  glShadeModel(GL_SMOOTH);
//  glEnable(GL_POLYGON_SMOOTH);
//  glHint(GL_POLYGON_SMOOTH, GL_NICEST);
//
//  glEnable(GL_BLEND);
//  glBlendFunc(GL_SRC_ALPHA,GL_ONE_MINUS_SRC_ALPHA);
//  //glColor4ub(clrColor.r,clrColor.g,clrColor.b,clrColor.a);
//
//  glBegin(GL_POLYGON);
//  glVertex2i(x+radius,y);
//  glVertex2i(x+w-radius,y);
//
//  {
//    float i;
//    for(i=(float)M_PI*1.5f; i<M_PI*2; i+=0.1f ) {
//      glVertex2f(x+w-radius+cos(i)*radius,y+radius+sin(i)*radius);
//    }
//    glVertex2i(x+w,y+radius);
//    glVertex2i(x+w,y+h-radius);
//    for(i=0;i<(float)M_PI*0.5f;i+=0.1f)
//      glVertex2f(x+w-radius+cos(i)*radius,y+h-radius+sin(i)*radius);
//    glVertex2i(x+w-radius,y+h);
//    glVertex2i(x+radius,y+h);
//    for(i=(float)M_PI*0.5f;i<M_PI;i+=0.1f)
//      glVertex2f(x+radius+cos(i)*radius,y+h-radius+sin(i)*radius);
//    glVertex2i(x,y+h-radius);
//    glVertex2i(x,y+radius);
//    for(i=(float)M_PI;i<M_PI*1.5f;i+=0.1f)
//      glVertex2f(x+radius+cos(i)*radius,y+radius+sin(i)*radius);
//  }
//  glEnd();
//
//  glPopAttrib();
//}
//
//static void strokeroundrect2d(int x,int y,int w,int h,int radius) 
//{  
//  glPushAttrib(GL_ENABLE_BIT|GL_CURRENT_BIT|GL_COLOR_BUFFER_BIT);
//  glDisable(GL_TEXTURE_2D);
//  glShadeModel(GL_SMOOTH);
//  glHint(GL_LINE_SMOOTH, GL_NICEST);
//  glEnable(GL_LINE_SMOOTH);
//  glEnable(GL_BLEND);
//  glBlendFunc(GL_SRC_ALPHA,GL_ONE_MINUS_SRC_ALPHA);	
//  glLineWidth((GLfloat)1);
//
//  w--;
//  h--;
//  glBegin(GL_LINE_STRIP);
//  {
//    float i;
//    for(i=(float)M_PI;i<=1.5f*M_PI;i+=0.1f)
//      glVertex2f(radius*cos(i)+x+radius,radius*sin(i)+y+radius);
//    for(i=1.5f*(float)M_PI;i<=2*M_PI; i+=0.1f)
//      glVertex2f(radius*cos(i)+x+w-radius,radius*sin(i)+y+radius);
//    for(i=0;i<=0.5f*M_PI; i+=0.1f)
//      glVertex2f(radius*cos(i)+x+w-radius,radius*sin(i)+y+h-radius);
//    for(i=0.5f*(float)M_PI;i<=M_PI;i+=0.1f) 
//      glVertex2f(radius*cos(i)+x+radius,radius*sin(i)+y+h-radius);
//    glVertex2i(x,y+radius);
//  }
//  glEnd();
//
//  glPopAttrib();
//}
//
//static int graphics_rect(lua_State* L, gfx_drawmode2d_t mode) {
//  int32_t x = luaL_checkint(L, 1);
//  int32_t y = luaL_checkint(L, 2);
//  int32_t w = clamp(luaL_checkint(L, 3), 0, 0x7fffffff);
//  int32_t h = clamp(luaL_checkint(L, 4), 0, 0x7fffffff);
//  uint32_t radius = luaL_optint(L, 5, 0);
//
//  if (radius > 0) {
//    if (mode == GFX_DRAWMODE2D_FILL) {
//      drawroundrect2d(x, y, w, h, radius);  
//    }
//    else {
//      strokeroundrect2d(x, y, w, h, radius);
//    }
//  }
//  else {
//    gfx_drawrectangle2d(x, y, w, h, mode);
//  }   
//  return 0;
//}
//
//static int graphics_strokerect(lua_State* L) {
//  return graphics_rect(L, GFX_DRAWMODE2D_LINE);
//}
//
static int graphics_fillrect(lua_State* L) {
  double x = luaL_checknumber(L, 1);
  double y = luaL_checknumber(L, 2);
  double w = luaL_checknumber(L, 3);
  double h = luaL_checknumber(L, 4);

  glDisable( GL_TEXTURE_2D );
  glBegin( GL_QUADS ); {   
    glVertex2d( x, y );    
    glVertex2d( x, y + h );    
    glVertex2d( x + w, y + h );    
    glVertex2d( x + w, y );	
  } glEnd();
  glEnable( GL_TEXTURE_2D );
  if (glGetError()) return luaL_error(L, "%d", glGetError());
  return 0;
}

static int graphics_pushstate2d(lua_State* L) {
  GLdouble width = luaL_checknumber(L, 1);
  GLdouble height = luaL_checknumber(L, 2);
  glPushAttrib( GL_COLOR_BUFFER_BIT | GL_ENABLE_BIT | GL_HINT_BIT | GL_SCISSOR_BIT | GL_TRANSFORM_BIT | GL_VIEWPORT_BIT );

  glDisable( GL_DEPTH_TEST );
  glDisable( GL_LIGHTING );

  glEnable( GL_BLEND );
  //glBlendFunc( GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA );
  glBlendFuncSeparate(GL_ONE, GL_ONE_MINUS_SRC_ALPHA, GL_ONE, GL_ZERO);
  if (glGetError()) return luaL_error(L, "%d", glGetError());


  glEnable( GL_LINE_SMOOTH );
  glHint( GL_LINE_SMOOTH_HINT, GL_NICEST );

  glEnable( GL_POINT_SMOOTH );
  glHint( GL_POINT_SMOOTH_HINT, GL_NICEST );

  glEnable( GL_SCISSOR_TEST );
  glScissor( 0, 0, (GLsizei)width, (GLsizei)height );

  glEnable( GL_TEXTURE_2D );

  glTexEnvf( GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE );

  glEnableClientState(GL_VERTEX_ARRAY);
  glEnableClientState(GL_TEXTURE_COORD_ARRAY);

  glViewport( 0, 0, (GLsizei)width, (GLsizei)height );

  glMatrixMode( GL_PROJECTION );
  glPushMatrix();
  glLoadIdentity();
  glOrtho( 0.0f, width, height, 0.0f, -1.0f, 1.0f );

  glMatrixMode( GL_MODELVIEW );
  glPushMatrix();
  glLoadIdentity();
  if (glGetError()) return luaL_error(L, "%d", glGetError());

  glClearColor(.5, .5, 1, 1);
  return 0;
}

static int graphics_popstate(lua_State* L) {
  glMatrixMode( GL_MODELVIEW );
  glPopMatrix();

  glMatrixMode( GL_PROJECTION );
  glPopMatrix();

  glPopAttrib();

  glDisableClientState(GL_VERTEX_ARRAY);
  glDisableClientState(GL_TEXTURE_COORD_ARRAY);
  if (glGetError()) return luaL_error(L, "%d", glGetError());
  return 0;
}

static int graphics_clear(lua_State* L) {
  glClear( GL_COLOR_BUFFER_BIT );if (glGetError()) return luaL_error(L, "%d", glGetError());
  return 0;
}

//texture or texturerect
//x -] destination rect
//y
//w
//h -]
//l position in texture, from topleft defines left of center portion
//t position in texture, from topleft defines top of center portion
//r 
//b
static int graphics_draw_texture_9grid(lua_State* L) {
  static GLubyte quadindexes[4*9] = {
    0, 4, 5, 1,
    1, 5, 6, 2,
    2, 6, 7, 3,

    4, 8, 9, 5,
    5, 9,10, 6,
    6,10,11, 7,

    8,12,13, 9,
    9,13,14,10,
    10,14,15,11
  };
  texture_t* texture = check_texture(L, 1);
  double x = luaL_checknumber(L, 2);
  double y = luaL_checknumber(L, 3);
  double w = luaL_checknumber(L, 4);
  double h = luaL_checknumber(L, 5);
  int l = luaL_checkint(L, 6);
  int t = luaL_optint(L, 7, l);
  int r = luaL_optint(L, 8, l);
  int b = luaL_optint(L, 9, t);
  int tw = texture->np2w;
  int th = texture->np2h;
  
  if (texobj != texture->id) {
    texobj = texture->id;
    glBindTexture (GL_TEXTURE_2D, texture->id);    
  }
  if (glGetError()) return luaL_error(L, "%d", glGetError());

  {
    vertexdata_2vt_t vertex[16];
    float sa[4] = {0, (float)l/texture->w, (float)(tw-r)/texture->w, (float)tw/texture->w};
    float ta[4] = {0, (float)t/texture->h, (float)(th-b)/texture->h, (float)th/texture->h};
    float xa[4] = {x+0, x+l, x+(w-r), x+w};
    float ya[4] = {y+0, y+t, y+(h-b), y+h};    

    int i, j;
    for (i=0, j=0; i < 4; i++, j++) {
      vertex[i].tex.s = sa[j];
      vertex[i].tex.t = ta[0];
      vertex[i].vertex.x = xa[j];
      vertex[i].vertex.y = ya[0];
    }
    for (i=4, j=0; i < 8; i++, j++) {
      vertex[i].tex.s = sa[j];
      vertex[i].tex.t = ta[1];
      vertex[i].vertex.x = xa[j];
      vertex[i].vertex.y = ya[1];
    }
    for (i=8, j=0; i < 12; i++, j++) {
      vertex[i].tex.s = sa[j];
      vertex[i].tex.t = ta[2];
      vertex[i].vertex.x = xa[j];
      vertex[i].vertex.y = ya[2];
    }
    for (i=12, j=0; i < 16; i++, j++) {
      vertex[i].tex.s = sa[j];
      vertex[i].tex.t = ta[3];
      vertex[i].vertex.x = xa[j];
      vertex[i].vertex.y = ya[3];
    }

    //for ( i = 0; i < 4; i++) {
    //  printf("(%f, %f [%f, %f]) ", vertex[i].vertex.x, vertex[i].vertex.y, vertex[i].tex.s, vertex[i].tex.t);      
    //}
    //printf("\n");
    //for ( i = 4; i < 8; i++) {
    //  printf("(%f, %f [%f, %f]) ", vertex[i].vertex.x, vertex[i].vertex.y, vertex[i].tex.s, vertex[i].tex.t);         
    //}
    //printf("\n");
    //for ( i = 8; i < 12; i++) {
    //  printf("(%f, %f [%f, %f]) ", vertex[i].vertex.x, vertex[i].vertex.y, vertex[i].tex.s, vertex[i].tex.t);          
    //}
    //printf("\n");
    //for ( i = 12; i < 16; i++) {
    //  printf("(%f, %f [%f, %f]) ", vertex[i].vertex.x, vertex[i].vertex.y, vertex[i].tex.s, vertex[i].tex.t);          
    //}
    //printf("\n=========================\n");
    //fflush(stdout);
      

    glEnableClientState(GL_VERTEX_ARRAY);if (glGetError()) return luaL_error(L, "%d", glGetError());
  glEnableClientState(GL_TEXTURE_COORD_ARRAY);if (glGetError()) return luaL_error(L, "%d", glGetError());

    glVertexPointer(2, GL_FLOAT, sizeof(vertexdata_2vt_t), &vertex[0].vertex);if (glGetError()) return luaL_error(L, "%d", glGetError());
    glTexCoordPointer(2, GL_FLOAT, sizeof(vertexdata_2vt_t), &vertex[0].tex);if (glGetError()) return luaL_error(L, "%d", glGetError());
    glDrawElements(GL_QUADS, 4*9, GL_UNSIGNED_BYTE, quadindexes);if (glGetError()) return luaL_error(L, "%d", glGetError());
    if (glGetError()) return luaL_error(L, "%d", glGetError());
  }

  

  return 0;
}

static int graphics_draw_texture_9grid_borders(lua_State* L) {
  static GLubyte quadindexes[4*8] = {
    0, 4, 5, 1,
    1, 5, 6, 2,
    2, 6, 7, 3,

    4, 8, 9, 5,
    //5, 9,10, 6,
    6,10,11, 7,

    8,12,13, 9,
    9,13,14,10,
    10,14,15,11
  };
  texture_t* texture = check_texture(L, 1);
  double x = luaL_checknumber(L, 2);
  double y = luaL_checknumber(L, 3);
  double w = luaL_checknumber(L, 4);
  double h = luaL_checknumber(L, 5);
  int l = luaL_checkint(L, 6);
  int t = luaL_optint(L, 7, l);
  int r = luaL_optint(L, 8, l);
  int b = luaL_optint(L, 9, t);
  int tw = texture->np2w;
  int th = texture->np2h;
  

  if (texobj != texture->id) {
    texobj = texture->id;
    glBindTexture (GL_TEXTURE_2D, texture->id);    
  }
  if (glGetError()) return luaL_error(L, "%d", glGetError());

  {
    vertexdata_2vt_t vertex[16];
    float sa[4] = {0, (float)l/texture->w, (float)(tw-r)/texture->w, (float)tw/texture->w};
    float ta[4] = {0, (float)t/texture->h, (float)(th-b)/texture->h, (float)th/texture->h};
    float xa[4] = {x+0, x+l, x+(w-r), x+w};
    float ya[4] = {y+0, y+t, y+(h-b), y+h};    

    int i, j;
    for (i=0, j=0; i < 4; i++, j++) {
      vertex[i].tex.s = sa[j];
      vertex[i].tex.t = ta[0];
      vertex[i].vertex.x = xa[j];
      vertex[i].vertex.y = ya[0];
    }
    for (i=4, j=0; i < 8; i++, j++) {
      vertex[i].tex.s = sa[j];
      vertex[i].tex.t = ta[1];
      vertex[i].vertex.x = xa[j];
      vertex[i].vertex.y = ya[1];
    }
    for (i=8, j=0; i < 12; i++, j++) {
      vertex[i].tex.s = sa[j];
      vertex[i].tex.t = ta[2];
      vertex[i].vertex.x = xa[j];
      vertex[i].vertex.y = ya[2];
    }
    for (i=12, j=0; i < 16; i++, j++) {
      vertex[i].tex.s = sa[j];
      vertex[i].tex.t = ta[3];
      vertex[i].vertex.x = xa[j];
      vertex[i].vertex.y = ya[3];
    }

    //for ( i = 0; i < 4; i++) {
    //  printf("(%f, %f [%f, %f]) ", vertex[i].vertex.x, vertex[i].vertex.y, vertex[i].tex.s, vertex[i].tex.t);      
    //}
    //printf("\n");
    //for ( i = 4; i < 8; i++) {
    //  printf("(%f, %f [%f, %f]) ", vertex[i].vertex.x, vertex[i].vertex.y, vertex[i].tex.s, vertex[i].tex.t);         
    //}
    //printf("\n");
    //for ( i = 8; i < 12; i++) {
    //  printf("(%f, %f [%f, %f]) ", vertex[i].vertex.x, vertex[i].vertex.y, vertex[i].tex.s, vertex[i].tex.t);          
    //}
    //printf("\n");
    //for ( i = 12; i < 16; i++) {
    //  printf("(%f, %f [%f, %f]) ", vertex[i].vertex.x, vertex[i].vertex.y, vertex[i].tex.s, vertex[i].tex.t);          
    //}
    //printf("\n=========================\n");
    //fflush(stdout);
      

    glEnableClientState(GL_VERTEX_ARRAY);
    glEnableClientState(GL_TEXTURE_COORD_ARRAY);

    glVertexPointer(2, GL_FLOAT, sizeof(vertexdata_2vt_t), &vertex[0].vertex);
    glTexCoordPointer(2, GL_FLOAT, sizeof(vertexdata_2vt_t), &vertex[0].tex);

    
    glDrawElements(GL_QUADS, 4*8, GL_UNSIGNED_BYTE, quadindexes);
    if (glGetError()) return luaL_error(L, "%d", glGetError());
  }

  

  return 0;
}
//texture or texturerect
//x -] destination rect
//y
//w
//h -]
//x position in texture, from topleft
//y position in texture, from topleft
static int graphics_draw_texture(lua_State* L) {
  texture_t* texture = check_texture(L, 1);
  double x = luaL_checknumber(L, 2);
  double y = luaL_checknumber(L, 3);
  double w = luaL_checknumber(L, 4);
  double h = luaL_checknumber(L, 5);
  int tx = luaL_optint(L, 6, 0);
  int ty = luaL_optint(L, 7, 0);
  int tw = luaL_optint(L, 8, texture->np2w);
  int th = luaL_optint(L, 9, texture->np2h);

  if (texobj != texture->id) {
    texobj = texture->id;
    glBindTexture (GL_TEXTURE_2D, texture->id);    
  }

  {
    vertexdata_2vt_t vertex[4];
    float x1, y1, x2, y2;
    x1 = (float)tx/texture->w;
    y1 = (float)ty/texture->h;
    x2 = ((float)(tx + tw))/texture->w;
    y2 = (float)(ty + th)/texture->h;
    

    vertex[0].tex.s = x1;
    vertex[0].tex.t = y1;

    vertex[0].vertex.x = x;
    vertex[0].vertex.y = y;    

    vertex[1].tex.s = x1;
    vertex[1].tex.t = y2;

    vertex[1].vertex.x = x;
    vertex[1].vertex.y = y+h;    

    vertex[2].tex.s = x2;
    vertex[2].tex.t = y2;

    vertex[2].vertex.x = x+w;
    vertex[2].vertex.y = y+h ;    

    vertex[3].tex.s = x2;
    vertex[3].tex.t = y1;

    vertex[3].vertex.x = x+w;
    vertex[3].vertex.y = y;    

    glVertexPointer(2, GL_FLOAT, sizeof(vertexdata_2vt_t), &vertex[0].vertex);
    glTexCoordPointer(2, GL_FLOAT, sizeof(vertexdata_2vt_t), &vertex[0].tex);
    glDrawArrays(GL_QUADS, 0, 4);
  }

  

  return 0;
}

//static int graphics_draw_texture(lua_State* L) {
//  texture_t* texture = check_texture(L, 1);
//  double x = luaL_checknumber(L, 2);
//  double y = luaL_checknumber(L, 3);
//  double w = luaL_checknumber(L, 4);
//  double h = luaL_checknumber(L, 5);
//  int tx = luaL_optint(L, 6, 0);
//  int ty = luaL_optint(L, 7, 0);
//  int tw = luaL_optint(L, 8, texture->np2w);
//  int th = luaL_optint(L, 9, texture->np2h);
//  
//  //glMatrixMode (GL_MODELVIEW);
//  //glLoadIdentity ();
//  //glPushMatrix ();
//
//  if (texture->id != lastid) {
//    glBindTexture (GL_TEXTURE_2D, texture->id);
//  }
//
//  lastid = texture->id;
//
//  glBegin( GL_QUADS ); {
//    float x1, y1, x2, y2;
//    x1 = (float)tx/texture->w;
//    y1 = (float)ty/texture->h;
//    x2 = ((float)(tx + tw))/texture->w;
//    y2 = (float)(ty + th)/texture->h;
//
//    glTexCoord2f(x1, y1);
//    glVertex2d( x, y );
//
//    glTexCoord2f (x1, y2);
//    glVertex2d( x, y + h );
//
//    glTexCoord2f (x2, y2);
//    glVertex2d( x + w, y + h );
//
//    glTexCoord2f (x2, y1);
//    glVertex2d( x + w, y );	
//  } glEnd();
//
//  //glPopMatrix();
//  return 0;
//}

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
  unsigned char* data = (unsigned char*)lua_touserdata(L, 2);
  int data_w = luaL_checkint(L, 3);
  int data_h = luaL_checkint(L, 4);

  
  if (texobj != texture->id) {
    texobj = texture->id;
    glBindTexture (GL_TEXTURE_2D, texture->id);    
  }
  if (glGetError()) return luaL_error(L, "%d", glGetError());

  //TODO add function to cario bindings
  //cairo_surface_flush(surface->surface);

  if lua_isnoneornil(L, 8) {
    glTexSubImage2D(GL_TEXTURE_2D, 0, 0, 0, data_w, data_h, GL_BGRA, GL_UNSIGNED_BYTE, data);
    { int error = glGetError();
    if (error) return luaL_error(L, "bad texsub %d", error);}
  }
  else{
    int imagex, imagey, w, h, texturex, texturey;

    imagex = luaL_checkint(L, 5);
    imagey = luaL_checkint(L, 6);
    w = luaL_checkint(L, 7);
    h = luaL_checkint(L, 8);
    texturex = luaL_optint(L, 9, imagex);
    texturey = luaL_optint(L, 10, imagey);

    if ( w < 1 || h < 1 ) {
      return 0;
    }

    //glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
    glPixelStorei(GL_UNPACK_ROW_LENGTH, data_w);if (glGetError()) return luaL_error(L, "%d", glGetError());
    data = data + (imagex + (imagey * data_w))*4;if (glGetError()) return luaL_error(L, "%d", glGetError());

    glTexSubImage2D(GL_TEXTURE_2D, 0, texturex, texturey, w, h, GL_BGRA, GL_UNSIGNED_BYTE, data);if (glGetError()) return luaL_error(L, "%d", glGetError());

    //glPixelStorei(GL_UNPACK_ALIGNMENT, 4);
    glPixelStorei( GL_UNPACK_ROW_LENGTH, 0 );
    if (glGetError()) return luaL_error(L, "%d", glGetError());
  }

  return 0;
}

static int glRotate_L(lua_State* L) {
  GLdouble angle = luaL_checknumber(L, 1);
  GLdouble x = luaL_optnumber(L, 2, 0);
  GLdouble y = luaL_optnumber(L, 3, 0);
  GLdouble z = luaL_optnumber(L, 4, 1);
  glRotated(angle, x, y, z);
  return 0;
}

static int glTranslate_L(lua_State* L) {  
  GLdouble x = luaL_checknumber(L, 1);
  GLdouble y = luaL_checknumber(L, 2);  
  glTranslated(x, y, 0);
  return 0;
}

static int glScale_L(lua_State* L) {  
  GLdouble x = luaL_checknumber(L, 1);
  GLdouble y = luaL_checknumber(L, 2);  
  glScaled(x, y, 1);
  return 0;
}

static int glPushMatrix_L(lua_State* L) {
  glPushMatrix();
  return 0;
}

static int glPopMatrix_L(lua_State* L) {
  glPopMatrix();
  return 0;
}

static int glLoadIdentity_L(lua_State* L) {
  glLoadIdentity();
  return 0;
}



GLuint texobj = 0;

void checkself_texture(lua_State* L, texture_t** rpp) {
  *rpp = luaL_checkudata(L, 1, "reactor_graphics_texture_t");  
  if (0 == (*rpp)->id) {
    luaL_argerror(L, 1, "texture is invalid becuase it has been destroyed");
  }
}

texture_t* check_texture(lua_State* L, int arg) {
  texture_t* texture = luaL_checkudata(L, arg, "reactor_graphics_texture_t");  
  if (0 == texture->id) {
    luaL_argerror(L, arg, "texture is invalid becuase it has been destroyed");
  }
  return texture;
}

static int graphics_texture_create_L(lua_State* L) {
  {
    int w = 0;
    int h = 0;
    texture_t* texture = 0;  
    texture = lua_newuserdata(L, sizeof(texture_t));
    luaL_getmetatable(L, "reactor_graphics_texture_t");
    lua_setmetatable(L, -2);

    w = luaL_checkint(L, 1);
    h = luaL_checkint(L, 2);

    glGenTextures( 1, &texture->id );
    if (glGetError()) return luaL_error(L, "%d", glGetError());
    glBindTexture( GL_TEXTURE_2D, texture->id );
    texobj = texture->id;
    if (glGetError()) return luaL_error(L, "%d", glGetError());

    for ( texture->w = 1; texture->w < w; texture->w <<= 1 );
    for ( texture->h = 1; texture->h < h; texture->h <<= 1 );  

    texture->np2w = w;
    texture->np2h = h;

    glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP );
    if (glGetError()) return luaL_error(L, "%d", glGetError());
    glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP );
    if (glGetError()) return luaL_error(L, "%d", glGetError());
    glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR );
    if (glGetError()) return luaL_error(L, "%d", glGetError());
    glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR );
    if (glGetError()) return luaL_error(L, "%d", glGetError());

    glTexImage2D( GL_TEXTURE_2D, 0, GL_RGBA8, texture->w, texture->h, 0, GL_BGRA, GL_UNSIGNED_BYTE, 0 );
    if (glGetError()) return luaL_error(L, "%d", glGetError());
  }
  return(1);
}

static int graphics_texture__gc_L(lua_State* L) {
  texture_t* texture = lua_touserdata(L, 1); 
  if (texture->id)
    glDeleteTextures(1, &texture->id);     
  return(0);
}

static int graphics_texture_destroy_L(lua_State* L) {
  texture_t* texture = 0;  

  checkself_texture(L, &texture);
  {
    glDeleteTextures(1, &texture->id);
    texture->id = 0;
  }
  return(0);
}

static void luaopen_reactor_graphics_texture(lua_State* L) {
  {  
    static const luaL_reg texture_functions[] = {
      {"__gc", graphics_texture__gc_L},
      {"destroy", graphics_texture_destroy_L},    
      {NULL, NULL}
    }; 

    static const luaL_reg module_functions[] = {
      {"create", graphics_texture_create_L}, 
      {"destroy", graphics_texture_destroy_L}, 
      {NULL, NULL}
    };

    luaL_newmetatable(L, "reactor_graphics_texture_t");
    lua_pushvalue(L, -1);
    lua_setfield(L, -2, "__index");
    luaL_register(L, 0, texture_functions);
    lua_pop(L, 1);
    
    lua_newtable(L); 
    luaL_register(L, 0, module_functions);
  }
}

extern void luaopen_reactor_graphics_texture(lua_State* L);
int luaopen_reactor_graphics(lua_State* L) {
  { 
    static const luaL_reg module_functions[] = {
      {"setcolor", graphics_setcolor},    
      {"setcolorf", graphics_setcolorf},   
      {"clipxywh", graphics_clip_xywh},
      {"clipltrb", graphics_clip_ltrb},    
      {"fillrect", graphics_fillrect},
      {"pushstate2d", graphics_pushstate2d},
      {"popstate", graphics_popstate},
      {"clear", graphics_clear},        
      {"drawtexture", graphics_draw_texture},
      {"draw9grid", graphics_draw_texture_9grid},
      {"draw9gridborders", graphics_draw_texture_9grid_borders},   
      
      //{"createtexture", graphics_create_texture},
      //{"destroytexture", graphics_destroy_texture},
      {"updatetexture", graphics_update_texture},

      {"rotate", glRotate_L},
      {"translate", glTranslate_L},
      {"scale", glScale_L},
      {"pushmatrix", glPushMatrix_L},
      {"popmatrix", glPopMatrix_L},
      {"loadidentity", glLoadIdentity_L},      
      {NULL, NULL}
    };

    lua_newtable(L); 
    luaL_register(L, 0, module_functions);

    lua_pushliteral(L, "texture");
    luaopen_reactor_graphics_texture(L);
    lua_settable(L, -3);
  }
  return(1);
}

