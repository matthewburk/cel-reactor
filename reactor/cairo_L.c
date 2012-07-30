#include <string.h>
#include <cairo.h>
#include <cairo-ft.h>
#include <ft2build.h>
#include FT_FREETYPE_H
#include <lua.h>
#include <lauxlib.h>
#include <lualib.h>

typedef struct lua_cairo_t lua_cairo_t;
typedef struct lua_cairo_surface_t lua_cairo_surface_t;
typedef struct lua_cairo_pattern_t lua_cairo_pattern_t;
typedef struct lua_cairo_font_face_t lua_cairo_font_face_t;

struct lua_cairo_t
{
  cairo_t* cairo;
};

struct lua_cairo_surface_t
{
  cairo_surface_t* surface;
  int w;
  int h;
  unsigned char* data;
};

struct lua_cairo_pattern_t
{
  cairo_pattern_t* pattern;
};

struct lua_cairo_font_face_t
{
  FT_Face ftface;
  cairo_font_face_t* crface;
};

luaopen_cairo_surface( lua_State* L );
luaopen_cairo_pattern( lua_State* L );
luaopen_cairo_font( lua_State* L );
lua_cairo_t* lua_cairo_check( lua_State* L, int narg );
lua_cairo_surface_t* lua_cairo_surface_check( lua_State* L, int narg );
lua_cairo_pattern_t* lua_cairo_pattern_check( lua_State* L, int narg );
lua_cairo_font_face_t* lua_cairo_font_face_check( lua_State* L, int narg );

static int cairo_create_l( lua_State* L );
static int cairo__gc_l( lua_State* L );
static int cairo_destroy_l( lua_State* L );
static int cairo_save_l( lua_State* L );
static int cairo_restore_l( lua_State* L );
static int cairo_push_group_l( lua_State* L );
static int cairo_push_group_with_content_l( lua_State* L );
static int cairo_pop_group_l( lua_State* L );
static int cairo_pop_group_to_source_l( lua_State* L );
static int cairo_set_source_rgb_l( lua_State* L );
static int cairo_set_source_rgba_l( lua_State* L );
static int cairo_set_source_l( lua_State* L );
static int cairo_set_source_surface_l( lua_State* L );
static int cairo_get_source_l( lua_State* L );
static int cairo_set_antialias_l( lua_State* L );
static int cairo_get_antialias_l( lua_State* L );
static int cairo_set_dash_l( lua_State* L );
static int cairo_get_dash_count_l( lua_State* L );
static int cairo_get_dash_l( lua_State* L );
static int cairo_set_line_cap_l( lua_State* L );
static int cairo_get_line_cap_l( lua_State* L );
static int cairo_set_line_join_l( lua_State* L );
static int cairo_get_line_join_l( lua_State* L );
static int cairo_set_line_width_l( lua_State* L );
static int cairo_get_line_width_l( lua_State* L );
static int cairo_set_miter_limit_l( lua_State* L );
static int cairo_get_miter_limit_l( lua_State* L );
static int cairo_set_operator_l( lua_State* L );
static int cairo_get_operator_l( lua_State* L );
static int cairo_clip_l( lua_State* L );
static int cairo_clip_preserve_l( lua_State* L );
static int cairo_clip_extents_l( lua_State* L );
static int cairo_in_clip_l( lua_State* L );
static int cairo_reset_clip_l( lua_State* L );
static int cairo_fill_l( lua_State* L );
static int cairo_fill_preserve_l( lua_State* L );
static int cairo_fill_extents_l( lua_State* L );
static int cairo_in_fill_l( lua_State* L );
static int cairo_mask_l( lua_State* L );
static int cairo_mask_surface_l( lua_State* L );
static int cairo_paint_l( lua_State* L );
static int cairo_paint_with_alpha_l( lua_State* L );
static int cairo_stroke_l( lua_State* L );
static int cairo_stroke_preserve_l( lua_State* L );
static int cairo_stroke_extents_l( lua_State* L );
static int cairo_in_stroke_l( lua_State* L );
static int cairo_new_path_l( lua_State* L );
static int cairo_new_sub_path_l( lua_State* L );
static int cairo_close_path_l( lua_State* L );
static int cairo_arc_l( lua_State* L );
static int cairo_arc_negative_l( lua_State* L );
static int cairo_curve_to_l( lua_State* L );
static int cairo_line_to_l( lua_State* L );
static int cairo_move_to_l( lua_State* L );
static int cairo_rectangle_l( lua_State* L );
static int cairo_text_path_l( lua_State* L );
static int cairo_rel_curve_to_l( lua_State* L );
static int cairo_rel_line_to_l( lua_State* L );
static int cairo_rel_move_to_l( lua_State* L );
static int cairo_path_extents_l( lua_State* L );
static int cairo_set_font_size_l( lua_State* L );
static int cairo_set_font_options_l( lua_State* L );
static int cairo_get_font_options_l( lua_State* L );
static int cairo_set_font_face_l( lua_State* L );
static int cairo_show_text_l( lua_State* L );
static int cairo_font_extents_l( lua_State* L );
static int cairo_text_extents_l( lua_State* L );
static int cairo_translate_l( lua_State* L );
static int cairo_scale_l( lua_State* L );
static int cairo_rotate_l( lua_State* L );
static int cairo_identity_matrix_l( lua_State* L );


static char* cairo_antialias_lst[] = {
  "default",
  "none",
  "gray",
  "subpixel",
  0
};

static char* cairo_content_lst[] = {
  "color",
  "alpha",
  "color alpha",
  0
};

static char* cairo_line_cap_lst[] = {
  "butt",
  "round",
  "square",
  0
};

static char* cairo_line_join_lst[] = {
  "miter",
  "round",
  "bevel",
  0
};

static char* cairo_operator_lst[] = {
  "clear",
  "source",
  "over",
  "in",
  "out",
  "atop",
  "dest",
  "dest over",
  "dest in",
  "dest out",
  "dest atop",
  "xor",
  "add",
  "saturate",
  "multiply",
  "screen",
  "overlay",
  "darken",
  "lighten",
  "color dodge",
  "color burn",
  "hard light",
  "soft light",
  "difference",
  "exclusion",
  "hsl hue",
  "hsl saturation",
  "hsl color",
  "hsl luminosity",
  0
};


/**
 * 
 */
