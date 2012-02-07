local cel = require 'cel'

cel.getface('cel'):new {
  color = cel.color.rgb(1, 0, 0, .3)
}:register('@caret')

local face = cel.getface('editbox')
face.color = cel.color.rgb(1, 1, 1)

do
  local face = cel.getface('editbox.text')
  face.textcolor = 'current'
  face.selectedtextcolor = cel.color.rgb(1, 1, 1)
  face.font = cel.loadfont('arial', 28)
  face.color = false
  face.bordercolor = false
  face.borderwidth = false 

  face.layout = {
    padding = {
      fitx='default',
      l = 0, r = 2, t = 0, b = 0,
    },
  }

  function face.cairodraw(_ENV, cr, f, t)
    if f.color then
      cairo.set_source_color(cr, _ENV.color)
      cairo.rectangle(cr, 0, 0, t.w, t.h)
      cairo.fill(cr)
    end

    if f.textcolor and t.text then
      cairo.set_source_color(cr, _ENV.textcolor)
      cairo.drawstring(cr, t.font, t.penx, t.peny, t.text)
      if t.selectionx then
        cairo.save(cr)
        cairo.rectangle(cr, t.selectionx, t.selectiony, t.selectionw, t.selectionh)
        cairo.clip(cr)
        cairo.paint(cr)
        cairo.set_source_color(cr, f.selectedtextcolor)
        cairo.drawstring(cr, t.font, t.penx, t.peny, t.text)
        cairo.restore(cr)
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
end




