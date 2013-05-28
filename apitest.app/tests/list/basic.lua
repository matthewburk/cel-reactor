local cel = require 'cel'

return function(root)

  local items = cel.list.new()

  for i = 1, 20 do
    local btn = cel.textbutton.new('item '..i):link(items)
    items:setslotface(btn, cel.colorface(app.colors.green))
  end

  
  root:addlinks {
    link = {nil, 20, 20},

    cel.window {
      w = 200, 
      h = 400, 
      title = 'A simple list';

      link = 'fill',

      cel.scroll {
        subject = {items, fillwidth=true},
      },

    }:adddefaultcontrols(),
  }

end