int luaopen_cairo( lua_State* L )
{
  static const luaL_reg methods[] = {
    {"__gc", cairo__gc_l},
    {"destroy", cairo_destroy_l},
    {"save", cairo_save_l},
    {"restore", cairo_restore_l},
    {"push_group", cairo_push_group_l},
    {"push_group_with_content", cairo_push_group_with_content_l},
    {"pop_group", cairo_pop_group_l},
    {"pop_group_to_source", cairo_pop_group_to_source_l},
    {"set_source_rgb", cairo_set_source_rgb_l},
    {"set_source_rgba", cairo_set_source_rgba_l},
    {"set_source", cairo_set_source_l},
    {"set_source_surface", cairo_set_source_surface_l},
    {"get_source", cairo_get_source_l},
    {"set_antialias", cairo_set_antialias_l},
    {"get_antialias", cairo_get_antialias_l},
    {"set_dash", cairo_set_dash_l},
    {"get_dash_count", cairo_get_dash_count_l},
    {"get_dash", cairo_get_dash_l},
    {"set_line_cap", cairo_set_line_cap_l},
    {"get_line_cap", cairo_get_line_cap_l},
    {"set_line_join", cairo_set_line_join_l},
    {"get_line_join", cairo_get_line_join_l},
    {"set_line_width", cairo_set_line_width_l},
    {"get_line_width", cairo_get_line_width_l},
    {"set_miter_limit", cairo_set_miter_limit_l},
    {"get_miter_limit", cairo_get_miter_limit_l},
    {"set_operator", cairo_set_operator_l},
    {"get_operator", cairo_get_operator_l},
    {"clip", cairo_clip_l},
    {"clip_preserve", cairo_clip_preserve_l},
    {"clip_extents", cairo_clip_extents_l},
    {"in_clip", cairo_in_clip_l},
    {"reset_clip", cairo_reset_clip_l},
    {"fill", cairo_fill_l},
    {"fill_preserve", cairo_fill_preserve_l},
    {"fill_extents", cairo_fill_extents_l},
    {"in_fill", cairo_in_fill_l},
    {"mask", cairo_mask_l},
    {"mask_surface", cairo_mask_surface_l},
    {"paint", cairo_paint_l},
    {"paint_with_alpha", cairo_paint_with_alpha_l},
    {"stroke", cairo_stroke_l},
    {"stroke_preserve", cairo_stroke_preserve_l},
    {"stroke_extents", cairo_stroke_extents_l},
    {"in_stroke", cairo_in_stroke_l},
    {"new_path", cairo_new_path_l},
    {"new_sub_path", cairo_new_sub_path_l},
    {"close_path", cairo_close_path_l},
    {"arc", cairo_arc_l},
    {"arc_negative", cairo_arc_negative_l},
    {"curve_to", cairo_curve_to_l},
    {"line_to", cairo_line_to_l},
    {"move_to", cairo_move_to_l},
    {"rectangle", cairo_rectangle_l},
    {"text_path", cairo_text_path_l},
    {"rel_curve_to", cairo_rel_curve_to_l},
    {"rel_line_to", cairo_rel_line_to_l},
    {"rel_move_to", cairo_rel_move_to_l},
    {"path_extents", cairo_path_extents_l},
    {"set_font_size", cairo_set_font_size_l},
    {"set_font_options", cairo_set_font_options_l},
    {"get_font_options", cairo_get_font_options_l},
    {"set_font_face", cairo_set_font_face_l},
    {"show_text", cairo_show_text_l},
    {"font_extents", cairo_font_extents_l},
    {"text_extents", cairo_text_extents_l},
    {"translate", cairo_translate_l},
    {"scale", cairo_scale_l},
    {"rotate", cairo_rotate_l},
    {"identity_matrix", cairo_identity_matrix_l},
    {0, 0}
  };

  static const luaL_reg cairo[] = {
    {"create", cairo_create_l},
    {"destroy", cairo_destroy_l},
    {"save", cairo_save_l},
    {"restore", cairo_restore_l},
    {"push_group", cairo_push_group_l},
    {"push_group_with_content", cairo_push_group_with_content_l},
    {"pop_group", cairo_pop_group_l},
    {"pop_group_to_source", cairo_pop_group_to_source_l},
    {"set_source_rgb", cairo_set_source_rgb_l},
    {"set_source_rgba", cairo_set_source_rgba_l},
    {"set_source", cairo_set_source_l},
    {"set_source_surface", cairo_set_source_surface_l},
    {"get_source", cairo_get_source_l},
    {"set_antialias", cairo_set_antialias_l},
    {"get_antialias", cairo_get_antialias_l},
    {"set_dash", cairo_set_dash_l},
    {"get_dash_count", cairo_get_dash_count_l},
    {"get_dash", cairo_get_dash_l},
    {"set_line_cap", cairo_set_line_cap_l},
    {"get_line_cap", cairo_get_line_cap_l},
    {"set_line_join", cairo_set_line_join_l},
    {"get_line_join", cairo_get_line_join_l},
    {"set_line_width", cairo_set_line_width_l},
    {"get_line_width", cairo_get_line_width_l},
    {"set_miter_limit", cairo_set_miter_limit_l},
    {"get_miter_limit", cairo_get_miter_limit_l},
    {"set_operator", cairo_set_operator_l},
    {"get_operator", cairo_get_operator_l},
    {"clip", cairo_clip_l},
    {"clip_preserve", cairo_clip_preserve_l},
    {"clip_extents", cairo_clip_extents_l},
    {"in_clip", cairo_in_clip_l},
    {"reset_clip", cairo_reset_clip_l},
    {"fill", cairo_fill_l},
    {"fill_preserve", cairo_fill_preserve_l},
    {"fill_extents", cairo_fill_extents_l},
    {"in_fill", cairo_in_fill_l},
    {"mask", cairo_mask_l},
    {"mask_surface", cairo_mask_surface_l},
    {"paint", cairo_paint_l},
    {"paint_with_alpha", cairo_paint_with_alpha_l},
    {"stroke", cairo_stroke_l},
    {"stroke_preserve", cairo_stroke_preserve_l},
    {"stroke_extents", cairo_stroke_extents_l},
    {"in_stroke", cairo_in_stroke_l},
    {"new_path", cairo_new_path_l},
    {"new_sub_path", cairo_new_sub_path_l},
    {"close_path", cairo_close_path_l},
    {"arc", cairo_arc_l},
    {"arc_negative", cairo_arc_negative_l},
    {"curve_to", cairo_curve_to_l},
    {"line_to", cairo_line_to_l},
    {"move_to", cairo_move_to_l},
    {"rectangle", cairo_rectangle_l},
    {"text_path", cairo_text_path_l},
    {"rel_curve_to", cairo_rel_curve_to_l},
    {"rel_line_to", cairo_rel_line_to_l},
    {"rel_move_to", cairo_rel_move_to_l},
    {"path_extents", cairo_path_extents_l},
    {"set_font_size", cairo_set_font_size_l},
    {"set_font_options", cairo_set_font_options_l},
    {"get_font_options", cairo_get_font_options_l},
    {"set_font_face", cairo_set_font_face_l},
    {"show_text", cairo_show_text_l},
    {"font_extents", cairo_font_extents_l},
    {"text_extents", cairo_text_extents_l},
    {"translate", cairo_translate_l},
    {"scale", cairo_scale_l},
    {"rotate", cairo_rotate_l},
    {"identity_matrix", cairo_identity_matrix_l},
    {0, 0}
  };

  luaL_newmetatable( L, "lua_cairo_t" );
  lua_pushvalue( L, -1 ); /* duplicate the metatable */
  lua_setfield( L, -2, "__index" ); /* set the metamethod to the metatable */

  luaL_register( L, 0, methods ); /* pack the methods in the metatable */
  lua_pop( L, 1 );

  luaL_register( L, "cairo", cairo );

  luaopen_cairo_surface( L );
  luaopen_cairo_pattern( L );
  luaopen_cairo_font( L );

  return( 1 );
}

/**
 * 
 */
static lua_cairo_t* lua_cairo_check( lua_State* L, int narg )
{
  lua_cairo_t* lc = (lua_cairo_t*)luaL_checkudata( L, narg, "lua_cairo_t" );

  if ( !lc->cairo ) {
    luaL_argerror( L, 1, "cairo context has been destroyed" );
  }

  return( lc );
}

/**
 * 
 */
static int cairo_create_l( lua_State* L )
{
  lua_cairo_surface_t* lcs = lua_cairo_surface_check( L, 1 );

  lua_cairo_t* lc = (lua_cairo_t*)lua_newuserdata( L, sizeof( lua_cairo_t ) );
  memset( lc, 0, sizeof( lua_cairo_t ) );

  luaL_getmetatable( L, "lua_cairo_t" );
  lua_setmetatable( L, -2 );

  lc->cairo = cairo_create( lcs->surface );

  return( 1 );
}

/**
 * 
 */
static int cairo__gc_l( lua_State* L )
{
  lua_cairo_t* lc = (lua_cairo_t*)lua_touserdata( L, 1 );

  if ( lc->cairo ) {
    cairo_destroy( lc->cairo );
    lc->cairo = 0;
  }

  return( 0 );
}

/**
 * 
 */
static int cairo_destroy_l( lua_State* L )
{
  lua_cairo_t* lc = lua_cairo_check( L, 1 );

  cairo_destroy( lc->cairo );
  lc->cairo = 0;

  return( 0 );
}

