local cel = require 'cel'

return function(_ENV)
  setfenv(1, _ENV)
  local face = cel.getface('cel'):new()
  face.fillcolor = cel.color.encodef(1, 1, 1)
  face.linecolor = cel.color.encodef(.4, .4, .4)
  face.linewidth = 1
  face:register('@marker')
end

