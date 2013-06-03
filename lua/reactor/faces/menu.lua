local cel = require 'cel'

do --menu.slot
  local face = cel.getface('menu.slot')
  face.color = app.colors.themecomplementlight
  face.bordercolor = app.colors.themecomplementlight --TODO change bordercolor to accentcolor
  face.layout = {
    margin = {
      l = 0,
      r = 30,
      t = 5,--function(w, h) return h*.25 end; 
      b = 5,--function(w, h) return h*.25 end;
    },
  }

  function face.cairodraw(_ENV, cr, f, t)

    if t.submenu and _ENV.bordercolor then
      local linker = cel.getlinker('right.center')
      local x, y, w, h = linker(t.w, t.h, 0, 0, t.h/3, t.h/3, t.h/4, 0)
      cr:set_source_color(_ENV.bordercolor)
      cr:rectangle(x, y, w, h)
      cr:fill()
    end

    if _ENV.color and (t.mousefocusin or t.submenu == 'active') then
      cr:set_source_color(_ENV.color)
      cr:rectangle(0, 0, t.w, t.h)
      cr:fill()
    end

    return _ENV.drawlinks(cr, t)
  end
end

local face = cel.getface('menu')
face.color = cel.color.rgb(.4, .4, .4)
face.bordercolor = cel.color.rgb(.2, .2, .2)
face.borderwidth = false

face.layout = {
  showdelay = 200,
  hidedelay = 500,
  menuslot = {
    face=nil,
    link = {'fill.leftmargin', 5},
  },
  
  divider = {
    w = 1; h = 1;
    link = {'width', 2};
  },
}

--[[
do --menu divider
  cel.face {
    metacel = 'cel';
    name = cel.menu.divider;
    color = cel.color.rgb(.8, .8, .8);
  }
end
--]]