/**
 * 
 */
static int cairo_save_l( lua_State* L )
{
  lua_cairo_t* lc = lua_cairo_check( L, 1 );

  cairo_save( lc->cairo );

  return( 0 );
}

/**
 * 
 */
static int cairo_restore_l( lua_State* L )
{
  lua_cairo_t* lc = lua_cairo_check( L, 1 );

  cairo_restore( lc->cairo );

  return( 0 );
}

/**
 * 
 */
static int cairo_push_group_l( lua_State* L )
{
  lua_cairo_t* lc = lua_cairo_check( L, 1 );

  cairo_push_group( lc->cairo );

  return( 0 );
}

/**
 * 
 */
static int cairo_push_group_with_content_l( lua_State* L )
{
  lua_cairo_t* lc = lua_cairo_check( L, 1 );

  cairo_push_group_with_content( lc->cairo, luaL_checkoption( L, 2, "color", cairo_content_lst ) );

  return( 0 );
}

/**
 * 
 */
static int cairo_pop_group_l( lua_State* L )
{
  lua_cairo_t* lc = lua_cairo_check( L, 1 );

  lua_cairo_pattern_t* lcp = (lua_cairo_pattern_t*)lua_newuserdata( L, sizeof( lua_cairo_pattern_t ) );
  memset( lcp, 0, sizeof( lua_cairo_pattern_t ) );

  luaL_getmetatable( L, "lua_cairo_pattern_t" );
  lua_setmetatable( L, -2 );

  lcp->pattern = cairo_pop_group( lc->cairo );

  return( 1 );
}

/**
 * 
 */
static int cairo_pop_group_to_source_l( lua_State* L )
{
  lua_cairo_t* lc = lua_cairo_check( L, 1 );

  cairo_pop_group_to_source( lc->cairo );

  return( 0 );
}

/**
 * 
 */
static int cairo_set_source_rgb_l( lua_State* L )
{
  lua_cairo_t* lc = lua_cairo_check( L, 1 );

  cairo_set_source_rgb( lc->cairo,
                        luaL_checknumber( L, 2 ),   /* red */
                        luaL_checknumber( L, 3 ),   /* green */
                        luaL_checknumber( L, 4 ) ); /* blue */

  return( 0 );
}

/**
 * 
 */
static int cairo_set_source_rgba_l( lua_State* L )
{
  lua_cairo_t* lc = lua_cairo_check( L, 1 );

  cairo_set_source_rgba( lc->cairo,
                         luaL_checknumber( L, 2 ),   /* red */
                         luaL_checknumber( L, 3 ),   /* green */
                         luaL_checknumber( L, 4 ),   /* blue */
                         luaL_checknumber( L, 5 ) ); /* alpha */

  return( 0 );
}

/**
 * 
 */
static int cairo_set_source_l( lua_State* L )
{
  lua_cairo_t* lc = lua_cairo_check( L, 1 );
  lua_cairo_pattern_t* lcp = lua_cairo_pattern_check( L, 2 );

  cairo_set_source( lc->cairo, lcp->pattern );

  return( 0 );
}

/**
 * 
 */
static int cairo_set_source_surface_l( lua_State* L )
{
  lua_cairo_t* lc = lua_cairo_check( L, 1 );
  lua_cairo_surface_t* lcs = lua_cairo_surface_check( L, 2 );

  cairo_set_source_surface( lc->cairo, lcs->surface, luaL_optnumber( L, 3, 0 ), luaL_optnumber( L, 4, 0 ) );

  return( 0 );
}

/**
 * 
 */
static int cairo_get_source_l( lua_State* L )
{
  lua_cairo_t* lc = lua_cairo_check( L, 1 );

  lua_cairo_pattern_t* lcp = (lua_cairo_pattern_t*)lua_newuserdata( L, sizeof( lua_cairo_pattern_t ) );
  memset( lcp, 0, sizeof( lua_cairo_pattern_t ) );

  luaL_getmetatable( L, "lua_cairo_pattern_t" );
  lua_setmetatable( L, -2 );

  lcp->pattern = cairo_get_source( lc->cairo );

  return( 1 );
}

/**
 * 
 */
static int cairo_set_antialias_l( lua_State* L )
{
  lua_cairo_t* lc = lua_cairo_check( L, 1 );

  cairo_set_antialias( lc->cairo, luaL_checkoption( L, 2, "default", cairo_antialias_lst ) );

  return( 0 );
}

/**
 * 
 */
static int cairo_get_antialias_l( lua_State* L )
{
  lua_cairo_t* lc = lua_cairo_check( L, 1 );

  lua_pushstring( L, cairo_antialias_lst[cairo_get_antialias( lc->cairo )] );

  return( 1 );
}

/**
 * 
 */
static int cairo_set_dash_l( lua_State* L )
{
  int num_dashes = 0;
  double dashes[64] = {0};
  lua_cairo_t* lc = lua_cairo_check( L, 1 );

  while ( num_dashes < 64 ) {
    if ( 0 > ( dashes[num_dashes] = luaL_optnumber( L, 2 + num_dashes, -1 ) ) ) {
      break;
    }

    num_dashes++;
  }

  cairo_set_dash( lc->cairo, dashes, num_dashes, 0 );

  return( 0 );
}

/**
 * 
 */
static int cairo_get_dash_count_l( lua_State* L )
{
  lua_cairo_t* lc = lua_cairo_check( L, 1 );

  lua_pushinteger( L, cairo_get_dash_count( lc->cairo ) );

  return( 1 );
}

/**
 * 
 */
static int cairo_get_dash_l( lua_State* L )
{
  int index = 0;
  double offset = 0;
  double dashes[64] = {0};
  lua_cairo_t* lc = lua_cairo_check( L, 1 );
  int count = cairo_get_dash_count( lc->cairo );

  if ( 64 < count ) {
    luaL_error( L, "cairo_get_dash_count() returned a value (%d) greater than 64", count );
  }

  if ( lua_checkstack( L, count ) ) {
    luaL_error( L, "lua_checkstack( L, %d ) failed", count );
  }

  cairo_get_dash( lc->cairo, dashes, &offset );

  for ( index = 0; index < count; index++ ) {
    lua_pushnumber( L, dashes[index] );
  }

  return( count );
}

/**
 * 
 */
static int cairo_set_line_cap_l( lua_State* L )
{
  lua_cairo_t* lc = lua_cairo_check( L, 1 );

  cairo_set_line_cap( lc->cairo, luaL_checkoption( L, 2, "butt", cairo_line_cap_lst ) );

  return( 0 );
}

/**
 * 
 */
static int cairo_get_line_cap_l( lua_State* L )
{
  lua_cairo_t* lc = lua_cairo_check( L, 1 );

  lua_pushstring( L, cairo_line_cap_lst[cairo_get_line_cap( lc->cairo )] );

  return( 1 );
}

/**
 * 
 */
static int cairo_set_line_join_l( lua_State* L )
{
  lua_cairo_t* lc = lua_cairo_check( L, 1 );

  cairo_set_line_join( lc->cairo, luaL_checkoption( L, 2, "miter", cairo_line_join_lst ) );

  return( 0 );
}

/**
 * 
 */
static int cairo_get_line_join_l( lua_State* L )
{
  lua_cairo_t* lc = lua_cairo_check( L, 1 );

  lua_pushstring( L, cairo_line_join_lst[cairo_get_line_join( lc->cairo )] );

  return( 1 );
}

/**
 * 
 */
static int cairo_set_line_width_l( lua_State* L )
{
  lua_cairo_t* lc = lua_cairo_check( L, 1 );

  cairo_set_line_width( lc->cairo,
                        luaL_checknumber( L, 2 ) ); /* width */

  return( 0 );
}

/**
 * 
 */
