do 
  local _print = print
  function print(...)
    _print(...) io.flush() 
  end
end

for i, v in ipairs{'..', '../cel'} do
  package.path = v .. '/?.lua;' .. v .. '/?/init.lua;' .. package.path
end

if jit then
  print('JIT')
  jit.opt.start( 
    'maxside=10',
    'hotloop=5',
    'loopunroll=32',
    'maxsnap=500',
    'tryside=5'
    )
else
  print('NO JIT')
end

local lfs = require 'lfs'
local cel = require 'cel'
local driver = require 'driver'
local faces = require 'faces'

function reactor.load(...)
  driver.load(reactor.w, reactor.h)

  local root = driver.root

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
        subject:link(sandbox, 'edges')
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

    addmodule'editbox',
    addmodule'windows',
    addmodule'altimetertest',
    addmodule'test.document.basic',
    addmodule'test.col.flux',
    addmodule'test.col.sort',
    addmodule'test.col.big',
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
    link = 'edges';
    cel.row {
      { modules, link = 'edges'; },
      { sandbox, link = 'edges'; flex=1; },
    },
  }

  --[[
  local function memusage()
    print( tostring(collectgarbage('count') / 1024))
    cel.doafter(100, memusage)
  end
  cel.doafter(1000, memusage)
  --]]

  do
    local _update = reactor.update
    
  end

  --[[
  for name in lfs.dir(lfs.currentdir()) do
    print(name)
  end
  --]]

  function root:onkeydown(key, ...)
    if key == ' ' then
      cel.printdescription()
    elseif key == 'f1' then
      reactor.fullscreen(true)
    elseif key == 'f2' then
      reactor.fullscreen(false)
    elseif key == 'escape' then
      reactor.quit()
    end
  end
end

function reactor.resized()
  driver.resize(reactor.w, reactor.h)
end

function reactor.update()
end

function reactor.draw()
  reactor.graphics.pushstate2d(reactor.w, reactor.h)
  reactor.graphics.setcolor(1, 1, 1)
  faces.draw(cel.describe())
  reactor.graphics.popstate()
end


