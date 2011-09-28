local cel = require 'cel'

require 'cel.textbutton'

return function(_ENV)
  setfenv(1, _ENV)

  local face = cel.getface('textbutton')

  face.layout = {
    padding = {
      fitx = 'bbox',
      l = function(w, h, font) return font.bbox.ymax * .5 end, --TODO need font em
      t = function(w, h, font) return h*.35 end,
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

  do
    face['%pressed'] = face:new {
      fillcolor = cel.color.tint(.5, face.fillcolor),
      linecolor = cel.color.encodef(0, 1, 1),
    }

    face['%mousefocusin'] = face:new {
      fillcolor = cel.color.tint(.5, face.fillcolor),
      linecolor = cel.color.encodef(0, 1, 1),
    }
    
    do
      local face = face['%mousefocusin']

      face['%pressed'] = face:new {
        textcolor = cel.color.encodef(.2, .2, .2),
        fillcolor = cel.color.encodef(0, .8, .8),
        linecolor = cel.color.encodef(0, 1, 1),
        linewidth = 2,
      }
    end
  end
end


