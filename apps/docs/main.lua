require 'stdinit'

local celdriver = require 'celdriver'
local cel = require 'cel'

function reactor.keydown(key, ...)
  celdriver.keydown(key, ...)
  if key == 'space' then
    cel.printdescription()
  elseif key == 'f1' then
    reactor.fullscreen(true)
  elseif key == 'f2' then
    reactor.fullscreen(false)
  elseif key == 'escape' then
    reactor.quit()
  end
end

--require('diagrams.coldiagram'):link(celdriver.root, 'center')
require('diagrams.basiccol'):link(celdriver.root, 'fill')
