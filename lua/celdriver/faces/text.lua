local cel = require 'cel'

local face = cel.getface('text')
face.textcolor = 'current'
face.color = false
face.bordercolor = false
face.borderwidth = false

face.layout = {
  padding = {
    l = function(w, h, font) return font.ascent * .1 end,
  },
}

function face.cairodraw(_ENV, cr, f, t)
  if f.color then
    cairo.rectangle(cr, 0, 0, t.w, t.h)
    cairo.set_source_color(cr, _ENV.color)
    cairo.fill(cr)
  end

  if f.textcolor and t.text then
    cairo.set_source_color(cr, _ENV.textcolor)
    for i, line in ipairs(t.lines) do
      if string.sub(t.text, line.j, line.j) ~= '\n' then
      --uncomment this optimization later
      --if t.y + line.y < t.clip.b  and t.y + line.y + line.h > t.clip.t then
        cairo.drawstring(cr, t.font, line.penx, line.peny, t.text, line.i, line.j)
      --end
      elseif line.i < line.j then
        cairo.drawstring(cr, t.font, line.penx, line.peny, t.text, line.i, line.j-1)
      end
    end
  end

  if f.borderwidth and f.bordercolor then
    cairo.set_line_width(cr, f.borderwidth)
    cairo.set_source_color(cr, _ENV.bordercolor)
    cairo.rectangle(cr, 0, 0, t.w, t.h)
    cairo.stroke(cr)
  end

  return _ENV.drawlinks(cr, t)
end

function face.print(f, t, pre, facename)
  local s = string.format('%s[%d:%s] { x:%d y:%d w:%d h:%d [refresh:%s]',
    t.metacel, t.id, tostring(facename), t.x, t.y, t.w, t.h, tostring(t.refresh))
  io.write(pre, s)
  if t.text then
    for i, line in ipairs(t.lines) do
      io.write('\n', pre, '  @@', string.format('line[%d %d %s]', line.penx, line.peny, 
        string.sub(t.text, line.i, line.j)))
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




