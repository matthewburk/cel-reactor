local cel = require 'cel'

return function(_ENV)
  setfenv(1, _ENV)

  local menu = cel.face {
    metacel = 'menu',
    color = cel.color.rgb(.4, .4, .4),
    bordercolor = cel.color.rgb(.2, .2, .2),
    borderwidth = false,
    radius = radius,

    layout = {
      showdelay = 200;
      hidedelay = 200;
      slot = {
        link = {'+width', 100};
        padding = {
          l = 0,
          r = 30,
          t = function(w, h) return h*.25 end; 
          b = function(w, h) return h*.25 end;
        };
        item = {
          link = 'width';
        };
      },
      divider = {
        w = 1; h = 1;
        link = {'width', 2};
      },
    }
  }

  do --menu divider
    cel.face {
      metacel = 'cel';
      name = cel.menu.divider;
      color = cel.color.rgb(.8, .8, .8);
    }
  end

  do --menu.slot
    local item = cel.face {
      metacel = 'menu.slot',
      highlightcolor = cel.color.rgb(1, 1, .5, .5),
    }

    function item.draw(f, t)
      drawlinks(t)

      if t.submenu then
        local linker = cel.getlinker('right.center')
        local x, y, w, h = linker(t.w, t.h, 0, 0, t.h/3, t.h/3, t.h/4, 0)
        cairo.rectangle(cr, t.x + x, t.y + y, w, h)
        cairo.fill(cr)
      end

      if t.mousefocusin or t.submenu == 'active' then
        if f.highlightcolor then
          cairo.extcel_set_source_color(cr, f.highlightcolor)
          cairo.rectangle(cr, t.x, t.y, t.w, t.h)
          cairo.fill(cr)
        end
      end
    end
  end

end






