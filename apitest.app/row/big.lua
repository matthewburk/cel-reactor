local cel = require 'cel'

return function(root)
  local linker = nil
  local new = cel.label.new

  cel.window {
    w = 400, h = 400, 
    title = 'row';
    link = 'fill';

    function(window)
      window:adddefaultcontrols()
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
              new('Fus'):link(row, linker)
              new('Roh'):link(row, linker)
              new('Da'):link(row, linker)
            end
          end
        },
      },
    },
  }:link(root)

end

