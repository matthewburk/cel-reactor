setfenv(1, setmetatable({}, {__index = _G}))

local cel = require 'cel'

local screen = cel.new()

function screen:onmousedown(button, x, y, intercepted)
  if intercepted then return end
  if button == cel.mouse.buttons.left then
    --link new
    return true
  elseif button == cel.mouse.buttons.right then
    --select host
    return true
  end
end

--a menu is provided to move to a differnt host, breadcrumb type
--to drill down use the expode panel, which will popup off teh last breadcrumb

function screen:show(acel)

  cel.peekdescription(acel)

  do
    local _refresh = acel.refresh
    function acel:refresh()
      screen:refresh()
    end
  end

  --the cel remains linked to its host, but is visible on the screen, its host is not
  --this is the host for any new cels added to the screen
  --
  --the screen should be able to zoom in/out
  --when it is dismissed it is 
  --will render only this cel
end

--screen should refresh its description with every 
