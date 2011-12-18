local cel = require 'cel'

return function(_ENV)
  setfenv(1, _ENV)

  local face = cel.getface('window')
  face.textcolor = false
  face.fillcolor = false
  face.linecolor = cel.color.encodef(.2, .2, .2)
  face.linewidth = 4
  face.radius = false

  do
    local border = 5
    local handle = 24
    face.layout = {
      minw = border + (handle*3) + border,
      minh = border + handle + border,
      maxw = nil,
      maxh = nil,

      border = { size = border },
      corner = { size = border * 2 },
      handle = {
        w = handle,
        h = handle,    
        link = {'width.top', border, border},
      },
      client = {    
        w = 0,
        h = 0,
        link = {'edges.topunique', border, border + handle + 1},
      }
    }
  end

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
        cairo.extcel_set_source_color(cr, f.fillcolor)
        cairo.ext_roundrect(cr, 0, 0, t.w, t.h, f.radius)
        cairo.fill(cr)
      end

      if f.textcolor and t.text then
        
        cairo.extcel_drawstring(cr, t.font, t.penx, t.peny, t.text)
      end

      if t.host.title and f.textcolor then
        cairo.extcel_set_source_color(cr, f.textcolor)
        cairo.extcel_drawstringlt(cr, f.font, 4, 4, t.host.title)
      end

      if f.linewidth and f.linecolor then
        cairo.set_line_width(cr, f.linewidth)
        cairo.extcel_set_source_color(cr, f.linecolor)
        cairo.ext_roundrect(cr, 0, 0, t.w, t.h, f.radius)
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



