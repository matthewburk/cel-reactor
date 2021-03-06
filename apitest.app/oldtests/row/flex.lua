local cel = require 'cel'

return function(root)
  local col = cel.col.new()

  col.debug = false 

  print('root', root.w, root.h)
  col:beginflux()

  for i = 1, 150 do
          cel.row {
            {flex=1; 'one',},
            {flex=1; 'two',},
            {flex=2;  link='width', cel.text.new([[Do Re Mi Fa So La Ti Do --]]):wrap('word'),},
            {flex=1; 'four',},
            {flex=1; 'five',},
            {flex=1; 'six',},
            {flex=1; 'seven',},
            {flex=1; 'eight',},
            {flex=1; 'nine',},
            {flex=1; 'ten',},
          }:link(col, 'width')
        end

  local window = cel.window.new():link(root, 'fill.margin', 5, 5):relink()

  col:link(window, 'fill.margin', 5, 5)

  col:endflux()

end

