local cel = require 'cel'

local face = cel.getface('label')
face.textcolor = 'current'
face.color = false
face.bordercolor = false
face.borderwidth = false

face.layout = {
  padding = {},
}

function face.cairodraw(_ENV, cr, f, t)
  if f.color then
    cr:rectangle(0, 0, t.w, t.h)
    cr:set_source_color(_ENV.color)
    cr:fill()
  end

  if f.textcolor and t.text then
    cr:set_source_color(_ENV.textcolor)
    cr:drawstring(t.font, t.penx, t.peny, t.text)
  end

  if f.borderwidth and f.bordercolor then
    cr:set_line_width(f.borderwidth)
    cr:set_source_color(_ENV.bordercolor)
    cr:rectangle(0, 0, t.w, t.h)
    cr:stroke()
  end

  return _ENV.drawlinks(cr, t)
end