static int cairo_get_line_width_l( lua_State* L )
{
  lua_cairo_t* lc = lua_cairo_check( L, 1 );

  lua_pushnumber( L, cairo_get_line_width( lc->cairo ) );

  return( 1 );
}

/**
 * 
 */
static int cairo_set_miter_limit_l( lua_State* L )
{
  lua_cairo_t* lc = lua_cairo_check( L, 1 );

  cairo_set_miter_limit( lc->cairo,
                         luaL_checknumber( L, 2 ) ); /* limit */

  return( 0 );
}

/**
 * 
 */
static int cairo_get_miter_limit_l( lua_State* L )
{
  lua_cairo_t* lc = lua_cairo_check( L, 1 );

  lua_pushnumber( L, cairo_get_miter_limit( lc->cairo ) );

  return( 1 );
}

/**
 * 
 */
static int cairo_set_operator_l( lua_State* L )
{
  lua_cairo_t* lc = lua_cairo_check( L, 1 );

  cairo_set_operator( lc->cairo, luaL_checkoption( L, 2, "over", cairo_operator_lst ) );

  return( 0 );
}

/**
 * 
 */
static int cairo_get_operator_l( lua_State* L )
{
  lua_cairo_t* lc = lua_cairo_check( L, 1 );

  lua_pushstring( L, cairo_operator_lst[cairo_get_operator( lc->cairo )] );

  return( 1 );
}

/**
 * 
 */
static int cairo_clip_l( lua_State* L )
{
  lua_cairo_t* lc = lua_cairo_check( L, 1 );

  cairo_clip( lc->cairo );

  return( 0 );
}

/**
 * 
 */
static int cairo_clip_preserve_l( lua_State* L )
{
  lua_cairo_t* lc = lua_cairo_check( L, 1 );

  cairo_clip_preserve( lc->cairo );

  return( 0 );
}

/**
 * 
 */
static int cairo_clip_extents_l( lua_State* L )
{
  double x1 = 0.0;
  double y1 = 0.0;
  double x2 = 0.0;
  double y2 = 0.0;
  lua_cairo_t* lc = lua_cairo_check( L, 1 );

  cairo_clip_extents( lc->cairo, &x1, &y1, &x2, &y2 );

  lua_pushnumber( L, x1 );
  lua_pushnumber( L, y1 );
  lua_pushnumber( L, x2 );
  lua_pushnumber( L, y2 );

  return( 4 );
}

/**
 * 
 */
static int cairo_in_clip_l( lua_State* L )
{
  lua_cairo_t* lc = lua_cairo_check( L, 1 );

  lua_pushboolean( L, cairo_in_clip( lc->cairo,
                                     luaL_checknumber( L, 2 ),     /* x */
                                     luaL_checknumber( L, 3 ) ) ); /* y */

  return( 1 );
}

/**
 * 
 */
static int cairo_reset_clip_l( lua_State* L )
{
  lua_cairo_t* lc = lua_cairo_check( L, 1 );

  cairo_reset_clip( lc->cairo );

  return( 0 );
}

/**
 * 
 */
static int cairo_fill_l( lua_State* L )
{
  lua_cairo_t* lc = lua_cairo_check( L, 1 );

  cairo_fill( lc->cairo );

  return( 0 );
}

/**
 * 
 */
static int cairo_fill_preserve_l( lua_State* L )
{
  lua_cairo_t* lc = lua_cairo_check( L, 1 );

  cairo_fill_preserve( lc->cairo );

  return( 0 );
}

/**
 * 
 */
static int cairo_fill_extents_l( lua_State* L )
{
  double x1 = 0.0;
  double y1 = 0.0;
  double x2 = 0.0;
  double y2 = 0.0;
  lua_cairo_t* lc = lua_cairo_check( L, 1 );

  cairo_fill_extents( lc->cairo, &x1, &y1, &x2, &y2 );

  lua_pushnumber( L, x1 );
  lua_pushnumber( L, y1 );
  lua_pushnumber( L, x2 );
  lua_pushnumber( L, y2 );

  return( 4 );
}

/**
 * 
 */
static int cairo_in_fill_l( lua_State* L )
{
  lua_cairo_t* lc = lua_cairo_check( L, 1 );

  lua_pushboolean( L, cairo_in_fill( lc->cairo,
                                     luaL_checknumber( L, 2 ),     /* x */
                                     luaL_checknumber( L, 3 ) ) ); /* y */

  return( 1 );
}

/**
 * 
 */
static int cairo_mask_l( lua_State* L )
{
  lua_cairo_t* lc = lua_cairo_check( L, 1 );
  lua_cairo_pattern_t* lcp = lua_cairo_pattern_check( L, 2 );

  cairo_mask( lc->cairo, lcp->pattern );

  return( 0 );
}

/**
 * 
 */
static int cairo_mask_surface_l( lua_State* L )
{
  lua_cairo_t* lc = lua_cairo_check( L, 1 );
  lua_cairo_surface_t* lcs = lua_cairo_surface_check( L, 2 );

  cairo_mask_surface( lc->cairo,
                      lcs->surface,               /* surface */
                      luaL_checknumber( L, 3 ),   /* x */
                      luaL_checknumber( L, 4 ) ); /* y */

  return( 0 );
}

/**
 * 
 */
static int cairo_paint_l( lua_State* L )
{
  lua_cairo_t* lc = lua_cairo_check( L, 1 );

  cairo_paint( lc->cairo );

  return( 0 );
}

/**
 * 
 */
static int cairo_paint_with_alpha_l( lua_State* L )
{
  lua_cairo_t* lc = lua_cairo_check( L, 1 );

  cairo_paint_with_alpha( lc->cairo,
                          luaL_checknumber( L, 2 ) ); /* alpha */

  return( 0 );
}

/**
 * 
 */
static int cairo_stroke_l( lua_State* L )
{
  lua_cairo_t* lc = lua_cairo_check( L, 1 );

  cairo_stroke( lc->cairo );

  return( 0 );
}

/**
 * 
 */
static int cairo_stroke_preserve_l( lua_State* L )
{
  lua_cairo_t* lc = lua_cairo_check( L, 1 );

  cairo_stroke_preserve( lc->cairo );

  return( 0 );
}

/**
 * 
 */
static int cairo_stroke_extents_l( lua_State* L )
{
  double x1 = 0.0;
  double y1 = 0.0;
  double x2 = 0.0;
  double y2 = 0.0;
  lua_cairo_t* lc = lua_cairo_check( L, 1 );

  cairo_stroke_extents( lc->cairo, &x1, &y1, &x2, &y2 );

  lua_pushnumber( L, x1 );
  lua_pushnumber( L, y1 );
  lua_pushnumber( L, x2 );
  lua_pushnumber( L, y2 );

  return( 4 );
}

/**
 * 
 */
static int cairo_in_stroke_l( lua_State* L )
{
  lua_cairo_t* lc = lua_cairo_check( L, 1 );

  lua_pushboolean( L, cairo_in_stroke( lc->cairo,
                                       luaL_checknumber( L, 2 ),     /* x */
                                       luaL_checknumber( L, 3 ) ) ); /* y */

  return( 1 );
}

/**
 * 
 */
static int cairo_new_path_l( lua_State* L )
{
  lua_cairo_t* lc = lua_cairo_check( L, 1 );

  cairo_new_path( lc->cairo );

  return( 0 );
}

/**
 * 
 */
static int cairo_new_sub_path_l( lua_State* L )
{
  lua_cairo_t* lc = lua_cairo_check( L, 1 );

  cairo_new_sub_path( lc->cairo );

  return( 0 );
}

/**
 * 
 */
static int cairo_close_path_l( lua_State* L )
{
  lua_cairo_t* lc = lua_cairo_check( L, 1 );

  cairo_close_path( lc->cairo );

  return( 0 );
}

/**
 * 
 */
