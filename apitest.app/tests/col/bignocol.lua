local cel = require 'cel'

return function(root)
  local new = cel.label.new

  local linker = nil

  local lblw, lblh = new('test'):pget('w', 'h')

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
        cel {
          function(cel)

            for i=1, 80000 do
              new('test'):link(cel, 0, lblh*(i-1))
            end
          end
        }:resize(lblw, lblh*80000),
      },
    },
  }:link(root)

end

