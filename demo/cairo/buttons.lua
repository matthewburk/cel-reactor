local cel = require 'cel'

local function clip(t, cr)
  local t = t.clip
  cr:reset_clip()
  cr:rectangle(t.l, t.t, t.r-t.l, t.b-t.t)
  cr:clip()
end

do
  local face = cel.getface('button'):new()

  face.color = cel.color.encodef(0, 1, 1)

  face.gradients = {
    cairo.pattern.create_linear(0, 0, 0, 1),
    cairo.pattern.create_linear(0, 0, 1, 0),
  }

  for i, lgrad in ipairs(face.gradients) do
    lgrad:add_color_stop(0, 1, 1, 1, .8)
    lgrad:add_color_stop(.05, 1, 1, 1, 0)
    lgrad:add_color_stop(.95, .5, .5, .5, 0)
    lgrad:add_color_stop(1, .5, .5, .5, .8)
  end

  face.border =15 
  face.select = false

  function face.draw(f, t)
    local cr = reactor.cr
    local x, y, w, h = t.x, t.y, t.w, t.h
    local border = f.border

    clip(t, cr)

    cr:set_source_rgb(cel.color.decodef(face.color))
    cr:rectangle(x, y, w, h)
    cr:fill()

    cr:save()
    cr:translate(x, y)
    cr:scale(w, h)

    if t.pressed then
      cr:rotate(math.pi)
    end

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

    --[[
    cr:set_source_rgb(.8, .8, .8)
    cr:rectangle(x+border, y+border, w-border-border, h-border-border)
    cr:fill()
    --]]
  end

  face:register('@pretty')
end

return function(root)
  cel.window {
    w = 400, h = 400,
    link = 'edges';
    cel.col {
      gap = 10;
      link = 'edges';
      { flex = 1;
        cel.row {
          gap = 10;
          { flex = 1; link = 'edges';
            cel.button.new(100, 100, '@pretty'),
            cel.button.new(100, 100, '@pretty'),
            cel.button.new(100, 100, '@pretty'),
            cel.button.new(100, 100, '@pretty'),
          };
        },
        cel.row {
          gap = 10;
          { flex = 1; link = 'edges';
            cel.button.new(100, 100, '@pretty'),
            cel.button.new(100, 100, '@pretty'),
            cel.button.new(100, 100, '@pretty'),
            cel.button.new(100, 100, '@pretty'),
          };
        },
        cel.row {
          gap = 10;
          { flex = 1; link = 'edges';
            cel.button.new(100, 100, '@pretty'),
            cel.button.new(100, 100, '@pretty'),
            cel.button.new(100, 100, '@pretty'),
            cel.button.new(100, 100, '@pretty'),
          };
        },
        cel.row {
          gap = 10;
          { flex = 1; link = 'edges';
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
