local cel = require 'cel'

local face = cel.getface('textbutton')

face.textcolor = 'current'
face.color = 'current'
face.bordercolor = app.colors.themebordercolor
face.borderwidth = 2

face.layout = {
  wrap = 'line',
  justification = 'center',
  padding = {
    l=function(w, h, font) return font.metrics['M'].advance end,
    t = function(w, h, font) return h*.35 end,
  },
}

function face.cairodraw(_ENV, cr, f, t)
 
  local bw = f.borderwidth and f.borderwidth/2 or 0
  --cr:roundrect(1+bw, 1+bw, t.w-bw-bw-2, t.h-bw-bw-2, (math.min(t.w, t.h)-2)/2)
  cr:rectangle(1+bw, 1+bw, t.w-bw-bw-2, t.h-bw-bw-2)
  cr:set_source_color(_ENV.color)
  cr:fill_preserve()

  if f.textcolor and t.text then
    cr:set_source_color(_ENV.textcolor)
    for i, line in ipairs(t.lines) do
      cr:drawstring(t.font, line.penx, line.peny, line.text)
    end
  end

  if f.borderwidth and f.bordercolor then
    cr:set_line_width(f.borderwidth)
    cr:set_source_color(_ENV.bordercolor)
    cr:stroke()
  else
    cr:new_path()
  end

  return _ENV.drawlinks(cr, t)
end

do
  face['%pressed'] = face:new {
    color = app.colors.themecomplementlight,
    bordercolor = app.colors.themebordercolor,
  }

  face['%mousefocusin'] = face:new {
    color = app.colors.themecomplementlight,
  }
  
  do
    local face = face['%mousefocusin']

    face['%pressed'] = face:new {
      textcolor = app.colors.themetextcolor,
      color = app.colors.themecomplement,
      bordercolor = app.colors.themebordercolor,
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


