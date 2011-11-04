local cel = require 'cel'

return function(_ENV)
  setfenv(1, _ENV)

  local face = cel.getface('cel'):new {
    fillcolor = cel.color.encodef(1, 0, 0, .3)
  }:register('@caret')

  local face = cel.getface('editbox')
  face.fillcolor = cel.color.encodef(1, 1, 1)

  do
    local face = cel.getface('editbox.text')
    face.textcolor = cel.color.encodef(0, 0, 0)
    face.selectedtextcolor = cel.color.encodef(1, 1, 1)
    face.font = cel.loadfont('arial', 28)
    face.fillcolor = false
    face.linecolor = cel.color.encodef(0, 1, 0)
    face.linewidth = false 

    face.layout = {
      padding = {
        fitx='default',
        l = 0, r = 2, t = 0, b = 0,
      },
    }

    function face.draw(f, t)
      if f.fillcolor then
        cairo.cel_set_source_rgba(cr, f.fillcolor)
        cairo.cel_roundrect(cr, 0, 0, t.w, t.h, f.radius)
        cairo.fill(cr)
      end

      if f.textcolor and t.text then
        --cairo.set_font_options(cr, 'gray')
        cairo.cel_set_source_rgba(cr, f.textcolor)
        cairo.cel_show_text(cr, t.font, t.penx, t.peny, t.text)
        if t.selectionx then
          cairo.save(cr)
          cairo.rectangle(cr, t.selectionx, t.selectiony, t.selectionw, t.selectionh)
          cairo.clip(cr)
          cairo.paint(cr)
          cairo.cel_set_source_rgba(cr, f.selectedtextcolor)
          cairo.cel_show_text(cr, t.font, t.penx, t.peny, t.text)
          cairo.restore(cr)
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

end




