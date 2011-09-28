local cel = require 'cel'

return function(_ENV)
  setfenv(1, _ENV)

  local face = cel.getface('text')
  face.textcolor = cel.color.encodef(.8, .8, .8)
  face.fillcolor = false
  face.linecolor = false
  face.linewidth = false

  face.layout = {
    padding = {
      l = function(w, h, font) return font.bbox.ymax * .1 end,
    },
  }

  function face.draw(f, t)
    if f.fillcolor then
      cairo.cel_set_source_rgba(cr, f.fillcolor)
      cairo.cel_roundrect(cr, 0, 0, t.w, t.h, f.radius)
      cairo.fill(cr)
    end

    if f.textcolor and t.text then
      cairo.cel_set_source_rgba(cr, f.textcolor)
      for i, line in ipairs(t.lines) do
        --uncomment this optimization later
        --if t.y + line.y < t.clip.b  and t.y + line.y + line.h > t.clip.t then
          cairo.cel_show_text(cr, t.font, line.penx, line.peny, t.text, line.i, line.j)
        --end
      end
    end

    if f.linewidth and f.linecolor then
      cairo.set_line_width(cr, f.linewidth)
      cairo.cel_set_source_rgba(cr, f.linecolor)
      cairo.cel_roundrect(cr, 0, 0, t.w, t.h, f.radius)
      cairo.stroke(cr)
    end

    return drawlinks(t)
  end

end




