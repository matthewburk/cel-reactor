local cel = require 'cel'
local socket = require 'socket'
print(socket._VERSION)

local udp = socket.udp()
--dprint(udp:setoption('ip-multicast-loop', true))
--dprint(udp:setoption('broadcast', true))
local count = 0

return function(root)

  count=count+1
  udp:sendto('join test'..count, "239.255.1.1", 8899)


  local button = cel.textbutton.new('debugjoins'):link(root)

  function button:onclick()
    cel.debugjoins()
  end

  local window = cel.window.new(300, 300)
    :link(root, 'center')
    :relink()
    :adddefaultcontrols()
    :settitle('window')

  local frame = cel.new(400, 400, cel.colorface(cel.color.rgb(1, 0, 0)))
    :link(root, 'right.center', 10)

  local j = cel.window.new(100, 100)
    :join(window, 'size')
    :adddefaultcontrols()
    :settitle('j')


  local button = cel.textbutton.new('bottom:top'):link(j, 'center.top')

  function button:onclick()
    j:join(window, 'bottom:top')
  end

  local button2 = cel.textbutton.new('size but bigger'):join(button, 'top:bottom')

  function button2:onclick()
    j:join(window, 'size', 10, 10)
    --j:relink('top')
  end

  cel.col {
    j, 
    {link='center',
    'in a col',
  },
  }:link(frame, 'width', 10)

  local prev = window
  for i=1, 5 do
    prev = cel.window.new():join(prev, 'top:bottom'):adddefaultcontrols()
  end

  dprint(j.w, j.h)
  cel.window.new():join(j, 'size'):adddefaultcontrols()
  --window:link(frame)
  --


  do --col join
    local window = cel.window {
      title = 'col join test'
    }:link(root)

    local col = cel.col{
      cel.window.new():settitle('A'),
      cel.window.new():settitle('B'),
      cel.window.new():settitle('C'),
    }
   
    --[[ does not work, need to wormhole across cels
    cel.row {
      col,
    }:link(window, 'center')
    --]]
    --

    cel.slot {
      link='center', 
      col,
    }:link(window, 'fill')

    local label = cel.label.new('joined to B'):join(col:get(2), 'bottom:top')
  end
end

