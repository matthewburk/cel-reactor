require 'stdinit'

local celdriver = require 'celdriver'
local cel = require 'cel'

--[[
celdriver.resize(1920/1.5, 1200/1.5)

function reactor.resized()
  celdriver.resize(1920/1.5, 1200/1.5)
end
--]]

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

  local root = celdriver.root

  local sandbox = cel.mutexpanel.new(100, 100)

  local subject = nil

  local function addmodule(name)
    local button = cel.textbutton.new(name)

    function button:onclick()
      if subject then
        sandbox:clear(subject)
        subject = nil
      end

      if not subject then
        subject =  root:newroot()
        subject:link(sandbox, 'fill')
        sandbox:select(subject)

        local sub = require(name)

        --collectgarbage('stop')
        local begtime = reactor.timermillis()
        sub(subject)
        print('TIME = ', (reactor.timermillis() - begtime)/1000)
        --collectgarbage('restart')
        --collectgarbage('collect')
      else
        sandbox:select(subject)
      end


    end

    return button
  end

  local modules = cel.col {
    link = 'width';

    addmodule'baseline',
    addmodule'editbox',
    addmodule'windows',
    addmodule'col.flux',
    addmodule'col.sort',
    addmodule'col.big',
    addmodule'test.row.row',
    addmodule'test.row.minw',
    addmodule'test.row.flex',
    addmodule'test.row.big',
    addmodule'test.formations.withoutlimits',
    addmodule'test.scroll.basic',
    addmodule'test.listbox.basic',
    addmodule'test.listbox.listboxtest',
    addmodule'test.listbox.big',
    addmodule'test.listbox.sort',
    addmodule'test.formations.basic',
    addmodule'test.tabpanel.basic',
    addmodule'test.coltest',
    addmodule'test.gridtest',
    addmodule'test.menutest',
    addmodule'test.listboxtest',
    addmodule'test.windowtest',
    addmodule'test.printbuffertest',
    addmodule'tutorial.tut_cel',
    addmodule'demo.cairo.buttons',
    cel.textbutton {
      text = 'PRINT';
      onclick = function()
        cel.printdescription()
      end
    },
    cel.textbutton {
      text = 'FULL GC';
      onclick = function()
        collectgarbage('collect')
        print( tostring(collectgarbage('count') / 1024))
      end,
      onhold = function()
        collectgarbage('collect')
        print( tostring(collectgarbage('count') / 1024))
      end
    },
    cel.textbutton {
      text = 'MEM USAGE';
      onclick = function()
        print( tostring(collectgarbage('count') / 1024))
      end,
      onhold = function()
        print( tostring(collectgarbage('count') / 1024))
      end
    },
  }

  root {
    link = 'fill';
    cel.row {
      { modules, link = 'fill'; },
      { sandbox, link = 'fill'; flex=1; },
    },
  }
