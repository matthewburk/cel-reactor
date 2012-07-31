local cel = require 'cel'

--require 'cel.textbutton'

local face = cel.getface('textbutton')

face.textcolor = 'current'
face.color = 'current'
face.bordercolor = cel.color.rgb(.4, .4, .4)
face.borderwidth = 1

face.layout = {
  wrap = 'line',
  justification = 'center',
  padding = {
    fitx = 'bbox',
    l = function(w, h, font) return font.ascent * .5 end, --TODO need font em
    t = function(w, h, font) return h*.35 end,
  },
}

function face.cairodraw(_ENV, cr, f, t)

  if f.textcolor and t.text then
    cr:set_source_color(_ENV.textcolor)
    for i, line in ipairs(t.lines) do
      --uncomment this optimization later
      --if t.y + line.y < t.clip.b  and t.y + line.y + line.h > t.clip.t then
      cr:drawstring(t.font, line.penx, line.peny, line.text)
      --end
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

do
  face['%pressed'] = face:new {
    color = cel.color.tint(face.color, .5),
    bordercolor = cel.color.rgb(0, 1, 1),
  }

  face['%mousefocusin'] = face:new {
    color = cel.color.tint(face.color, .5),
    bordercolor = cel.color.rgb(0, 1, 1),
  }
  
  do
    local face = face['%mousefocusin']

    face['%pressed'] = face:new {
      textcolor = cel.color.rgb(.2, .2, .2),
      color = cel.color.rgb(0, .8, .8),
      bordercolor = cel.color.rgb(0, 1, 1),
      borderwidth = 2,
    }
  end
end

function face.select(face, t)
  if t.mousefocusin then
    face = face['%mousefocusin'] or face
    if t.pressed then
      face = face['%pressed'] or face
    end
  elseif t.pressed then
    face = face['%pressed'] or face
  end
  return face
end


