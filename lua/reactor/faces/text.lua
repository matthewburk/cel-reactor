local cel = require 'cel'

local face = cel.getface('text')
face.textcolor = 'current'
face.color = false
face.bordercolor = false
face.borderwidth = false 

face.layout = {
  padding = {
    l=function(w, h, font) return math.floor(font.metrics[' '].advance/2) end,
    r=function(w, h, font) return math.floor(.9+font.metrics[' '].advance/2) end,
  },
}

function face.cairodraw(_ENV, cr, f, t)
  if f.color then
    cr:rectangle(0, 0, t.w, t.h)
    cr:set_source_color(_ENV.color)
    cr:fill()
  end

  if f.textcolor and t.text then
    cr:set_source_color(_ENV.textcolor)

    --TODO lineheight is not exact, this may skip things that should be rendered
    local lineheight = t.font.lineheight
    local ymin = t.clip.t - _ENV.Y - lineheight
    local ymax = t.clip.b - _ENV.Y + lineheight

    for i, line in ipairs(t.lines) do
      if line.peny > ymin then
        if line.peny > ymax then
          break
        else
          cr:drawstring(t.font, line.penx, line.peny, line.text)
        end
      end
    end
  end

  if f.borderwidth and f.bordercolor then
    cr:set_line_width(f.borderwidth)
    cr:set_source_color(_ENV.bordercolor)
    cr:rectangle(0, 0, t.w, t.h)
    cr:stroke()
  end

  return _ENV.drawlinks(cr, t)
end

function face.print(f, t, pre, facename)
  local s = string.format('%s[%d:%s] { x:%d y:%d w:%d h:%d [refresh:%s]',
    t.metacel, t.id, tostring(facename), t.x, t.y, t.w, t.h, tostring(t.refresh))
  io.write(pre, s)
  if t.text then
    for i, line in ipairs(t.lines) do
      io.write('\n', pre, '  @@', string.format('line[%d %d %s]', line.penx, line.peny, line.text))
    end
  end
  if t.font then
    io.write('\n', pre, '  @@', string.format('font[%s:%d]', t.font.name, t.font.size))
  end
  if f.color then
    io.write('\n', pre, '  @@', string.format('color[%d, %d, %d, %d]', string.byte(f.color, 1, 4)))
  end
  if f.bordercolor and f.borderwidth then
    io.write('\n', pre, '  @@', string.format('bordercolor[%d, %d, %d, %d]', string.byte(f.bordercolor, 1, 4)))
  end
end




