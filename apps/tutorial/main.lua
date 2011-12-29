require 'stdinit' {'../..', '../../cel'}

local celdriver = require 'celdriver'
local cel = require 'cel'

local _w, _h = 1920, 1080

function reactor.load(...)
  celdriver.resize(_w, _h)
  require('tutorials.tutorials')(celdriver.root)
end

function reactor.resized()
  celdriver.resize(_w, _h)
end

function reactor.draw()
  celdriver.draw() 
end

function celdriver.root:onkeydown(key, ...)
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
