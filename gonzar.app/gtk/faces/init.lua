local cel = require 'cel'

do --scroll
  local face = cel.getface('scroll')

  face.flow = {
    scroll = cel.flows.linear(100);
  }

  face.layout = {
    xbar = {
      face=false,
      show=false,
      track= {
        thumb={},
      },
    },
    ybar = {
      face=false,
      show=false,
      track= {
        thumb={},
      },
    },
  }
end
