local cel = require 'cel'

return function(root)
  local b = cel.new(200, 30, cel.colorface(cel.color.rgb(1, 0, 0)))

  cel.col { 
    link={'center.top', nil, 4},
    cel.textbutton.new('MODE'):setlimits(200),
    {
      link = function(hw, hh, x, y, w, h, ...)
        --print('blinker', hw, hh, x, y, w, h)
        --print('>>>', debug.traceback())
        return cel.getlinker('center.top')(hw, hh, x, y, w, h, ...)
      end,
      b,
    }
  }:link(root, 'center')

  cel.row {
    cel.textbutton {
      text = '250\195\177',
      onclick = function(btn)
        print('##250')
        b:setlimits(250, 250)
      end,
    },

    cel.textbutton {
      text = '200',
      onclick = function(btn)
        print('##200')
        b:setlimits(200, 200)
      end,
    },

    cel.textbutton {
      text = '150',
      onclick = function(btn)
        print('##150')
        b:setlimits(150, 150)
      end,
    },
  }:link(root, 'center.top')

end

