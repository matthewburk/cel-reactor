require 'stdinit'

local celdriver = require 'celdriver'
local cel = require 'cel'

---[[
celdriver.resize(1920/2, 1080/2)


function reactor.resized()
  celdriver.resize(1920/2, 1080/2)
end
--]]

_G.root = celdriver.root
_G.drawtime = 0

do
  local lastdrawms = 0
  function reactor.draw()    
    celdriver.draw()
    local ms = reactor.timermillis()
    _G.drawtime = math.max(_G.drawtime, ms-lastdrawms)
    lastdrawms = ms
  end
end

local plots = cel.window {
  w = 400, h = 400,  
  function(window)
    local latency = cel.plot.new(0, 0, function(time)
      local r = _G.drawtime
      _G.drawtime = 0
      return r or 1 
    end)

    latency:setrange(0, 50, 10)
    latency:setdomain(-5000, 0, 1000)
    latency:setpollinterval(16)
    latency:start()

    local memcount = cel.plot.new(0, 0, function(time) return collectgarbage('count') end)
    memcount:setrange(0, 1024*128, 8192)
    memcount:setdomain(-60000 , 0, 5000) 
    memcount:setpollinterval(200)
    memcount:start()


    cel.col {
      link = 'fill';
      'latency',
      { flex=1; minh=0;
        latency,
      },
      'collectgarbage "count"',
      { flex=1; minh=0;
        memcount,
      }
    }:link(window, 'fill')
  end
}

function reactor.keydown(key, ...)
  celdriver.keydown(key, ...)
  if key == 'space' then
    cel.printdescription()
  elseif key == 'f1' then
    reactor.fullscreen(true)
  elseif key == 'f2' then
    reactor.fullscreen(false)
  elseif key == 'f9' then
    plots:link(celdriver.root, 'center'):relink() 
  elseif key == 'escape' then
    reactor.quit()
  end
end

require 'cairo.star'
