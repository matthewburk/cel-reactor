local cel = require 'cel'

local face = cel.getface('window')
face.textcolor = false
face.color = false
face.bordercolor = app.colors.gray2
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
  bordercolor = app.colors.gray2,
}

face['%mousefocusin'] = face:new {
  bordercolor = app.colors.gray4,
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
  face.color = app.colors.gray2
  face.font = cel.loadfont('arial:bold')
  face.textcolor = app.colors.oceanblue

  face['%focus'] = face:new {
    textcolor = app.colors.gray2,
    color = app.colors.oceanblue,
  }

  function face.select(face, t)
    if t.host.focus then
      face = face['%focus'] or face
    end
    return face
  end

  function face.cairodraw(_ENV, cr, f, t)
    if f.color then
      cr:set_source_color(_ENV.color)
      cr:rectangle(0, 0, t.w, t.h)
      cr:fill()
    end

    if t.host.title then -- and f.textcolor then
      cr:set_source_color(_ENV.textcolor)
      cr:drawstringlt(f.font, 4, 4, t.host.title)
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

do --window.client
  local face = cel.getface('window.client')
  face.color = app.colors.themecolor
  face.bordercolor = false
  face.borderwidth = false
end

