require 'stdinit'
require 'strict'

local celdriver = require 'celdriver'
local cel = require 'cel'

--[[
celdriver.resize(1920/2, 1080/2)

function reactor.resized()
  celdriver.resize(1920/2, 1080/2)
end
--]]

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


do
  local face = cel.getface('cel'):new {
  }:register('@grid')

  face.surface = cairo.surface.create(100, 100)
  do
    local cr = cairo.create(face.surface)
    cr:arc(50, 50, 45, 0, math.pi*2)
    cairo.set_source_rgb(cr, 0, 1, 0)
    cairo.set_line_width(cr, 10)
    cairo.stroke(cr)
  end
  
  function face.cairodraw(_ENV, cr, f, t)
    cairo.set_source_surface(cr, f.surface, 0, 0)
    cairo.rectangle(cr, 0, 0, t.w, t.h)
    cairo.fill(cr)
  end
end

local chooser = cel.row {
  {flex=0;
    cel.textbutton {
      text = 'imageborder';
    }
  },
  function(row)
    local client = cel.new():link(row, 'fill', nil, nil, {flex=1})
    row.__link = client
  end
}:link(celdriver.root, 'fill')

cel.new(200, 200, '@grid'):link(chooser, 'fill.margin', 10)