static int cairo_arc_l( lua_State* L )
{
  lua_cairo_t* lc = lua_cairo_check( L, 1 );

  cairo_arc( lc->cairo,
             luaL_checknumber( L, 2 ),   /* xc */
             luaL_checknumber( L, 3 ),   /* yc */
             luaL_checknumber( L, 4 ),   /* radius */
             luaL_checknumber( L, 5 ),   /* angle1 */
             luaL_checknumber( L, 6 ) ); /* angle2 */

  return( 0 );
}

/**
 * 
 */
static int cairo_arc_negative_l( lua_State* L )
{
  lua_cairo_t* lc = lua_cairo_check( L, 1 );

  cairo_arc_negative( lc->cairo,
                      luaL_checknumber( L, 2 ),   /* xc */
                      luaL_checknumber( L, 3 ),   /* yc */
                      luaL_checknumber( L, 4 ),   /* radius */
                      luaL_checknumber( L, 5 ),   /* angle1 */
                      luaL_checknumber( L, 6 ) ); /* angle2 */

  return( 0 );
}

/**
 * 
 */
static int cairo_curve_to_l( lua_State* L )
{
  lua_cairo_t* lc = lua_cairo_check( L, 1 );

  cairo_curve_to( lc->cairo,
                  luaL_checknumber( L, 2 ),   /* x1 */
                  luaL_checknumber( L, 3 ),   /* y1 */
                  luaL_checknumber( L, 4 ),   /* x2 */
                  luaL_checknumber( L, 5 ),   /* y2 */
                  luaL_checknumber( L, 6 ),   /* x3 */
                  luaL_checknumber( L, 7 ) ); /* y3 */

  return( 0 );
}

/**
 * 
 */
static int cairo_line_to_l( lua_State* L )
{
  lua_cairo_t* lc = lua_cairo_check( L, 1 );

  cairo_line_to( lc->cairo,
                 luaL_checknumber( L, 2 ),   /* x */
                 luaL_checknumber( L, 3 ) ); /* y */

  return( 0 );
}

/**
 * 
 */
static int cairo_move_to_l( lua_State* L )
{
  lua_cairo_t* lc = lua_cairo_check( L, 1 );

  cairo_move_to( lc->cairo,
                 luaL_checknumber( L, 2 ),   /* x */
                 luaL_checknumber( L, 3 ) ); /* y */

  return( 0 );
}

/**
 * 
 */
static int cairo_rectangle_l( lua_State* L )
{
  lua_cairo_t* lc = lua_cairo_check( L, 1 );

  cairo_rectangle( lc->cairo,
                   luaL_checknumber( L, 2 ),   /* x */
                   luaL_checknumber( L, 3 ),   /* y */
                   luaL_checknumber( L, 4 ),   /* width */
                   luaL_checknumber( L, 5 ) ); /* height */

  return( 0 );
}

/**
 * 
 */
static int cairo_text_path_l( lua_State* L )
{
  lua_cairo_t* lc = lua_cairo_check( L, 1 );

  cairo_text_path( lc->cairo,
                   luaL_checkstring( L, 2 ) ); /* utf8 */

  return( 0 );
}

/**
 * 
 */
static int cairo_rel_curve_to_l( lua_State* L )
{
  lua_cairo_t* lc = lua_cairo_check( L, 1 );

  cairo_rel_curve_to( lc->cairo,
                      luaL_checknumber( L, 2 ),   /* dx1 */
                      luaL_checknumber( L, 3 ),   /* dy1 */
                      luaL_checknumber( L, 4 ),   /* dx2 */
                      luaL_checknumber( L, 5 ),   /* dy2 */
                      luaL_checknumber( L, 6 ),   /* dx3 */
                      luaL_checknumber( L, 7 ) ); /* dy3 */

  return( 0 );
}

/**
 * 
 */
static int cairo_rel_line_to_l( lua_State* L )
{
  lua_cairo_t* lc = lua_cairo_check( L, 1 );

  cairo_rel_line_to( lc->cairo,
                     luaL_checknumber( L, 2 ),   /* dx */
                     luaL_checknumber( L, 3 ) ); /* dy */

  return( 0 );
}

/**
 * 
 */
static int cairo_rel_move_to_l( lua_State* L )
{
  lua_cairo_t* lc = lua_cairo_check( L, 1 );

  cairo_rel_move_to( lc->cairo,
                     luaL_checknumber( L, 2 ),   /* dx */
                     luaL_checknumber( L, 3 ) ); /* dy */

  return( 0 );
}

/**
 * 
 */
static int cairo_path_extents_l( lua_State* L )
{
  double x1 = 0.0;
  double y1 = 0.0;
  double x2 = 0.0;
  double y2 = 0.0;
  lua_cairo_t* lc = lua_cairo_check( L, 1 );

  cairo_path_extents( lc->cairo, &x1, &y1, &x2, &y2 );

  lua_pushnumber( L, x1 );
  lua_pushnumber( L, y1 );
  lua_pushnumber( L, x2 );
  lua_pushnumber( L, y2 );

  return( 4 );
}

/**
 * 
 */
static int cairo_set_font_size_l( lua_State* L )
{
  lua_cairo_t* lc = lua_cairo_check( L, 1 );

  cairo_set_font_size( lc->cairo,
                       luaL_checknumber( L, 2 ) ); /* size */

  return( 0 );
}

/**
 * 
 */
static int cairo_set_font_options_l( lua_State* L )
{
  lua_cairo_t* lc = lua_cairo_check( L, 1 );

  return( 0 );
}

/**
 * 
 */
static int cairo_get_font_options_l( lua_State* L )
{
  lua_cairo_t* lc = lua_cairo_check( L, 1 );

  return( 0 );
}

/**
 * 
 */
static int cairo_set_font_face_l( lua_State* L )
{
  lua_cairo_t* lc = lua_cairo_check( L, 1 );
  lua_cairo_font_face_t* lcff = lua_cairo_font_face_check( L, 2 );

  cairo_set_font_face( lc->cairo, lcff->crface );

  return( 0 );
}

/**
 * 
 */
static int cairo_show_text_l( lua_State* L )
{
  size_t length = 0;
  char restore = 0;
  lua_cairo_t* lc = lua_cairo_check( L, 1 );
  const char* text = luaL_checklstring( L, 2, &length );
  lua_Integer start = luaL_optinteger( L, 3, 1 );
  lua_Integer end = luaL_optinteger( L, 4, -1 );

  start = ( start >= 0 ) ? start : (lua_Integer)length + start + 1;
  end = ( end >= 0 ) ? end : (lua_Integer)length + end + 1;

  if ( start < 1 ) {
    start = 1;
  }

  if ( end > (lua_Integer)length ) {
    end = (lua_Integer)length;
  }

  if ( start <= end ) {
    restore = text[end];
    ((char*)text)[end] = 0;
    text += (start - 1);
    cairo_show_text( lc->cairo, text );
    text -= (start - 1);
    ((char*)text)[end] = restore;
  }

  return( 0 );
}

/**
 * 
 */
static int cairo_font_extents_l( lua_State* L )
{
  cairo_font_extents_t extents = {0};
  lua_cairo_t* lc = lua_cairo_check( L, 1 );

  cairo_font_extents( lc->cairo, &extents );

  lua_pushnumber( L, extents.ascent );
  lua_pushnumber( L, extents.descent );
  lua_pushnumber( L, extents.height );
  lua_pushnumber( L, extents.max_x_advance );
  lua_pushnumber( L, extents.max_y_advance );

  return( 5 );
}

/**
 * 
 */
