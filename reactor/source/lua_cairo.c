#include <stdlib.h>
#include <debug.h>
#include "gl.h"
#include "reactor_graphics.h"
#include "lua_cairo.h"

char* slant_options[] = {
  "normal",
  "italic",
  "oblique",
  0 
};

char* weight_options[] = {
  "normal",
  "bold",  
  0 
};

char* content_options[] = {
  "color",
  "alpha",
  "color alpha",  
  0
};

char* antialias_options[] = {
  "default",
  "none",
  "gray",
  "subpixel",
  0
};

char* line_cap_options[] = { 
  "butt",
  "round",
  "square",
  0
};

char* line_join_options[] = { 
  "miter",
  "round",
  "bevel",
  0
};

char* operator_options[] = {
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

void checkself_cairo(lua_State* L, reactor_cairo_t** rcr, cairo_t** cr) {
  *rcr = luaL_checkudata(L, 1, "reactor_cairo_t");
  *cr = (*rcr)->cr;
  if (!*cr) {
    luaL_argerror(L, 1, "cairo context is invalid becuase it has been destroyed");
  }
}

static int cairo_create_L(lua_State* L) {    
  reactor_cairo_t* rcr = 0;  
  DBG_ENTER();  
  rcr = lua_newuserdata(L, sizeof(reactor_cairo_t));
  luaL_getmetatable(L, "reactor_cairo_t");
  lua_setmetatable(L, -2);
  rcr->cr = cairo_create(check_cairo_surface(L, 1));      
  DBG_RETURN(1);
}

static int cairo__gc_L(lua_State* L) {
  DBG_ENTER();
  {
    reactor_cairo_t* rcr = lua_touserdata(L, 1); 
    if (rcr->cr)
      cairo_destroy(rcr->cr);
  }
  DBG_RETURN(0);
}

static int cairo_destroy_L(lua_State* L) {    
  reactor_cairo_t* rcr = 0;
  cairo_t* cr = 0;
  DBG_ENTER();
  checkself_cairo(L, &rcr, &cr);
  {
    rcr->cr = 0;
    cairo_destroy(cr);
  }
  DBG_RETURN(0);
}

static int cairo_save_L(lua_State* L) {    
  reactor_cairo_t* rcr = 0;
  cairo_t* cr = 0;
  DBG_ENTER();
  checkself_cairo(L, &rcr, &cr);
  {
    cairo_save(cr);
  }
  DBG_RETURN(0);
}

static int cairo_restore_L(lua_State* L) {    
  reactor_cairo_t* rcr = 0;
  cairo_t* cr = 0;
  DBG_ENTER();
  checkself_cairo(L, &rcr, &cr);
  {
    cairo_restore(cr);
  }
  DBG_RETURN(0);
}

static int cairo_push_group_L(lua_State* L) {    
  reactor_cairo_t* rcr = 0;
  cairo_t* cr = 0;
  DBG_ENTER();
  checkself_cairo(L, &rcr, &cr);
  {
    cairo_push_group(cr);
  }
  DBG_RETURN(0);
}



static int cairo_push_group_with_content_L(lua_State* L) {    
  reactor_cairo_t* rcr = 0;
  cairo_t* cr = 0;
  DBG_ENTER();
  checkself_cairo(L, &rcr, &cr);
  {
    cairo_push_group_with_content(cr, luaL_checkoption(L, 2, "color", content_options));
  }
  DBG_RETURN(0);
}

static int cairo_pop_group_L(lua_State* L) {    
  reactor_cairo_t* rcr = 0;
  cairo_t* cr = 0;
  DBG_ENTER();
  checkself_cairo(L, &rcr, &cr);
  {    
    create_reactor_cairo_pattern(L, cairo_pop_group(cr));
  }
  DBG_RETURN(1);
}

static int cairo_pop_group_to_source_L(lua_State* L) {    
  reactor_cairo_t* rcr = 0;
  cairo_t* cr = 0;
  DBG_ENTER();
  checkself_cairo(L, &rcr, &cr);
  {    
    cairo_pop_group_to_source(cr);
  }
  DBG_RETURN(0);
}

static int cairo_set_source_rgb_L(lua_State* L) {
  reactor_cairo_t* rcr = 0;
  cairo_t* cr = 0;
  DBG_ENTER();
  checkself_cairo(L, &rcr, &cr);
  {
  cairo_set_source_rgb (cr, 
    luaL_checknumber(L, 2),
    luaL_checknumber(L, 3),
    luaL_checknumber(L, 4));
  }
  DBG_RETURN(0);
}

static int cairo_set_source_rgba_L(lua_State* L) {
  reactor_cairo_t* rcr = 0;
  cairo_t* cr = 0;
  DBG_ENTER();
  checkself_cairo(L, &rcr, &cr);
  {
  cairo_set_source_rgba (cr, 
    luaL_checknumber(L, 2),
    luaL_checknumber(L, 3),
    luaL_checknumber(L, 4),
    luaL_checknumber(L, 5));
  }
  DBG_RETURN(0);
}

static int cairo_set_source_L(lua_State* L) {    
  reactor_cairo_t* rcr = 0;
  cairo_t* cr = 0;
  DBG_ENTER();
  checkself_cairo(L, &rcr, &cr);
  {
    cairo_set_source(cr, check_cairo_pattern(L, 2));
  }
  DBG_RETURN(0);
}

static int cairo_set_source_surface_L(lua_State* L) {    
  reactor_cairo_t* rcr = 0;
  cairo_t* cr = 0;
  DBG_ENTER();
  checkself_cairo(L, &rcr, &cr);
  {
    cairo_set_source_surface(cr, check_cairo_surface(L, 2), luaL_optnumber(L, 3, 0), luaL_optnumber(L, 4, 0));
  }
  DBG_RETURN(0);
}



static int cairo_set_antialias_L(lua_State* L) {    
  reactor_cairo_t* rcr = 0;
  cairo_t* cr = 0;
  DBG_ENTER();
  checkself_cairo(L, &rcr, &cr);
  {
    cairo_set_antialias(cr, luaL_checkoption (L, 2, "default", antialias_options));
  }
  DBG_RETURN(0);
}

static int cairo_get_antialias_L(lua_State* L) {    
  reactor_cairo_t* rcr = 0;
  cairo_t* cr = 0;
  DBG_ENTER();
  checkself_cairo(L, &rcr, &cr);
  {    
    lua_pushstring(L, antialias_options[cairo_get_antialias(cr)]);
  }
  DBG_RETURN(1);
}

static int cairo_set_dash_L(lua_State* L) {    
  reactor_cairo_t* rcr = 0;
  cairo_t* cr = 0;
  DBG_ENTER();
  checkself_cairo(L, &rcr, &cr);
  {    
    double dashes[64];
    int num_dashes = 0;    
    
    while(num_dashes < 64) {
      dashes[num_dashes] = luaL_optnumber(L, 2 + num_dashes, -1);
      if (dashes[num_dashes] < 0)
        break;
      num_dashes++;
    }

    cairo_set_dash(cr, dashes, num_dashes, 0);    
  }
  DBG_RETURN(0);
}

static int cairo_get_dash_count_L(lua_State* L) {    
  reactor_cairo_t* rcr = 0;
  cairo_t* cr = 0;
  DBG_ENTER();
  checkself_cairo(L, &rcr, &cr);
  {
    lua_pushnumber(L, cairo_get_dash_count(cr));
  }
  DBG_RETURN(1);
}

static int cairo_get_dash_L(lua_State* L) {    
  reactor_cairo_t* rcr = 0;
  cairo_t* cr = 0;
  int count = 0;
  DBG_ENTER();
  checkself_cairo(L, &rcr, &cr);
  {    
    double dashes[64];
    double offset;    
    int i;

    count = cairo_get_dash_count(cr);
    cairo_get_dash(cr, dashes, &offset);

    lua_checkstack(L, count); //TODO what to do when checkstack fails?

    for(i=0; i<count; i++) {
      lua_pushnumber(L, dashes[i]);
    }       
  }
  DBG_RETURN(count);
}



static int cairo_set_line_cap_L(lua_State* L) {    
  reactor_cairo_t* rcr = 0;
  cairo_t* cr = 0;
  DBG_ENTER();
  checkself_cairo(L, &rcr, &cr);
  {
    cairo_set_line_cap(cr, luaL_checkoption(L, 2, "butt", line_cap_options));
  }
  DBG_RETURN(0);
}

static int cairo_get_line_cap_L(lua_State* L) {    
  reactor_cairo_t* rcr = 0;
  cairo_t* cr = 0;
  DBG_ENTER();
  checkself_cairo(L, &rcr, &cr);
  {
    lua_pushstring(L, line_cap_options[cairo_get_line_cap(cr)]);
  }
  DBG_RETURN(1);
}



static int cairo_set_line_join_L(lua_State* L) {    
  reactor_cairo_t* rcr = 0;
  cairo_t* cr = 0;
  DBG_ENTER();
  checkself_cairo(L, &rcr, &cr);
  {
    cairo_set_line_join(cr, luaL_checkoption(L, 2, "miter", line_join_options));
  }
  DBG_RETURN(0);
}

static int cairo_get_line_join_L(lua_State* L) {    
  reactor_cairo_t* rcr = 0;
  cairo_t* cr = 0;
  DBG_ENTER();
  checkself_cairo(L, &rcr, &cr);
  {
    lua_pushstring(L, line_join_options[cairo_get_line_join(cr)]);
  }
  DBG_RETURN(1);
}


static int cairo_set_line_width_L(lua_State* L) {    
  reactor_cairo_t* rcr = 0;
  cairo_t* cr = 0;
  DBG_ENTER();
  checkself_cairo(L, &rcr, &cr);
  {
    cairo_set_line_width(cr, luaL_checknumber(L, 2));
  }
  DBG_RETURN(0);
}

static int cairo_get_line_width_L(lua_State* L) {    
  reactor_cairo_t* rcr = 0;
  cairo_t* cr = 0;
  DBG_ENTER();
  checkself_cairo(L, &rcr, &cr);
  {
    lua_pushnumber(L, cairo_get_line_width(cr));
  }
  DBG_RETURN(1);
}

static int cairo_set_miter_limit_L(lua_State* L) {    
  reactor_cairo_t* rcr = 0;
  cairo_t* cr = 0;
  DBG_ENTER();
  checkself_cairo(L, &rcr, &cr);
  {
    cairo_set_miter_limit(cr, luaL_checknumber(L, 2));
  }
  DBG_RETURN(0);
}

static int cairo_get_miter_limit_L(lua_State* L) {    
  reactor_cairo_t* rcr = 0;
  cairo_t* cr = 0;
  DBG_ENTER();
  checkself_cairo(L, &rcr, &cr);
  {
    lua_pushnumber(L, cairo_get_miter_limit(cr));
  }
  DBG_RETURN(1);
}



static int cairo_set_operator_L(lua_State* L) {    
  reactor_cairo_t* rcr = 0;
  cairo_t* cr = 0;
  DBG_ENTER();
  checkself_cairo(L, &rcr, &cr);
  {
    cairo_set_operator(cr, luaL_checkoption(L, 2, "over", operator_options));
  }
  DBG_RETURN(0);
}

static int cairo_get_operator_L(lua_State* L) {    
  reactor_cairo_t* rcr = 0;
  cairo_t* cr = 0;
  DBG_ENTER();
  checkself_cairo(L, &rcr, &cr);
  {    
    lua_pushstring(L, operator_options[cairo_get_operator(cr)]);
  }
  DBG_RETURN(1);
}

static int cairo_clip_L(lua_State* L) {    
  reactor_cairo_t* rcr = 0;
  cairo_t* cr = 0;
  DBG_ENTER();
  checkself_cairo(L, &rcr, &cr);
  {
    cairo_clip(cr);
  }
  DBG_RETURN(0);
}

static int cairo_clip_preserve_L(lua_State* L) {    
  reactor_cairo_t* rcr = 0;
  cairo_t* cr = 0;
  DBG_ENTER();
  checkself_cairo(L, &rcr, &cr);
  {
    cairo_clip_preserve(cr);
  }
  DBG_RETURN(0);
}

static int cairo_clip_extents_L(lua_State* L) {    
  reactor_cairo_t* rcr = 0;
  cairo_t* cr = 0;
  DBG_ENTER();
  checkself_cairo(L, &rcr, &cr);
  {
    double x1, y1, x2, y2;
    cairo_clip_extents(cr, &x1, &y1, &x2, &y2);
    lua_pushnumber(L, x1);
    lua_pushnumber(L, y1);
    lua_pushnumber(L, x2);
    lua_pushnumber(L, y2);
  }
  DBG_RETURN(4);
}

static int cairo_reset_clip_L(lua_State* L) {    
  reactor_cairo_t* rcr = 0;
  cairo_t* cr = 0;
  DBG_ENTER();
  checkself_cairo(L, &rcr, &cr);
  {
    cairo_reset_clip(cr);
  }
  DBG_RETURN(0);
}

static int cairo_fill_L(lua_State* L) {    
  reactor_cairo_t* rcr = 0;
  cairo_t* cr = 0;
  DBG_ENTER();
  checkself_cairo(L, &rcr, &cr);
  {
    cairo_fill(cr);
  }
  DBG_RETURN(0);
}

static int cairo_fill_preserve_L(lua_State* L) {    
  reactor_cairo_t* rcr = 0;
  cairo_t* cr = 0;
  DBG_ENTER();
  checkself_cairo(L, &rcr, &cr);
  {
    cairo_fill_preserve(cr);
  }
  DBG_RETURN(0);
}

static int cairo_fill_extents_L(lua_State* L) {    
  reactor_cairo_t* rcr = 0;
  cairo_t* cr = 0;
  DBG_ENTER();
  checkself_cairo(L, &rcr, &cr);
  {
    double x1, y1, x2, y2;
    cairo_fill_extents(cr, &x1, &y1, &x2, &y2);
    lua_pushnumber(L, x1);
    lua_pushnumber(L, y1);
    lua_pushnumber(L, x2);
    lua_pushnumber(L, y2);
  }
  DBG_RETURN(4);
}

static int cairo_in_fill_L(lua_State* L) {    
  reactor_cairo_t* rcr = 0;
  cairo_t* cr = 0;
  DBG_ENTER();
  checkself_cairo(L, &rcr, &cr);
  {
    lua_pushboolean(L, cairo_in_fill(cr, luaL_checknumber(L, 2), luaL_checknumber(L, 3)));
  }
  DBG_RETURN(1);
}

static int cairo_mask_L(lua_State* L) {    
  reactor_cairo_t* rcr = 0;
  cairo_t* cr = 0;
  DBG_ENTER();
  checkself_cairo(L, &rcr, &cr);
  {
    cairo_mask(cr, check_cairo_pattern(L, 2));
  }
  DBG_RETURN(0);
}

static int cairo_mask_surface_L(lua_State* L) {    
  reactor_cairo_t* rcr = 0;
  cairo_t* cr = 0;
  DBG_ENTER();
  checkself_cairo(L, &rcr, &cr);
  {
    cairo_mask_surface(cr, check_cairo_surface(L, 2), luaL_checknumber(L, 3), luaL_checknumber(L, 4));
  }
  DBG_RETURN(0);
}

static int cairo_paint_L(lua_State* L) {    
  reactor_cairo_t* rcr = 0;
  cairo_t* cr = 0;
  DBG_ENTER();
  checkself_cairo(L, &rcr, &cr);
  {
    cairo_paint(cr);
  }
  DBG_RETURN(0);
}

static int cairo_paint_with_alpha_L(lua_State* L) {    
  reactor_cairo_t* rcr = 0;
  cairo_t* cr = 0;
  DBG_ENTER();
  checkself_cairo(L, &rcr, &cr);
  {
    cairo_paint_with_alpha(cr, luaL_checknumber(L, 2));
  }
  DBG_RETURN(0);
}

static int cairo_stroke_L(lua_State* L) {    
  reactor_cairo_t* rcr = 0;
  cairo_t* cr = 0;
  DBG_ENTER();
  checkself_cairo(L, &rcr, &cr);
  {
    cairo_stroke(cr);
  }
  DBG_RETURN(0);
}

static int cairo_stroke_preserve_L(lua_State* L) {    
  reactor_cairo_t* rcr = 0;
  cairo_t* cr = 0;
  DBG_ENTER();
  checkself_cairo(L, &rcr, &cr);
  {
    cairo_stroke_preserve(cr);
  }
  DBG_RETURN(0);
}

static int cairo_stroke_extents_L(lua_State* L) {    
  reactor_cairo_t* rcr = 0;
  cairo_t* cr = 0;
  DBG_ENTER();
  checkself_cairo(L, &rcr, &cr);
  {
    double x1, y1, x2, y2;
    cairo_stroke_extents(cr, &x1, &y1, &x2, &y2);
    lua_pushnumber(L, x1);
    lua_pushnumber(L, y1);
    lua_pushnumber(L, x2);
    lua_pushnumber(L, y2);
  }
  DBG_RETURN(4);
}

static int cairo_in_stroke_L(lua_State* L) {    
  reactor_cairo_t* rcr = 0;
  cairo_t* cr = 0;
  DBG_ENTER();
  checkself_cairo(L, &rcr, &cr);
  {
    lua_pushboolean(L, cairo_in_stroke(cr, luaL_checknumber(L, 2), luaL_checknumber(L, 3)));
  }
  DBG_RETURN(1);
}

static int cairo_new_path_L(lua_State* L) {    
  reactor_cairo_t* rcr = 0;
  cairo_t* cr = 0;
  DBG_ENTER();
  checkself_cairo(L, &rcr, &cr);
  {
    cairo_new_path(cr);
  }
  DBG_RETURN(0);
}

static int cairo_new_sub_path_L(lua_State* L) {    
  reactor_cairo_t* rcr = 0;
  cairo_t* cr = 0;
  DBG_ENTER();
  checkself_cairo(L, &rcr, &cr);
  {
    cairo_new_sub_path(cr);
  }
  DBG_RETURN(0);
}

static int cairo_close_path_L(lua_State* L) {    
  reactor_cairo_t* rcr = 0;
  cairo_t* cr = 0;
  DBG_ENTER();
  checkself_cairo(L, &rcr, &cr);
  {
    cairo_close_path(cr);
  }
  DBG_RETURN(0);
}

static int cairo_arc_L(lua_State* L) {    
  reactor_cairo_t* rcr = 0;
  cairo_t* cr = 0;
  DBG_ENTER();
  checkself_cairo(L, &rcr, &cr);
  {
    cairo_arc(cr, 
      luaL_checknumber(L, 2), luaL_checknumber(L, 3),
      luaL_checknumber(L, 4), luaL_checknumber(L, 5),
      luaL_checknumber(L, 6)
      );
  }
  DBG_RETURN(0);
}

static int cairo_arc_negative_L(lua_State* L) {    
  reactor_cairo_t* rcr = 0;
  cairo_t* cr = 0;
  DBG_ENTER();
  checkself_cairo(L, &rcr, &cr);
  {
    cairo_arc_negative(cr, 
      luaL_checknumber(L, 2), luaL_checknumber(L, 3),
      luaL_checknumber(L, 4), luaL_checknumber(L, 5),
      luaL_checknumber(L, 6)
      );
  }
  DBG_RETURN(0);
}

static int cairo_curve_to_L(lua_State* L) {    
  reactor_cairo_t* rcr = 0;
  cairo_t* cr = 0;
  DBG_ENTER();
  checkself_cairo(L, &rcr, &cr);
  {
    cairo_curve_to(cr, 
      luaL_checknumber(L, 2), luaL_checknumber(L, 3),
      luaL_checknumber(L, 4), luaL_checknumber(L, 5),
      luaL_checknumber(L, 6), luaL_checknumber(L, 7));
  }
  DBG_RETURN(0);
}

static int cairo_line_to_L(lua_State* L) {    
  reactor_cairo_t* rcr = 0;
  cairo_t* cr = 0;
  DBG_ENTER();
  checkself_cairo(L, &rcr, &cr);
  {
    cairo_line_to(cr, luaL_checknumber(L, 2), luaL_checknumber(L, 3));
  }
  DBG_RETURN(0);
}

static int cairo_move_to_L(lua_State* L) {    
  reactor_cairo_t* rcr = 0;
  cairo_t* cr = 0;
  DBG_ENTER();
  checkself_cairo(L, &rcr, &cr);
  {
    cairo_move_to(cr, luaL_checknumber(L, 2), luaL_checknumber(L, 3));
  }
  DBG_RETURN(0);
}

static int cairo_rectangle_L(lua_State* L) {    
  reactor_cairo_t* rcr = 0;
  cairo_t* cr = 0;
  DBG_ENTER();
  checkself_cairo(L, &rcr, &cr);
  {
    cairo_rectangle(cr, 
      luaL_checknumber(L, 2), luaL_checknumber(L, 3),
      luaL_checknumber(L, 4), luaL_checknumber(L, 5));
  }
  DBG_RETURN(0);
}

static int cairo_text_path_L(lua_State* L) {    
  reactor_cairo_t* rcr = 0;
  cairo_t* cr = 0;
  DBG_ENTER();
  checkself_cairo(L, &rcr, &cr);
  {
    cairo_text_path(cr, luaL_checkstring(L, 2));
  }
  DBG_RETURN(0);
}

static int cairo_rel_curve_to_L(lua_State* L) {    
  reactor_cairo_t* rcr = 0;
  cairo_t* cr = 0;
  DBG_ENTER();
  checkself_cairo(L, &rcr, &cr);
  {
    cairo_rel_curve_to(cr, 
      luaL_checknumber(L, 2), luaL_checknumber(L, 3),
      luaL_checknumber(L, 4), luaL_checknumber(L, 5),
      luaL_checknumber(L, 6), luaL_checknumber(L, 7));
  }
  DBG_RETURN(0);
}

static int cairo_rel_line_to_L(lua_State* L) {    
  reactor_cairo_t* rcr = 0;
  cairo_t* cr = 0;
  DBG_ENTER();
  checkself_cairo(L, &rcr, &cr);
  {
    cairo_rel_line_to(cr, luaL_checknumber(L, 2), luaL_checknumber(L, 3));
  }
  DBG_RETURN(0);
}

static int cairo_rel_move_to_L(lua_State* L) {    
  reactor_cairo_t* rcr = 0;
  cairo_t* cr = 0;
  DBG_ENTER();
  checkself_cairo(L, &rcr, &cr);
  {
    cairo_rel_move_to(cr, luaL_checknumber(L, 2), luaL_checknumber(L, 3));
  }
  DBG_RETURN(0);
}

static int cairo_path_extents_L(lua_State* L) {    
  reactor_cairo_t* rcr = 0;
  cairo_t* cr = 0;
  DBG_ENTER();
  checkself_cairo(L, &rcr, &cr);
  {
    double x1, y1, x2, y2;
    cairo_path_extents(cr, &x1, &y1, &x2, &y2);
    lua_pushnumber(L, x1);
    lua_pushnumber(L, y1);
    lua_pushnumber(L, x2);
    lua_pushnumber(L, y2);
  }
  DBG_RETURN(4);
}



static int cairo_select_font_face_L(lua_State* L) {    
  reactor_cairo_t* rcr = 0;
  cairo_t* cr = 0;
  DBG_ENTER();
  checkself_cairo(L, &rcr, &cr);
  {
    const char* face = luaL_checkstring(L, 2);
    int slant = luaL_checkoption (L, 3, "normal", slant_options);
    int weight = luaL_checkoption (L, 4, "normal", weight_options); 
    cairo_select_font_face(cr, face, slant, weight);
  }
  DBG_RETURN(0);
}

static int cairo_set_font_size_L(lua_State* L) {    
  reactor_cairo_t* rcr = 0;
  cairo_t* cr = 0;
  DBG_ENTER();
  checkself_cairo(L, &rcr, &cr);
  {    
    cairo_set_font_size(cr, luaL_checknumber(L, 2));
    //{
    //cairo_font_options_t* options = cairo_font_options_create();

    ////if (luaL_optstring(L, 2, 0))
    //cairo_font_options_set_antialias(options, CAIRO_ANTIALIAS_GRAY);//luaL_checkoption(L, 2, "default", antialias_options));

    //cairo_set_font_options(cr, options);
    //cairo_font_options_destroy(options);
    //}
  }
  DBG_RETURN(0);
}

static int cairo_set_font_options_L(lua_State* L) {    
  reactor_cairo_t* rcr = 0;
  cairo_t* cr = 0;
  DBG_ENTER();
  checkself_cairo(L, &rcr, &cr);
  { 
    //TODO put this as member in rcr so we don't malloc each time
    cairo_font_options_t* options = cairo_font_options_create();

    if (luaL_optstring(L, 2, 0))
      cairo_font_options_set_antialias(options, luaL_checkoption(L, 2, "default", antialias_options));


    //cairo_font_options_set_hint_metrics (options, CAIRO_HINT_METRICS_OFF);

    cairo_set_font_options(cr, options);
    cairo_font_options_destroy(options);
  }
  DBG_RETURN(0);
}

static int cairo_set_font_face_L(lua_State* L) {    
  reactor_cairo_t* rcr = 0;
  cairo_t* cr = 0;
  DBG_ENTER();
  checkself_cairo(L, &rcr, &cr);
  { 
    cairo_set_font_face(cr, check_cairo_font_face(L, 2));
  }
  DBG_RETURN(0);
}

//takes 2 extra params to indicate a substring
static int cairo_show_text_L(lua_State* L) {
  reactor_cairo_t* rcr = 0;
  cairo_t* cr = 0;
  DBG_ENTER();
  checkself_cairo(L, &rcr, &cr);
  { 
    size_t l;
    const char *s = luaL_checklstring(L, 2, &l);
    ptrdiff_t start = posrelat(luaL_optinteger(L, 3, 1), l);
    ptrdiff_t end = posrelat(luaL_optinteger(L, 4, -1), l);

    if (start < 1) start = 1;
    if (end > (ptrdiff_t)l) end = (ptrdiff_t)l;

    if (start <= end) {    
      size_t len = end-start+1;
      s+= (start-1);

      if (end < (ptrdiff_t)l) {
        //This is a huge bad hack, playing with fire, don't want to allocate a buffer every time to make it work with cairo api
        //this will probably be fatal in luajit, need to use real cairo text api, damnit.
        char restore = s[len];
        ((char*)s)[len] = 0;        
        cairo_show_text(cr, s);
        ((char*)s)[len] = restore;
      }
      else {        
        cairo_show_text(cr, s);
      }
    }
  }  
  DBG_RETURN(0);
}

static int cairo_font_extents_L(lua_State* L) {
  reactor_cairo_t* rcr = 0;
  cairo_t* cr = 0;
  DBG_ENTER();
  checkself_cairo(L, &rcr, &cr);
  { 
    cairo_font_extents_t rec;
    cairo_font_extents(cr, &rec);
    lua_pushnumber(L, rec.ascent);
    lua_pushnumber(L, rec.descent);
    lua_pushnumber(L, rec.height);
    lua_pushnumber(L, rec.max_x_advance);
    lua_pushnumber(L, rec.max_y_advance);  
  }  
  DBG_RETURN(5);
}

//takes 2 extra params to indicate a substring
static int cairo_text_extents_L(lua_State* L) {
  reactor_cairo_t* rcr = 0;
  cairo_t* cr = 0;
  DBG_ENTER();
  checkself_cairo(L, &rcr, &cr);
  {
    cairo_text_extents_t rec;
    size_t l;
    const char *s = luaL_checklstring(L, 2, &l);
    ptrdiff_t start = posrelat(luaL_optinteger(L, 3, 1), l);
    ptrdiff_t end = posrelat(luaL_optinteger(L, 4, -1), l);

    if (start < 1) start = 1;
    if (end > (ptrdiff_t)l) end = (ptrdiff_t)l;

    if (start <= end) {    
      size_t len = end-start+1;
      s+= (start-1);

      if (end < (ptrdiff_t)l) {
        //This is a huge bad hack, playing with fire, don't want to allocate a buffer every time to make it work with cairo api
        //this will probably be fatal in luajit, need to use real cairo text api, damnit.
        char restore = s[len];
        ((char*)s)[len] = 0;
        cairo_text_extents(cr, s, &rec);
        ((char*)s)[len] = restore;
      }
      else {
        cairo_text_extents(cr, s, &rec);
      }
    }
    lua_pushnumber(L, rec.x_bearing);
    lua_pushnumber(L, rec.y_bearing);
    lua_pushnumber(L, rec.width);
    lua_pushnumber(L, rec.height);
    lua_pushnumber(L, rec.x_advance);
    lua_pushnumber(L, rec.y_advance); 
  }
  DBG_RETURN(6);
}



static int cairo_scale_L(lua_State* L) {    
  reactor_cairo_t* rcr = 0;
  cairo_t* cr = 0;
  DBG_ENTER();
  checkself_cairo(L, &rcr, &cr);
  {
    cairo_scale(cr, luaL_checknumber(L, 2), luaL_checknumber(L, 3));
  }
  DBG_RETURN(0);
}

static int cairo_translate_L(lua_State* L) {    
  reactor_cairo_t* rcr = 0;
  cairo_t* cr = 0;
  DBG_ENTER();
  checkself_cairo(L, &rcr, &cr);
  {
    cairo_translate(cr, luaL_checknumber(L, 2), luaL_checknumber(L, 3));
  }
  DBG_RETURN(0);
}

static int cairo_rotate_L(lua_State* L) {    
  reactor_cairo_t* rcr = 0;
  cairo_t* cr = 0;
  DBG_ENTER();
  checkself_cairo(L, &rcr, &cr);
  {
    cairo_rotate(cr, luaL_checknumber(L, 2));
  }
  DBG_RETURN(0);
}

static int cairo_identity_matrix_L(lua_State* L) {    
  reactor_cairo_t* rcr = 0;
  cairo_t* cr = 0;
  DBG_ENTER();
  checkself_cairo(L, &rcr, &cr);
  {
    cairo_identity_matrix(cr);
  }
  DBG_RETURN(0);
}


void luaopen_cairo(lua_State* L) 
{
  DBG_ENTER();
  {    
    static const luaL_reg cairo_functions[] = {
      {"__gc", cairo__gc_L},   
      {"destroy", cairo_destroy_L}, 
      {"save", cairo_save_L}, 
      {"restore", cairo_restore_L}, 
      {"push_group", cairo_push_group_L}, 
      {"push_group_with_content", cairo_push_group_with_content_L}, 
      {"pop_group", cairo_pop_group_L}, 
      {"pop_group_to_source", cairo_pop_group_to_source_L}, 
      {"set_source_rgb", cairo_set_source_rgb_L}, 
      {"set_source_rgba", cairo_set_source_rgba_L}, 
      {"set_source", cairo_set_source_L}, 
      {"set_source_surface", cairo_set_source_surface_L}, 
      {"set_antialias", cairo_set_antialias_L},
      {"get_antialias", cairo_get_antialias_L}, 
      {"set_dash", cairo_set_dash_L}, 
      {"get_dash_count", cairo_get_dash_count_L}, 
      {"get_dash", cairo_get_dash_L}, 
      {"set_line_cap", cairo_set_line_cap_L}, 
      {"get_line_cap", cairo_get_line_cap_L}, 
      {"set_line_join", cairo_set_line_join_L},
      {"get_line_join", cairo_get_line_join_L}, 
      {"set_line_width", cairo_set_line_width_L}, 
      {"get_line_width", cairo_get_line_width_L}, 
      {"set_miter_limit", cairo_set_miter_limit_L}, 
      {"get_miter_limit", cairo_get_miter_limit_L}, 
      {"set_operator", cairo_set_operator_L}, 
      {"get_operator", cairo_get_operator_L},
      {"clip", cairo_clip_L}, 
      {"clip_preserve", cairo_clip_preserve_L}, 
      {"clip_extents", cairo_clip_extents_L}, 
      {"reset_clip", cairo_reset_clip_L}, 
      {"fill", cairo_fill_L}, 
      {"fill_preserve", cairo_fill_preserve_L}, 
      {"fill_extents", cairo_fill_extents_L},
      {"in_fill", cairo_in_fill_L}, 
      {"mask", cairo_mask_L}, 
      {"mask_surface", cairo_mask_surface_L}, 
      {"paint", cairo_paint_L}, 
      {"paint_with_alpha", cairo_paint_with_alpha_L}, 
      {"stroke", cairo_stroke_L}, 
      {"stroke_preserve", cairo_stroke_preserve_L},
      {"stroke_extents", cairo_stroke_extents_L}, 
      {"in_stroke", cairo_in_stroke_L}, 
      {"new_path", cairo_new_path_L}, 
      {"new_sub_path", cairo_new_sub_path_L}, 
      {"close_path", cairo_close_path_L}, 
      {"arc", cairo_arc_L}, 
      {"arc_negative", cairo_arc_negative_L},
      {"curve_to", cairo_curve_to_L}, 
      {"line_to", cairo_line_to_L}, 
      {"move_to", cairo_move_to_L}, 
      {"rectangle", cairo_rectangle_L}, 
      {"text_path", cairo_text_path_L}, 
      {"rel_curve_to", cairo_rel_curve_to_L}, 
      {"rel_line_to", cairo_rel_line_to_L},
      {"rel_move_to", cairo_rel_move_to_L}, 
      {"path_extents", cairo_path_extents_L},
      {"select_font_face", cairo_select_font_face_L}, 
      {"set_font_size", cairo_set_font_size_L}, 
      {"set_font_options", cairo_set_font_options_L}, 
      {"set_font_face", cairo_set_font_face_L},
      {"show_text", cairo_show_text_L}, 
      {"font_extents", cairo_font_extents_L}, 
      {"text_extents", cairo_text_extents_L}, 
      {"scale", cairo_scale_L}, 
      {"translate", cairo_translate_L}, 
      {"rotate", cairo_rotate_L},    
      {"identity_matrix", cairo_identity_matrix_L},  
      {0, 0}
    };

    static const luaL_reg module_functions[] = {      
      {"create", cairo_create_L}, 
      {"destroy", cairo_destroy_L}, 
      {"save", cairo_save_L}, 
      {"restore", cairo_restore_L}, 
      {"push_group", cairo_push_group_L}, 
      {"push_group_with_content", cairo_push_group_with_content_L}, 
      {"pop_group", cairo_pop_group_L}, 
      {"pop_group_to_source", cairo_pop_group_to_source_L}, 
      {"set_source_rgb", cairo_set_source_rgb_L}, 
      {"set_source_rgba", cairo_set_source_rgba_L}, 
      {"set_source", cairo_set_source_L}, 
      {"set_source_surface", cairo_set_source_surface_L}, 
      {"set_antialias", cairo_set_antialias_L},
      {"get_antialias", cairo_get_antialias_L}, 
      {"set_dash", cairo_set_dash_L}, 
      {"get_dash_count", cairo_get_dash_count_L}, 
      {"get_dash", cairo_get_dash_L}, 
      {"set_line_cap", cairo_set_line_cap_L}, 
      {"get_line_cap", cairo_get_line_cap_L}, 
      {"set_line_join", cairo_set_line_join_L},
      {"get_line_join", cairo_get_line_join_L}, 
      {"set_line_width", cairo_set_line_width_L}, 
      {"get_line_width", cairo_get_line_width_L}, 
      {"set_miter_limit", cairo_set_miter_limit_L}, 
      {"get_miter_limit", cairo_get_miter_limit_L}, 
      {"set_operator", cairo_set_operator_L}, 
      {"get_operator", cairo_get_operator_L},
      {"clip", cairo_clip_L}, 
      {"clip_preserve", cairo_clip_preserve_L}, 
      {"clip_extents", cairo_clip_extents_L}, 
      {"reset_clip", cairo_reset_clip_L}, 
      {"fill", cairo_fill_L}, 
      {"fill_preserve", cairo_fill_preserve_L}, 
      {"fill_extents", cairo_fill_extents_L},
      {"in_fill", cairo_in_fill_L}, 
      {"mask", cairo_mask_L}, 
      {"mask_surface", cairo_mask_surface_L}, 
      {"paint", cairo_paint_L}, 
      {"paint_with_alpha", cairo_paint_with_alpha_L}, 
      {"stroke", cairo_stroke_L}, 
      {"stroke_preserve", cairo_stroke_preserve_L},
      {"stroke_extents", cairo_stroke_extents_L}, 
      {"in_stroke", cairo_in_stroke_L}, 
      {"new_path", cairo_new_path_L}, 
      {"new_sub_path", cairo_new_sub_path_L}, 
      {"close_path", cairo_close_path_L}, 
      {"arc", cairo_arc_L}, 
      {"arc_negative", cairo_arc_negative_L},
      {"curve_to", cairo_curve_to_L}, 
      {"line_to", cairo_line_to_L}, 
      {"move_to", cairo_move_to_L}, 
      {"rectangle", cairo_rectangle_L}, 
      {"text_path", cairo_text_path_L}, 
      {"rel_curve_to", cairo_rel_curve_to_L}, 
      {"rel_line_to", cairo_rel_line_to_L},
      {"rel_move_to", cairo_rel_move_to_L}, 
      {"path_extents", cairo_path_extents_L},      
      {"select_font_face", cairo_select_font_face_L}, 
      {"set_font_size", cairo_set_font_size_L}, 
      {"set_font_options", cairo_set_font_options_L}, 
      {"set_font_face", cairo_set_font_face_L},
      {"show_text", cairo_show_text_L}, 
      {"font_extents", cairo_font_extents_L}, 
      {"text_extents", cairo_text_extents_L}, 
      {"scale", cairo_scale_L}, 
      {"translate", cairo_translate_L}, 
      {"rotate", cairo_rotate_L},  
      {"identity_matrix", cairo_identity_matrix_L},  
      {NULL, NULL}
    };
    luaL_newmetatable(L, "reactor_cairo_t");
    lua_pushvalue(L, -1);
    lua_setfield(L, -2, "__index");
    luaL_register(L, 0, cairo_functions);
    lua_pop(L, 1);

    luaL_register(L, "cairo", module_functions);

    lua_pushliteral(L, "surface");
    luaopen_cairo_surface(L);
    lua_settable(L, -3);

    lua_pushliteral(L, "pattern");
    luaopen_cairo_pattern(L);
    lua_settable(L, -3);

    lua_pushliteral(L, "font");
    luaopen_cairo_font_face(L);
    lua_settable(L, -3);
  }
  DBG_RETURN_VOID();
}





