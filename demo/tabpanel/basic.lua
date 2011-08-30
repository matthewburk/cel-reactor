local cel = require 'cel'

local function newtabhandle(tabs, name)
  local button = cel.textbutton.new(name)
  function button:onmousedown()
    tabs:selecttab(name)
  end
  return button
end

local function newtabsubject(name)
  local window = cel.window.new(300, 300, name)
  return window
end

return function(root)
  root {
    link = {nil, 40, 40};
    cel.window {
      w = 400, h = 400, title = 'tabs';

      function(window)
        window:adddefaultcontrols()

        local tabs = cel.tabpanel.new()

        tabs:link(window, 'edges')

        tabs:addtab('a', newtabhandle(tabs, 'a'), newtabsubject('a') )
        tabs:addtab('b', newtabhandle(tabs, 'b'), newtabsubject('b') )
        tabs:addtab('c', newtabhandle(tabs, 'c'), newtabsubject('c') )
      end,
    }
  }

end

