local cel = require 'cel'

return function(root)

  local new = cel.label.new

  local linker = cel.composelinker('width', 'center')
  linker = nil
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
            for i=1, 10000 do
              new('Do'):link(col, linker)
              new('Re'):link(col, linker)
              new('Mi'):link(col, linker)
              new('Fa'):link(col, linker)
              new('So'):link(col, linker)
              new('La'):link(col, linker)
              new('Ti'):link(col, linker)
              new('Do'):link(col, linker)
            end
          end
        },
      },
    },
  }:link(root)

end

