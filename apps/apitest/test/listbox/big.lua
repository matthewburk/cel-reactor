local cel = require 'cel'

return function(root)


  local linker = nil
  cel.window {
    w = 400, h = 400, 
    title = 'listbox';

    link = 'fill';
    function(self)
      self:adddefaultcontrols()
    end,
    cel.listbox {
      w = 400,
      h = 400,
      function(listbox)
        local new = cel.label.new
        local tostring = tostring
        for i=1, 1000 * 10 do          
          new('Hi ' .. i):link(listbox)
        end
        print(listbox:len())
      end
    },
  }:link(root)

  

end

