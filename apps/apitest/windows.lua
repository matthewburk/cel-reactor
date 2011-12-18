local cel = require 'cel'

return function(root)

  --[[
  local function task()
    airspeed:setaltitude(collectgarbage('count'))
    airspeed:setaltitude(10180)
    cel.doafter(10, task)
  end

  cel.doafter(10, task)
  --]]

  local bigcel = cel.new(5000, 5000)

  for i = 1, 50 do 
    cel.window.new(math.random(100, 500), math.random(100, 500), 'a window'):link(bigcel, math.random(1, 2000), math.random(1, 2000))
  end

  cel.scroll {
    w = 300, h = 300, title = 'windows',    
    subject = bigcel,
  }:link(root, 'edges')
end

