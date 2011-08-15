local cel = require 'cel'

return function(root)
  local window = cel.window.new():link(root, 'edges', 5, 5):relink()

  local row = cel.row {
    gap = 10,
  }:link(window, 'edges')

  local linker = cel.composelinker('width', 'center')
  cel.text.new('hello this is some text that will hopefully wrap'):link(row, linker, nil, nil, {flex=1})
  cel.window.new():link(row, 5, 20, {flex=1}):move(10, 10)

end

