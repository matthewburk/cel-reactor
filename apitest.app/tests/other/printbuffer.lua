local cel = require 'cel'

return function(root)
  local buffer = cel.printbuffer.new():link(cel.window.new(200, 200):link(root), 'fill')

  function buffer:onmousedown()
    buffer:printdescription()
  end
end
