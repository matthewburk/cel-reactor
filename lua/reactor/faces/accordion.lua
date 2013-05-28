local cel = require 'cel'

do --accordion
  local face = cel.getface('accordion')

  face.flow = {
    transition = cel.flows.linear(300),
  }
end
