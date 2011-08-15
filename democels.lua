do 
  local _print = print
  function print(...)
    _print(...) io.flush() 
  end

  package.path = 'cel/?.lua;cel/?/init.lua;' .. package.path
  print(package.path)
  print(package.cpath)

  if jit then
    jit.opt.start( 'maxside=10', 'hotloop=5', 'loopunroll=32', 'maxsnap=250', 'tryside=2')
    print('JIT')
  else
    print('NO JIT')
  end
end

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

  local function addmodule(name)
    local button = cel.textbutton.new(name)
    function button:onclick()

      if self.subject then
        sandbox:clear(self.subject)
        self.subject = nil
      end

      if not self.subject then
        self.subject =  root:newroot() 
        sandbox:show(self.subject, 'edges')

        local sub = require(name)

        local begtime = reactor.timermillis()
        sub(self.subject)
        print('TIME = ', (reactor.timermillis() - begtime)/1000)
      else
        sandbox:show(self.subject, 'edges')
      end


    end

    return button
  end

  local modules = cel.sequence.y {
    {link = 'width'; addmodule'test.sequence.basic'},
    {link = 'width'; addmodule'demo.col.basic'},
    {link = 'width'; addmodule'demo.tabpanel.basic'},
    {link = 'width'; addmodule'demo.listbox.basic'},
    {link = 'width'; addmodule'demo.listbox.listboxtest'},
    {link = 'width'; addmodule'test.sequencetest'},
    {link = 'width'; addmodule'test.rowtest'},
    {link = 'width'; addmodule'test.gridtest'},
    {link = 'width'; addmodule'test.menutest'},
    {link = 'width'; addmodule'test.listboxtest'},
    {link = 'width'; addmodule'test.windowtest'},
    {link = 'width'; addmodule'test.printbuffertest'},
    {link = 'width'; addmodule'tutorial.tut_cel'},
    {link = 'width';
      cel.textbutton {
        text = 'PRINT';
        onclick = function()
          cel.printdescription()
        end
      }
    };
    {link = 'width';
      cel.textbutton {
        text = 'FULL GC';
        onclick = function()
          collectgarbage('collect')
          print( tostring(collectgarbage('count') / 1000))
        end
      }
    };
    {link = 'width';
      cel.textbutton {
        text = 'MEM USAGE';
        onclick = function()
          print( tostring(collectgarbage('count') / 1000))
        end
      }
    };
  }

  root {
    cel.row {
      link = 'edges';
      { link = 'edges';
        modules 
      },
      { link = 'edges'; flex=1,
        sandbox,
      },
    },
  }
end




