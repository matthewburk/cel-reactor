local cel = require 'cel'

return function(root)

  local airspeed = cel.meters.airspeed.new()

  --[[
  local function task()
    airspeed:setaltitude(collectgarbage('count'))
    airspeed:setaltitude(10180)
    cel.doafter(10, task)
  end

  cel.doafter(10, task)
  --]]

  cel.window {
    w = 300, h = 300, title = 'airspeed',
    link = 'edges';
    airspeed,
  }:link(root)
end