static int cairo_text_extents_l( lua_State* L )
{
  size_t length = 0;
  char restore = 0;
  cairo_text_extents_t extents = {0};
  lua_cairo_t* lc = lua_cairo_check( L, 1 );
  const char* text = luaL_checklstring( L, 2, &length );
  lua_Integer start = luaL_optinteger( L, 3, 1 );
  lua_Integer end = luaL_optinteger( L, 4, -1 );

  start = ( start >= 0 ) ? start : (lua_Integer)length + start + 1;
  end = ( end >= 0 ) ? end : (lua_Integer)length + end + 1;

  if ( start < 1 ) {
    start = 1;
  }

  if ( end > (lua_Integer)length ) {
    end = (lua_Integer)length;
  }

  if ( start <= end ) {
    restore = text[end];
    ((char*)text)[end] = 0;
    text += (start - 1);
    cairo_text_extents( lc->cairo, text, &extents );
    text -= (start - 1);
    ((char*)text)[end] = restore;
  }

  lua_pushnumber( L, extents.x_bearing );
  lua_pushnumber( L, extents.y_bearing );
  lua_pushnumber( L, extents.width );
  lua_pushnumber( L, extents.height );
  lua_pushnumber( L, extents.x_advance );
  lua_pushnumber( L, extents.y_advance );

  return( 6 );
}

/**
 * 
 */
static int cairo_translate_l( lua_State* L )
{
  lua_cairo_t* lc = lua_cairo_check( L, 1 );

  cairo_translate( lc->cairo,
                   luaL_checknumber( L, 2 ),   /* tx */
                   luaL_checknumber( L, 3 ) ); /* ty */

  return( 0 );
}

/**
 * 
 */
static int cairo_scale_l( lua_State* L )
{
  lua_cairo_t* lc = lua_cairo_check( L, 1 );

  cairo_scale( lc->cairo,
               luaL_checknumber( L, 2 ),   /* sx */
               luaL_checknumber( L, 3 ) ); /* sy */

  return( 0 );
}

/**
 * 
 */
static int cairo_rotate_l( lua_State* L )
{
  lua_cairo_t* lc = lua_cairo_check( L, 1 );

  cairo_rotate( lc->cairo,
                luaL_checknumber( L, 2 ) ); /* angle */

  return( 0 );
}

/**
 * 
 */
static int cairo_identity_matrix_l( lua_State* L )
{
  lua_cairo_t* lc = lua_cairo_check( L, 1 );

  cairo_identity_matrix( lc->cairo );

  return( 0 );
}


static int cairo_image_surface_create_l( lua_State* L );
static int cairo_image_surface_create_from_png_l( lua_State* L );
static int cairo_surface__gc_l( lua_State* L );
static int cairo_surface_destroy_l( lua_State* L );
static int cairo_surface_get_size_l( lua_State* L );
static int cairo_surface_flush_L( lua_State* L );

static int cairo_surface_get_data_L( lua_State* L ) {
  lua_cairo_surface_t* lcs = lua_cairo_surface_check( L, 1 );
  lua_pushlightuserdata(L, cairo_image_surface_get_data(lcs->surface));
  lua_pushnumber(L, cairo_image_surface_get_width(lcs->surface));
  lua_pushnumber(L, cairo_image_surface_get_height(lcs->surface));
  lua_pushnumber(L, cairo_image_surface_get_stride(lcs->surface));
  return 4;
}

/**
 * 
 */
int luaopen_cairo_surface( lua_State* L )
{
  static const luaL_reg methods[] = {
    {"__gc", cairo_surface__gc_l},
    {"destroy", cairo_surface_destroy_l},
    {"get_size", cairo_surface_get_size_l},
    {"get_data", cairo_surface_get_data_L},
    {"flush", cairo_surface_flush_L},
    {0, 0}
  };

  static const luaL_reg surface[] = {
    {"create", cairo_image_surface_create_l},
    {"create_from_png", cairo_image_surface_create_from_png_l},
    {0, 0}
  };

  luaL_newmetatable( L, "lua_cairo_surface_t" );
  lua_pushvalue( L, -1 ); /* duplicate the metatable */
  lua_setfield( L, -2, "__index" ); /* set the metamethod to the metatable */

  luaL_register( L, 0, methods ); /* pack the methods in the metatable */
  lua_pop( L, 1 );

  lua_pushliteral( L, "surface" ); /* cairo.surface */
  lua_newtable( L );
  luaL_register( L, 0, surface );
  lua_settable( L, -3 );

  return( 1 );
}

/**
 * 
 */
lua_cairo_surface_t* lua_cairo_surface_check( lua_State* L, int narg )
{
  lua_cairo_surface_t* lcs = (lua_cairo_surface_t*)luaL_checkudata( L, narg, "lua_cairo_surface_t" );

  if ( !lcs->surface ) {
    luaL_argerror( L, 1, "cairo surface has been destroyed" );
  }

  return( lcs );
}

/**
 * 
 */
static int cairo_image_surface_create_l( lua_State* L )
{
  int w = luaL_checkint( L, 1 );
  int h = luaL_checkint( L, 2 );

  lua_cairo_surface_t* lcs = (lua_cairo_surface_t*)lua_newuserdata( L, sizeof( lua_cairo_surface_t ) );
  memset( lcs, 0, sizeof( lua_cairo_surface_t ) );

  luaL_getmetatable( L, "lua_cairo_surface_t" );
  lua_setmetatable( L, -2 );

  if ( !( lcs->surface = cairo_image_surface_create( CAIRO_FORMAT_ARGB32, w, h ) ) ) {
    luaL_error( L, "cairo_image_surface_create() failed" );
  }

  lcs->w = cairo_image_surface_get_width( lcs->surface );
  lcs->h = cairo_image_surface_get_height( lcs->surface );
  lcs->data = cairo_image_surface_get_data( lcs->surface );

  return( 1 );
}

/**
 * 
 */
static int cairo_image_surface_create_from_png_l( lua_State* L )
{
  const char* filename = luaL_checkstring( L, 1 );

  lua_cairo_surface_t* lcs = (lua_cairo_surface_t*)lua_newuserdata( L, sizeof( lua_cairo_surface_t ) );
  memset( lcs, 0, sizeof( lua_cairo_surface_t ) );

  luaL_getmetatable( L, "lua_cairo_surface_t" );
  lua_setmetatable( L, -2 );

  if ( !( lcs->surface = cairo_image_surface_create_from_png( filename ) ) ) {
    luaL_error( L, "cairo_image_surface_create_from_png() failed" );
  }

  lcs->w = cairo_image_surface_get_width( lcs->surface );
  lcs->h = cairo_image_surface_get_height( lcs->surface );
  lcs->data = cairo_image_surface_get_data( lcs->surface );

  return( 1 );
}

/**
 * 
 */
static int cairo_surface__gc_l( lua_State* L )
{
  lua_cairo_surface_t* lcs = (lua_cairo_surface_t*)lua_touserdata( L, 1 );

  if ( lcs->surface ) {
    cairo_surface_destroy( lcs->surface );
    lcs->surface = 0;
  }

  return( 0 );
}

/**
 * 
 */
static int cairo_surface_destroy_l( lua_State* L )
{
  lua_cairo_surface_t* lcs = lua_cairo_surface_check( L, 1 );

  cairo_surface_destroy( lcs->surface );
  lcs->surface = 0;

  return( 0 );
}

/**
 * 
 */
static int cairo_surface_get_size_l( lua_State* L )
{
  lua_cairo_surface_t* lcs = lua_cairo_surface_check( L, 1 );

  lua_pushinteger( L, lcs->w );
  lua_pushinteger( L, lcs->h );

  return( 2 );
}




/**
 * 
 */
static int cairo_surface_flush_L( lua_State* L )
{
  lua_cairo_surface_t* lcs = lua_cairo_surface_check( L, 1 );

  cairo_surface_flush(lcs->surface);

  return( 0 );
}

