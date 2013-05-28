local cel = require 'cel'

return function(root)
  local new = cel.label.new

  local linker = nil

  cel.window {
    w = 400, h = 400, 
    title = 'row';
    link = 'fill';

    function(self)
      self:adddefaultcontrols()
    end,

    cel.scroll {
      subject = {
        fillwidth = false;
        fillheight = false;
        cel.row {
          function(row)
            for i=1, 10000 do
              new('Do'):link(row, linker)
              new('Re'):link(row, linker)
              new('Mi'):link(row, linker)
              new('Fa'):link(row, linker)
              new('So'):link(row, linker)
              new('La'):link(row, linker)
              new('Ti'):link(row, linker)
              new('Do'):link(row, linker)
            end
          end
        },
      },
    },
  }:link(root)

end

