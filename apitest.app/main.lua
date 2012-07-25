local cel = require 'cel'

--make root cel a fixed size, it will scale, comment out and root is sized to app.window size
app.window.root:setlimits(1920/2, nil, 800, nil)

function app.window:draw()
  app.window.root:draw()
end

local plots = cel.window {
  w = 400, h = 400,  
  function(window)
    local drawtime = 0

    function app.window:ondraw(drawcycletime)
      drawtime = math.max(drawtime, drawcycletime)
    end

    local latency = cel.plot.new(0, 0, function(time)
      local r = drawtime
      drawtime = 0
      return r
    end)

    latency:setrange(0, 50, 10)
    latency:setdomain(-5000, 0, 1000)
    latency:setpollinterval(16)
    latency:start()

    local memcount = cel.plot.new(0, 0, function(time) return collectgarbage('count') end)
    memcount:setrange(0, 1024*8, 1024)
    memcount:setdomain(-60000 , 0, 5000) 
    memcount:setpollinterval(50)
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

function app.window:onkeydown(key, ...)
  if key == 'space' then
    cel.printdescription()
  elseif key == 'f1' then
    app.window:fullscreen(true)
  elseif key == 'f2' then
    app.window:fullscreen(false)
  elseif key == 'escape' then
    reactor.quit()
  elseif key == 'f9' then
    plots:link(app.window.root, 'center'):relink() 
  end
end

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
      subject =  cel.new()
      subject:link(sandbox, 'fill')
      sandbox:select(subject)

      local sub = require(name)
      local begtime = reactor.timermillis()
      sub(subject)
      dprint('TIME = ', (reactor.timermillis() - begtime)/1000)
    else
      sandbox:select(subject)
    end
  end

  return button
end

local modules = cel.col {
  link = 'width';

  addmodule'text.wraplong',
  addmodule'brokencol',
  addmodule'celcoroutine',
  addmodule'slider',
  addmodule'cairo.buttons',
  addmodule'menu',
  addmodule'baseline',
  addmodule'editbox',
  addmodule'windows',
  addmodule'printbuffer',
  addmodule'col.flexandminh',
  addmodule'col.flux',
  addmodule'col.sort',
  addmodule'col.big',
  addmodule'col.randomaccess',
  addmodule'row.randomaccess',
  addmodule'row.big',
  addmodule'row.minw',
  addmodule'row.flex',
  addmodule'col.withoutlimits',
  addmodule'row.withoutlimits',
  addmodule'scroll.basic',
  addmodule'listbox.basic',
  addmodule'listbox.big',
  addmodule'listbox.sort',
  addmodule'listbox.listboxtest',

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
}

app.window.root:addlinks {
  link = 'fill';
  cel.row {
    { modules, link = 'fill'; },
    { sandbox, link = 'fill'; flex=1; },
  },
}
