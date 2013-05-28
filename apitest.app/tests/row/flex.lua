local cel = require 'cel'

return function(root)
  local col = cel.col.new(0, cel.colorface(app.colors.green))

  col:beginflux()

  col.__debug = true

  for i = 1, 1 do
          cel.row { face=cel.colorface(app.colors.gray5),
            --__debug = true,


            {flex=1; link='width',
              maxw=true,
              face=cel.colorface(app.colors.red),
              cel.text.new([[Do Fa So La Ti Do --]]):wrap('word'),
            },

            {flex=1; link='width', 
              --maxw=true, --flex allocation does not work with max correctly
              face=cel.colorface(app.colors.blue),
              'one', 
            },
            {flex=1; 
              --minw=true, 
              --maxw=true, 
              face=cel.colorface(app.colors.blue),
              'three', 
            },

            --[[
            {flex=1; 'four',},
            {flex=1; 'five',},
            {flex=1; 'six',},
            {flex=1; 'seven',},
            {flex=1; 'eight',},
            {flex=1; 'nine',},
            {flex=1; 'ten', face=cel.colorface(app.colors.blue),},
            --]]
          }:link(col, 'width')
        end

  local window = cel.window.new():link(root, 5, 5):relink():resize(500, 500)

  col:link(window, 'fill.margin', 5, 5)

  col:endflux()

  collectgarbage('collect')
  dprint(collectgarbage('count'))
end

