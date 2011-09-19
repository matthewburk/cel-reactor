do 
  local _print = print
  function print(...)
    _print(...) io.flush() 
  end

  package.path = 'cel/?.lua;cel/?/init.lua;' .. package.path
  print('PATH=', package.path)
  print('CPATH=', package.cpath)

  if jit then
    jit.opt.start( 
      'maxside=10',
      'hotloop=5',
      'loopunroll=32',
      'maxsnap=500',
      'tryside=5'
      )
    print('JIT')
  else
    print('NO JIT')
  end
end

local lfs = require 'lfs'

local celdriver = require 'celrender'
local cel = require 'cel'
local app

do
  local cels = {}

  app = cel.newnamespace {
    new = function(metacel, ...)
      if metacel ~= 'cel' then
        return cel[metacel].new(...)
      else
        return cel.new(...)
      end
    end,

    compile = function(metacel, t)
      if metacel ~= 'cel' then
        local ret = cel[metacel](t)
        if t.__name then cels[t.__name] = ret end
        return ret
      else
        return cel(t)
      end
    end,
  }

  function app.find(name)
    return cels[name]
  end
end


function celdriver.load(...)
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
    local i = 0
    function reactor.update(...)
      _update(...)
      i = i + 1

      if i % 10000 == 0 then
        print( tostring(collectgarbage('count') / 1024))
        i = 0
      end
    end
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




