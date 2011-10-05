local cel = require 'cel'

return function(_ENV)
  setfenv(1, _ENV)

  local face = cel.getface('window')
  face.textcolor = false
  face.fillcolor = false
  face.linecolor = cel.color.encodef(.2, .2, .2)
  face.linewidth = 4
  face.radius = false

  face.flow = {
    minimize = cel.flows.smooth(300),
    maximize = cel.flows.smooth(300),
    restore = cel.flows.smooth(300),
  }

  face['%focus'] = face:new {
    linecolor = cel.color.encodef(0, 1, 1),
  }

  face['%mousefocusin'] = face:new {
    linecolor = cel.color.encodef(.4, .4, .4),
  }

  function face.select(face, t)
    if t.focus then
      face = face['%focus'] or face
    elseif t.mousefocusin then
      face = face['%mousefocusin'] or face
    end
    return face
  end

  do --window.handle
    local face = cel.getface('window.handle')
    face.fillcolor = cel.color.encodef(.4, .4, .4)
    face.font = cel.loadfont('arial:bold')

    face['%focus'] = face:new {
      textcolor = cel.color.encodef(.2, .2, .2),
      fillcolor = cel.color.encodef(0, 1, 1),
    }

    function face.select(face, t)
      if t.host.focus then
        face = face['%focus'] or face
      end
      return face
    end

    function face.draw(f, t)
      if f.fillcolor then
        cairo.cel_set_source_rgba(cr, f.fillcolor)
        cairo.cel_roundrect(cr, 0, 0, t.w, t.h, f.radius)
        cairo.fill(cr)
      end

      if f.textcolor and t.text then
        
        cairo.cel_show_text(cr, t.font, t.penx, t.peny, t.text)
      end

      if t.host.title and f.textcolor then
        cairo.cel_set_source_rgba(cr, f.textcolor)
        cairo.cel_show_textlt(cr, f.font, 4, 4, t.host.title)
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

  do --window.client
    local face = cel.getface('window.client')
    face.fillcolor = cel.color.encodef(.2, .2, .2)
    face.linecolor = false
    face.linewidth = false
  end

  --[[
  do --window.border, window.corner
    cel.getface('window.border').draw = false
    cel.getface('window.border').select = false
    cel.getface('window.corner').draw = false
    cel.getface('window.corner').select = false
  end
  --]]
end



