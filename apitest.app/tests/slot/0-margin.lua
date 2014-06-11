local cel = require 'cel'

return function(root)
  local slot = cel.slot.new(10, 10, '#ff0000')
  local link = cel.new(15, 15, '#00ff00')

  slot:setmargins(10)
  link:link(slot, 'right')

  local window = cel.window.new(300, 300)
    :link(root)

  slot:link(window, 'fill')

  local col = cel.col {
    '1',
    '2',
    '3',
  }:link(window, 'center')

  col:setslotface(2, '#88bbaa')
end

