local cel = require 'cel'

cel.getface('cel'):new {
  color = cel.color.rgb(1, 0, 0, .3)
}:register('@caret')

local face = cel.getface('editbox')
face.color = cel.color.rgb(1, 1, 1)

do
  local face = cel.getface('editbox.text')
  face.textcolor = cel.color.rgb(0, 0, 0)
  face.selectedtextcolor = cel.color.rgb(1, 1, 1)
  face.font = cel.loadfont('arial', 28)
  face.color = false 
  face.bordercolor = false
  face.borderwidth = false 

  face.layout = {
    padding = {
      l = 0, r = 2, --make room for caret at end
      t = 0, b = 0,
    },
  }

  function face.cairodraw(_ENV, cr, f, t)
    if f.color then
      cr:set_source_color(_ENV.color)
      cr:rectangle(0, 0, t.w, t.h)
      cr:fill()
    end

    if f.textcolor and t.text then
      cr:set_source_color(_ENV.textcolor)
      cr:drawstring(t.font, t.penx, t.peny, t.text)
      if t.selectionx then
        cr:save()
        cr:rectangle(t.selectionx, t.selectiony, t.selectionw, t.selectionh)
        cr:clip()
        cr:paint()
        cr:set_source_color(f.selectedtextcolor)
        cr:drawstring(t.font, t.penx, t.peny, t.text)
        cr:restore()
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
end




