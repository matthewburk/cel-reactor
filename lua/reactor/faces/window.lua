local cel = require 'cel'

local face = cel.getface('window')
face.textcolor = false
face.color = false
face.bordercolor = cel.color.rgb(.2, .2, .2)
face.borderwidth = 4
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
      link = {cel.rcomposelinker('fill.topmargin', 'fill.margin'), {handle + 1,  border}},
    }
  }
end

face.flow = {
  minimize = cel.flows.smooth(300),
  maximize = cel.flows.smooth(300),
  restore = cel.flows.smooth(300),
}

face['%focus'] = face:new {
  bordercolor = cel.color.rgb(0, 1, 1),
}

face['%mousefocusin'] = face:new {
  bordercolor = cel.color.rgb(.4, .4, .4),
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
  face.color = cel.color.rgb(.4, .4, .4)
  face.font = cel.loadfont('arial:bold')

  face['%focus'] = face:new {
    textcolor = cel.color.rgb(.2, .2, .2),
    color = cel.color.rgb(0, 1, 1),
  }

  function face.select(face, t)
    if t.host.focus then
      face = face['%focus'] or face
    end
    return face
  end

  function face.cairodraw(_ENV, cr, f, t)
    if f.color then
      cairo.set_source_color(cr, _ENV.color)
      cairo.rectangle(cr, 0, 0, t.w, t.h)
      cairo.fill(cr)
    end

    if t.host.title and f.textcolor then
      cairo.set_source_color(cr, _ENV.textcolor)
      cairo.drawstringlt(cr, f.font, 4, 4, t.host.title)
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

do --window.client
  local face = cel.getface('window.client')
  face.color = cel.color.rgb(.2, .2, .2)
  face.bordercolor = false
  face.borderwidth = false
end

