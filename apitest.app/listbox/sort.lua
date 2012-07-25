local cel = require 'cel'

return function(root)

  local function comp(b1, b2)
    return b1:gettext() < b2:gettext()
  end

  local function rcomp(b1, b2)
    return b2:gettext() < b1:gettext()
  end

  cel.window {
    w = 400, h = 400, 
    title = 'listbox';

    link = 'fill';

    function(self)
      self:adddefaultcontrols()
    end,

    cel.listbox {
      onmousedown = function(listbox)
        listbox:sort(rcomp)
      end,

      onmouseup = function(listbox)
        listbox:sort(comp)
      end,

      function(listbox)
        local new = cel.label.new
        for i=1,30 do
          new('Do'):link(listbox, linker)
          new('Re'):link(listbox, linker)
          new('Mi'):link(listbox, linker)
          new('Fa'):link(listbox, linker)
          new('So'):link(listbox, linker)
          new('La'):link(listbox, linker)
          new('Ti'):link(listbox, linker)
        end
        print(listbox:len())
      end
    },
  }:link(root)

  

  
  

end

