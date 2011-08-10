local cel = require 'cel'

return function(root)
  local window = cel.window.new():link(root, 'edges', 5, 5):relink()

  local row = cel.row {
    gap = 10,
  }:link(window, 'edges')

  cel.window.new(100, 100, '4'):link(row, nil, nil, nil, function() return 0, 1 end)
  cel.textbutton.new('3'):link(row, nil, nil, nil, function() return 0, 1 end)
  cel.textbutton.new('2'):link(row, nil, nil, nil, function() return 0, 1 end)
  cel.textbutton.new('1'):link(row, nil, nil, nil, function() return 0, 1 end)
end

