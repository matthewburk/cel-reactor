local cel = require 'cel'

return function(root)
  
  
  local window = cel.window.new(200, 200)
    :link(root)

  local buffer = cel.printbuffer.new()
    :link(window, 'fill')

  function window:onmousedown()
    buffer:printdescription()
  end
end
