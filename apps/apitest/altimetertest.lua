local cel = require 'cel'

return function(root)

  local altimeter = cel.meters.altimeter.new()

  local function task()
    altimeter:setaltitude(collectgarbage('count'))
    cel.doafter(10, task)
  end

  cel.doafter(10, task)

  cel.window {
    w = 300, h = 300, title = 'altimeter',
    link = 'edges';
    altimeter,
  }:link(root)
end