static int cairo_pattern_create_rgb_l( lua_State* L );
static int cairo_pattern_create_rgba_l( lua_State* L );
static int cairo_pattern_create_for_surface_l( lua_State* L );
static int cairo_pattern_create_linear_l( lua_State* L );
static int cairo_pattern_create_radial_l( lua_State* L );
static int cairo_pattern__gc_l( lua_State* L );
static int cairo_pattern_destroy_l( lua_State* L );
static int cairo_pattern_get_rgba_l( lua_State* L );
static int cairo_pattern_get_linear_points_l( lua_State* L );
static int cairo_pattern_get_radial_circles_l( lua_State* L );
static int cairo_pattern_add_color_stop_rgb_l( lua_State* L );
static int cairo_pattern_add_color_stop_rgba_l( lua_State* L );
static int cairo_pattern_get_color_stop_count_l( lua_State* L );
static int cairo_pattern_get_color_stop_rgba_l( lua_State* L );

/**
 * 
 */
int luaopen_cairo_pattern( lua_State* L )
{
  static const luaL_reg methods[] = {
    {"__gc", cairo_pattern__gc_l},
    {"destroy", cairo_pattern_destroy_l},
    {"get_rgba", cairo_pattern_get_rgba_l},
    {"get_linear_points", cairo_pattern_get_linear_points_l},
    {"get_radial_circles", cairo_pattern_get_radial_circles_l},
    {"add_color_stop_rgb", cairo_pattern_add_color_stop_rgb_l},
    {"add_color_stop_rgba", cairo_pattern_add_color_stop_rgba_l},
    {"get_color_stop_count", cairo_pattern_get_color_stop_count_l},
    {"get_color_stop_rgba", cairo_pattern_get_color_stop_rgba_l},
    {0, 0}
  };

  static const luaL_reg pattern[] = {
    {"create_rgb", cairo_pattern_create_rgb_l},
    {"create_rgba", cairo_pattern_create_rgba_l},
    {"create_for_surface", cairo_pattern_create_for_surface_l},
    {"create_linear", cairo_pattern_create_linear_l},
    {"create_radial", cairo_pattern_create_radial_l},
    {0, 0}
  };

  luaL_newmetatable( L, "lua_cairo_pattern_t" );
  lua_pushvalue( L, -1 ); /* duplicate the metatable */
  lua_setfield( L, -2, "__index" ); /* set the metamethod to the metatable */

  luaL_register( L, 0, methods ); /* pack the methods in the metatable */
  lua_pop( L, 1 );

  lua_pushliteral( L, "pattern" ); /* cairo.pattern */
  lua_newtable( L );
  luaL_register( L, 0, pattern );
  lua_settable( L, -3 );

  return( 1 );
}

/**
 * 
 */
lua_cairo_pattern_t* lua_cairo_pattern_check( lua_State* L, int narg )
{
  lua_cairo_pattern_t* lcp = (lua_cairo_pattern_t*)luaL_checkudata( L, narg, "lua_cairo_pattern_t" );

  if ( !lcp->pattern ) {
    luaL_argerror( L, 1, "cairo pattern has been destroyed" );
  }

  return( lcp );
}

/**
 * 
 */
static int cairo_pattern_create_rgb_l( lua_State* L )
{
  double red = luaL_checknumber( L, 1 );
  double green = luaL_checknumber( L, 2 );
  double blue = luaL_checknumber( L, 3 );

  lua_cairo_pattern_t* lcp = (lua_cairo_pattern_t*)lua_newuserdata( L, sizeof( lua_cairo_pattern_t ) );
  memset( lcp, 0, sizeof( lua_cairo_pattern_t ) );

  luaL_getmetatable( L, "lua_cairo_pattern_t" );
  lua_setmetatable( L, -2 );

  lcp->pattern = cairo_pattern_create_rgb( red, green, blue );

  return( 1 );
}

/**
 * 
 */
static int cairo_pattern_create_rgba_l( lua_State* L )
{
  double red = luaL_checknumber( L, 1 );
  double green = luaL_checknumber( L, 2 );
  double blue = luaL_checknumber( L, 3 );
  double alpha = luaL_checknumber( L, 4 );

  lua_cairo_pattern_t* lcp = (lua_cairo_pattern_t*)lua_newuserdata( L, sizeof( lua_cairo_pattern_t ) );
  memset( lcp, 0, sizeof( lua_cairo_pattern_t ) );

  luaL_getmetatable( L, "lua_cairo_pattern_t" );
  lua_setmetatable( L, -2 );

  lcp->pattern = cairo_pattern_create_rgba( red, green, blue, alpha );

  return( 1 );
}

/**
 * 
 */
static int cairo_pattern_create_for_surface_l( lua_State* L )
{
  lua_cairo_surface_t* lcs = lua_cairo_surface_check( L, 1 );

  lua_cairo_pattern_t* lcp = (lua_cairo_pattern_t*)lua_newuserdata( L, sizeof( lua_cairo_pattern_t ) );
  memset( lcp, 0, sizeof( lua_cairo_pattern_t ) );

  luaL_getmetatable( L, "lua_cairo_pattern_t" );
  lua_setmetatable( L, -2 );

  lcp->pattern = cairo_pattern_create_for_surface( lcs->surface );

  return( 1 );
}

/**
 * 
 */
static int cairo_pattern_create_linear_l( lua_State* L )
{
  double x0 = luaL_checknumber( L, 1 );
  double y0 = luaL_checknumber( L, 2 );
  double x1 = luaL_checknumber( L, 3 );
  double y1 = luaL_checknumber( L, 4 );

  lua_cairo_pattern_t* lcp = (lua_cairo_pattern_t*)lua_newuserdata( L, sizeof( lua_cairo_pattern_t ) );
  memset( lcp, 0, sizeof( lua_cairo_pattern_t ) );

  luaL_getmetatable( L, "lua_cairo_pattern_t" );
  lua_setmetatable( L, -2 );

  lcp->pattern = cairo_pattern_create_linear( x0, y0, x1, y1 );

  return( 1 );
}

/**
 * 
 */
static int cairo_pattern_create_radial_l( lua_State* L )
{
  double cx0 = luaL_checknumber( L, 1 );
  double cy0 = luaL_checknumber( L, 2 );
  double radius0 = luaL_checknumber( L, 3 );
  double cx1 = luaL_checknumber( L, 4 );
  double cy1 = luaL_checknumber( L, 5 );
  double radius1 = luaL_checknumber( L, 6 );

  lua_cairo_pattern_t* lcp = (lua_cairo_pattern_t*)lua_newuserdata( L, sizeof( lua_cairo_pattern_t ) );
  memset( lcp, 0, sizeof( lua_cairo_pattern_t ) );

  luaL_getmetatable( L, "lua_cairo_pattern_t" );
  lua_setmetatable( L, -2 );

  lcp->pattern = cairo_pattern_create_radial( cx0, cy0, radius0, cx1, cy1, radius1 );

  return( 1 );
}

/**
 * 
 */
static int cairo_pattern__gc_l( lua_State* L )
{
  lua_cairo_pattern_t* lcp = (lua_cairo_pattern_t*)lua_touserdata( L, 1 );

  if ( lcp->pattern ) {
    cairo_pattern_destroy( lcp->pattern );
    lcp->pattern = 0;
  }

  return( 0 );
}

/**
 * 
 */
static int cairo_pattern_destroy_l( lua_State* L )
{
  lua_cairo_pattern_t* lcp = lua_cairo_pattern_check( L, 1 );

  cairo_pattern_destroy( lcp->pattern );
  lcp->pattern = 0;

  return( 0 );
}

/**
 * 
 */
static int cairo_pattern_get_rgba_l( lua_State* L )
{
  double red = 0.0;
  double green = 0.0;
  double blue = 0.0;
  double alpha = 0.0;
  lua_cairo_pattern_t* lcp = lua_cairo_pattern_check( L, 1 );

  if ( cairo_pattern_get_rgba( lcp->pattern, &red, &green, &blue, &alpha ) ) {
    luaL_argerror( L, 1, "pattern is not a solid color pattern" );
  }

  lua_pushnumber( L, red );
  lua_pushnumber( L, green );
  lua_pushnumber( L, blue );
  lua_pushnumber( L, alpha );

  return( 4 );
}

