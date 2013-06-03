local cel = require 'cel'

return function(root)
  local w, h = 50, 10
  local n = 3

  do
    local col = cel.col.new(0, cel.colorface(app.colors.white)):link(root, 'center')

    col.__debug = true 
      cel.label.new('180'):link(col)

    local blue = cel.new(60, 30, cel.colorface(app.colors.blue))
        :link(col, 'fill.aspect', nil, nil, {face=cel.colorface(app.colors.red)})


    col:link(root, 'center')

  end

end

