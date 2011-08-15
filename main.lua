do 
  local _print = print
  function print(...)
    _print(...) io.flush() 
  end

  package.path = 'cel/?.lua;cel/?/init.lua;' .. package.path

  if jit then
    jit.opt.start( 'maxside=10', 'hotloop=5', 'loopunroll=32', 'maxsnap=250', 'tryside=2')
    print('JIT')
  else
    print('NO JIT')
  end
end

local celdriver = require 'celdriver'
local cel = require 'cel'
require 'celfaces'

function celdriver.load(...)
  local root = celdriver.root

  local function laodfactory(s)
    local button = cel.textbutton.new(s)
    function button:onclick()
      app.changefactory(s)
    end
  end
  local function factorypanel()
    cel.col {
      loadfactory('cel'),
      loadfactory('cel.button'),
      loadfactory('cel.label'),
      loadfactory('cel.text'),
      loadfactory('cel.textbutton'),
      loadfactory('cel.window'),
      loadfactory('cel.row'),
      loadfactory('cel.col'),
      loadfactory('cel.scroll'),
      loadfactory('cel.panel'),
      loadfactory('cel.mutexpanel'),
    },
  end

end





