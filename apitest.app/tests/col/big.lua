local cel = require 'cel'

return function(root)
  local new = cel.label.new

  local linker = nil
  local tostring = tostring

  cel.window {
    w = 400, h = 400, 
    title = 'col';
    link = 'fill';

    function(self)
      self:adddefaultcontrols()
    end,

    cel.scroll {
      subject = {
        fillwidth = false;
        fillheight = false;
        cel.col {
          function(col)
            for i=1, 80000 do
              new('test'):link(col, linker)
            end
          end
        },
      },
    },
  }:link(root)

end

