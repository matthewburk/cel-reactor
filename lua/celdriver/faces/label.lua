local cel = require 'cel'

local face = cel.getface('label')
face.textcolor = 'current'
face.color = false
face.bordercolor = false
face.borderwidth = false

face.layout = {
  padding = {
    l = 1,
    t = 1,
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
    cairo.drawstring(cr, t.font, t.penx, t.peny, t.text)
  end

  if f.borderwidth and f.bordercolor then
    cairo.set_line_width(cr, f.borderwidth)
    cairo.set_source_color(cr, _ENV.bordercolor)
    cairo.rectangle(cr, 0, 0, t.w, t.h)
    cairo.stroke(cr)
  end

  return _ENV.drawlinks(cr, t)
end



