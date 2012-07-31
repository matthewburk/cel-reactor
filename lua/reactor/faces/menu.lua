local cel = require 'cel'

local face = cel.getface('menu')

face.color = cel.color.rgb(.4, .4, .4)
face.bordercolor = cel.color.rgb(.2, .2, .2)
face.borderwidth = false

face.layout = {
  showdelay = 200;
  hidedelay = 500;
  slot = {
    margin = {
      l = 0,
      r = 30,
      t = function(w, h) return h*.25 end; 
      b = function(w, h) return h*.25 end;
    };
    link = {'fill.leftmargin', 5};
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

do --menu.slot
  local face = cel.getface('menu.slot')

  function face.cairodraw(_ENV, cr, f, t)
    _ENV.drawlinks(cr, t)

    if t.submenu then
      local linker = cel.getlinker('right.center')
      local x, y, w, h = linker(t.w, t.h, 0, 0, t.h/3, t.h/3, t.h/4, 0)
      cr:set_source_rgb(0, 0, 1)
      cr:rectangle(x, y, w, h)
      cr:fill()
    end

    if t.mousefocusin or t.submenu == 'active' then
      cr:set_source_rgba(0, 1, 1, .3)
      cr:rectangle(0, 0, t.w, t.h)
      cr:fill()
    end
  end
end






