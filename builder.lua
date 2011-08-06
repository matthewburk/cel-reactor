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

local celdriver = require 'celdriver'
local kit = require 'kit'

local root = kit.root

kit.root {
  kit.row { link = 'edges';
    { minw=100; require 'kit.sandbox' },
    { weight=1; require 'kit.tools' },
  },
}