/**
 * 
 */
static int cairo_pattern_get_linear_points_l( lua_State* L )
{
  double x0 = 0.0;
  double y0 = 0.0;
  double x1 = 0.0;
  double y1 = 0.0;
  lua_cairo_pattern_t* lcp = lua_cairo_pattern_check( L, 1 );

  if ( cairo_pattern_get_linear_points( lcp->pattern, &x0, &y0, &x1, &y1 ) ) {
    luaL_argerror( L, 1, "pattern is not a linear gradient pattern" );
  }

  lua_pushnumber( L, x0 );
  lua_pushnumber( L, y0 );
  lua_pushnumber( L, x1 );
  lua_pushnumber( L, y1 );

  return( 4 );
}

/**
 * 
 */
static int cairo_pattern_get_radial_circles_l( lua_State* L )
{
  double x0 = 0.0;
  double y0 = 0.0;
  double r0 = 0.0;
  double x1 = 0.0;
  double y1 = 0.0;
  double r1 = 0.0;
  lua_cairo_pattern_t* lcp = lua_cairo_pattern_check( L, 1 );

  if ( cairo_pattern_get_radial_circles( lcp->pattern, &x0, &y0, &r0, &x1, &y1, &r1 ) ) {
    luaL_argerror( L, 1, "pattern is not a radial gradient pattern" );
  }

  lua_pushnumber( L, x0 );
  lua_pushnumber( L, y0 );
  lua_pushnumber( L, r0 );
  lua_pushnumber( L, x1 );
  lua_pushnumber( L, y1 );
  lua_pushnumber( L, r1 );

  return( 6 );
}

/**
 * 
 */
static int cairo_pattern_add_color_stop_rgb_l( lua_State* L )
{
  lua_cairo_pattern_t* lcp = lua_cairo_pattern_check( L, 1 );
  double offset = luaL_checknumber( L, 2 );
  double red = luaL_checknumber( L, 3 );
  double green = luaL_checknumber( L, 4 );
  double blue = luaL_checknumber( L, 5 );

  cairo_pattern_add_color_stop_rgb( lcp->pattern, offset, red, green, blue );

  return( 0 );
}

/**
 * 
 */
static int cairo_pattern_add_color_stop_rgba_l( lua_State* L )
{
  lua_cairo_pattern_t* lcp = lua_cairo_pattern_check( L, 1 );
  double offset = luaL_checknumber( L, 2 );
  double red = luaL_checknumber( L, 3 );
  double green = luaL_checknumber( L, 4 );
  double blue = luaL_checknumber( L, 5 );
  double alpha = luaL_checknumber( L, 6 );

  cairo_pattern_add_color_stop_rgba( lcp->pattern, offset, red, green, blue, alpha );

  return( 0 );
}

/**
 * 
 */
static int cairo_pattern_get_color_stop_count_l( lua_State* L )
{
  int count = 0;
  lua_cairo_pattern_t* lcp = lua_cairo_pattern_check( L, 1 );

  if ( cairo_pattern_get_color_stop_count( lcp->pattern, &count ) ) {
    luaL_argerror( L, 1, "pattern is not a gradient pattern" );
  }

  lua_pushinteger( L, count );

  return( 1 );
}

/**
 * 
 */
static int cairo_pattern_get_color_stop_rgba_l( lua_State* L )
{
  cairo_status_t status = CAIRO_STATUS_SUCCESS;
  double offset = 0.0;
  double red = 0.0;
  double green = 0.0;
  double blue = 0.0;
  double alpha = 0.0;
  lua_cairo_pattern_t* lcp = lua_cairo_pattern_check( L, 1 );
  int index = luaL_checkint( L, 2 );

  if ( CAIRO_STATUS_SUCCESS != ( status = cairo_pattern_get_color_stop_rgba( lcp->pattern, index, &offset, &red, &green, &blue, &alpha ) ) ) {
    if ( CAIRO_STATUS_INVALID_INDEX == status ) {
      luaL_argerror( L, 2, "invalid index" );
    }
    else {
      luaL_argerror( L, 1, "pattern is not a gradient pattern" );
    }
  }

  lua_pushnumber( L, offset );
  lua_pushnumber( L, red );
  lua_pushnumber( L, green );
  lua_pushnumber( L, blue );
  lua_pushnumber( L, alpha );

  return( 5 );
}

static int cairo_font_face_create_l( lua_State* L );
static int cairo_font_face__gc_l( lua_State* L );
static int cairo_font_face_destroy_l( lua_State* L );


static FT_Library m_ftlibrary;

/**
 * 
 */
int luaopen_cairo_font( lua_State* L )
{
  static const luaL_reg methods[] = {
    {"__gc", cairo_font_face__gc_l},
    {"destroy", cairo_font_face_destroy_l},
    {0, 0}
  };

  static const luaL_reg font[] = {
    {"create", cairo_font_face_create_l},
    {0, 0}
  };

  if ( FT_Init_FreeType( &m_ftlibrary ) ) {
    luaL_error( L, "FT_Init_FreeType() failed" );
  }

  luaL_newmetatable( L, "lua_cairo_font_face_t" );
  lua_pushvalue( L, -1 ); /* duplicate the metatable */
  lua_setfield( L, -2, "__index" ); /* set the metamethod to the metatable */

  luaL_register( L, 0, methods ); /* pack the methods in the metatable */
  lua_pop( L, 1 );

  lua_pushliteral( L, "font" ); /* cairo.font */
  lua_newtable( L );
  luaL_register( L, 0, font );
  lua_settable( L, -3 );

  return( 1 );
}

/**
 * 
 */
lua_cairo_font_face_t* lua_cairo_font_face_check( lua_State* L, int narg )
{
  lua_cairo_font_face_t* lcff = (lua_cairo_font_face_t*)luaL_checkudata( L, narg, "lua_cairo_font_face_t" );

  if ( !lcff->crface ) {
    luaL_argerror( L, 1, "cairo font face has been destroyed" );
  }

  return( lcff );
}

/**
 * 
 */
static int cairo_font_face_create_l( lua_State* L )
{
  const char* filename = luaL_checkstring( L, 1 );

  lua_cairo_font_face_t* lcff = (lua_cairo_font_face_t*)lua_newuserdata( L, sizeof( lua_cairo_font_face_t ) );
  memset( lcff, 0, sizeof( lua_cairo_font_face_t ) );

  luaL_getmetatable( L, "lua_cairo_font_face_t" );
  lua_setmetatable( L, -2 );

  if ( FT_New_Face( m_ftlibrary, filename, 0, &lcff->ftface ) ) {
    luaL_error( L, "Failed to load font from file %s", filename );
  }

  if ( !( lcff->crface = cairo_ft_font_face_create_for_ft_face( lcff->ftface, 0 ) ) ) {
    luaL_error( L, "cairo_ft_font_face_create_for_ft_face() failed for font %s", filename );
  }

  return( 1 );
}

/**
 * 
 */
static int cairo_font_face__gc_l( lua_State* L )
{
  lua_cairo_font_face_t* lcff = (lua_cairo_font_face_t*)lua_touserdata( L, 1 );

  if ( lcff->crface ) {
    cairo_font_face_destroy( lcff->crface );
    lcff->crface = 0;
    FT_Done_Face( lcff->ftface );
  }

  return( 0 );
}

/**
 * 
 */
static int cairo_font_face_destroy_l( lua_State* L )
{
  lua_cairo_font_face_t* lcff = lua_cairo_font_face_check( L, 1 );

  cairo_font_face_destroy( lcff->crface );
  lcff->crface = 0;
  FT_Done_Face( lcff->ftface );

  return( 0 );
}
