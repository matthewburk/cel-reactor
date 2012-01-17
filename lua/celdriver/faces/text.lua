local cel = require 'cel'

return function(_ENV)
  setfenv(1, _ENV)

  local face = cel.getface('text')
  face.textcolor = cel.color.rgb(.1, .1, .1)
  face.fillcolor = false
  face.linecolor = false
  face.linewidth = false

  face.layout = {
    padding = {
      l = function(w, h, font) return font.ascent * .1 end,
    },
  }

  function face.draw(f, t)
    if f.fillcolor then
      cairo.extcel_set_source_color(cr, f.fillcolor)
      cairo.ext_roundrect(cr, 0, 0, t.w, t.h, f.radius)
      cairo.fill(cr)
    end

    if f.textcolor and t.text then
      cairo.extcel_set_source_color(cr, f.textcolor)
      for i, line in ipairs(t.lines) do
        if string.sub(t.text, line.j, line.j) ~= '\n' then
        --uncomment this optimization later
        --if t.y + line.y < t.clip.b  and t.y + line.y + line.h > t.clip.t then
          cairo.extcel_drawstring(cr, t.font, line.penx, line.peny, t.text, line.i, line.j)
        --end
        elseif line.i < line.j then
          cairo.extcel_drawstring(cr, t.font, line.penx, line.peny, t.text, line.i, line.j-1)
        end
      end
    end

    if f.linewidth and f.linecolor then
      cairo.set_line_width(cr, f.linewidth)
      cairo.extcel_set_source_color(cr, f.linecolor)
      cairo.ext_roundrect(cr, 0, 0, t.w, t.h, f.radius)
      cairo.stroke(cr)
    end

    return drawlinks(t)
  end

  function face.print(f, t, pre)
    local s = string.format('%s[%d:%s] { x:%d y:%d w:%d h:%d [refresh:%s]',
      t.metacel, t.id, tostring(t.face[_name]), t.x, t.y, t.w, t.h, tostring(t.refresh))
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
    if f.fillcolor then
      io.write('\n', pre, '  @@', string.format('fillcolor[%d, %d, %d, %d]', string.byte(f.fillcolor, 1, 4)))
    end
    if f.linecolor and f.linewidth then
      io.write('\n', pre, '  @@', string.format('linecolor[%d, %d, %d, %d]', string.byte(f.linecolor, 1, 4)))
    end
  end

end




