local cel = require 'cel'

local function onmousedown(acel)
  if acel.ontouch then acel:ontouch() end
end

local gtk = cel.newnamespace {
  new = function(metacel, ...)
    local cel = cel[metacel].new(...)
    cel.onmousedown = onmousedown
    return cel
  end,

  compile = function(metacel, t)
    local cel = cel[metacel](t)
    cel.onmousedown = onmousedown
    return cel
  end,
}

gtk.root = app.window.root

require('gtk.faces')

gtk.newpattern = require((...)..'.pattern')

return gtk
