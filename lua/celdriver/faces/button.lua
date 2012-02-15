local cel = require 'cel'

local face = cel.getface('button')

face.textcolor = 'current'
face.color = 'current'
face.bordercolor = cel.color.rgb(.4, .4, .4)
face.borderwidth = 1
face.image = {
  texture = reactor.graphics.texture.create(32, 32),
  l = 5,
}

do --draw to texture
  local surface = cairo.surface.create(32, 32)
  local cr = cairo.create(surface)
  cairo.set_line_width(cr, 4)
  cairo.roundrect(cr, 2, 2, 32-4, 32-4, 4)
  cairo.set_source_rgb(cr, 1, 1, 1)
  cairo.stroke(cr)
  reactor.graphics.updatetexture(face.image.texture, surface)
  cr:destroy()
  surface:destroy()
end

function face.select(f, t)
  if t.mousefocusin then
    f = f['%mousefocusin'] or f
    if t.pressed then
      f = f['%pressed'] or f
    end
  elseif t.pressed then
    f = f['%pressed'] or f
  end
  return f
end

do
  face['%pressed'] = face:new {
    color = cel.color.tint(face.color, .5),
    bordercolor = cel.color.rgb(0, 1, 1),
  }

  face['%mousefocusin'] = face:new {
    color = cel.color.tint(face.color, .5),
    bordercolor = cel.color.rgb(0, 1, 1),
  }
  
  do
    local face = face['%mousefocusin']

    face['%pressed'] = face:new {
      textcolor = cel.color.rgb(.2, .2, .2),
      color = cel.color.rgb(0, .8, .8),
      bordercolor = cel.color.rgb(0, 1, 1),
      borderwidth = 2,
    }
  end
end


