local cel = require 'cel'

local face = cel.getface('grip')
face.color = cel.color.rgb(.2, .2, .2)
face.bordercolor = cel.color.rgb(.4, .4, .4)
face.borderwidth = 1

function face.select(face, t)
  if t.mousefocusin then
    face = face['%mousefocusin'] or face
    if t.isgrabbed then
      face = face['%grabbed'] or face
    end
  elseif t.isgrabbed then
    face = face['%grabbed'] or face
  end
  return face
end

do
  face['%grabbed'] = face:new {
    color = cel.color.rgb(.4, .4, .4),
    bordercolor = cel.color.rgb(0, 1, 1),
  }

  face['%mousefocusin'] = face:new {
    color = cel.color.rgb(.4, .4, .4),
    bordercolor = cel.color.rgb(0, 1, 1),
  }
  
  do
    local face = face['%mousefocusin']

    face['%grabbed'] = face:new {
      color = cel.color.rgb(0, .8, .8),
      bordercolor = cel.color.rgb(0, 1, 1),
      borderwidth = 1,
    }
  end
end

