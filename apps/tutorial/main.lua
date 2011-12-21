require 'stdinit' {'../..', '../../cel'}

local cel = require 'cel'
local driver = require 'driver'
local faces = require 'faces'

local _w, _h = 1920, 1080
function reactor.load(...)
  driver.load(_w, _h)

  function driver.root:onkeydown(key, ...)
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

  require('tutorials.tutorials')(driver.root)
end

function reactor.resized()
  driver.resize(_w, _h)
end

function reactor.update()
end

function reactor.draw()
  faces.draw() 
end
