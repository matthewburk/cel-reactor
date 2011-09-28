local cel = require 'cel'

return function(_ENV)
  setfenv(1, _ENV)

  local face = cel.getface('label')
  face.textcolor = cel.color.encodef(.8, .8, .8)
  face.fillcolor = false
  face.linecolor = false
  face.linewidth = false

  face.layout = {
    padding = {
      l = 1,
      t = 1,
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
      cairo.cel_show_text(cr, t.font, t.penx, t.peny, t.text)
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



