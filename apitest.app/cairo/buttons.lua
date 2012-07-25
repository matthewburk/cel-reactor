local cel = require 'cel'

local function clip(t, cr)
  local t = t.clip
  cr:reset_clip()
  cr:rectangle(t.l, t.t, t.r-t.l, t.b-t.t)
  cr:clip()
end

do
  local face = cel.getface('button'):new()

  face.color = cel.color.rgb(0, 1, 1)

  face.gradients = {
    cairo.pattern.create_linear(0, 0, 0, 1),
    cairo.pattern.create_linear(0, 0, 1, 0),
  }

  for i, lgrad in ipairs(face.gradients) do
    lgrad:add_color_stop_rgba(0, 1, 1, 1, 1)
    lgrad:add_color_stop_rgba(.15, 1, 1, 1, 0)
    lgrad:add_color_stop_rgba(.85, .5, .5, .5, 0)
    lgrad:add_color_stop_rgba(1, .5, .5, .5, 1)
  end

  face.border =15 
  face.select = false

  function face.cairodraw(_ENV, cr, f, t)
    local x, y, w, h = t.x, t.y, t.w, t.h
    local border = f.border

    cairo.set_source_color(cr, f.color)
    

    cr:save()

    if t.pressed then
      cr:translate(w/2, h/2)
      cr:rotate(math.pi)
      cr:translate(-w/2, -h/2)
    end

    cr:rectangle(0, 0, w, h)
    cr:fill()

    cr:scale(w, h)

    

    cr:set_source(f.gradients[2])
    cr:move_to(.5, .5)
    cr:line_to(0, 1)
    cr:line_to(0, 0)
    cr:fill()

    cr:set_source(f.gradients[1])
    cr:move_to(.5, .5)
    cr:line_to(0, 0)
    cr:line_to(1, 0)
    cr:fill()

    cr:set_source(f.gradients[2])
    cr:move_to(.5, .5)
    cr:line_to(1, 0)
    cr:line_to(1, 1)
    cr:fill()

    cr:set_source(f.gradients[1])
    cr:move_to(.5, .5)
    cr:line_to(1, 1)
    cr:line_to(0, 1)
    cr:fill()

    cr:restore()
  end

  face:register('@pretty')
end

return function(root)
  cel.window {
    w = 400, h = 400,
    link = 'fill';
    cel.col {
      gap = 10;
      link = 'fill';
      { flex = 1;
        cel.row {
          gap = 10;
          { flex = 1; link = 'fill';
            cel.button.new(100, 100, '@pretty'),
            cel.button.new(100, 100, '@pretty'),
            cel.button.new(100, 100, '@pretty'),
            cel.button.new(100, 100, '@pretty'),
          };
        },
        cel.row {
          gap = 10;
          { flex = 1; link = 'fill';
            cel.button.new(100, 100, '@pretty'),
            cel.button.new(100, 100, '@pretty'),
            cel.button.new(100, 100, '@pretty'),
            cel.button.new(100, 100, '@pretty'),
          };
        },
        cel.row {
          gap = 10;
          { flex = 1; link = 'fill';
            cel.button.new(100, 100, '@pretty'),
            cel.button.new(100, 100, '@pretty'),
            cel.button.new(100, 100, '@pretty'),
            cel.button.new(100, 100, '@pretty'),
          };
        },
        cel.row {
          gap = 10;
          { flex = 1; link = 'fill';
            cel.button.new(100, 100, '@pretty'),
            cel.button.new(100, 100, '@pretty'),
            cel.button.new(100, 100, '@pretty'),
            cel.button.new(100, 100, '@pretty'),
          };
        },
      };
    }
  }:link(root)
end
