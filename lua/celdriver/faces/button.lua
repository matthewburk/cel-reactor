local cel = require 'cel'

return function(_ENV)
  setfenv(1, _ENV)

  local face = cel.getface('button')

  face.textcolor = cel.color.rgb(.8, .8, .8)
  face.fillcolor = cel.color.rgb(.2, .2, .2)
  face.linecolor = cel.color.rgb(.4, .4, .4)
  face.linewidth = 1

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

  do
    face['%pressed'] = face:new {
      fillcolor = cel.color.tint(face.fillcolor, .5),
      linecolor = cel.color.rgb(0, 1, 1),
    }

    face['%mousefocusin'] = face:new {
      fillcolor = cel.color.tint(face.fillcolor, .5),
      linecolor = cel.color.rgb(0, 1, 1),
    }
    
    do
      local face = face['%mousefocusin']

      face['%pressed'] = face:new {
        textcolor = cel.color.rgb(.2, .2, .2),
        fillcolor = cel.color.rgb(0, .8, .8),
        linecolor = cel.color.rgb(0, 1, 1),
        linewidth = 2,
      }
    end
  end
end


