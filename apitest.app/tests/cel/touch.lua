local cel = require 'cel'

return function(root)
  local a = cel.panel.new(500, 500, '#ff00ff')
    :link(root, 'center')


  local b = cel.panel.new(400, 400, '#ff0000')
    :link(a, 'center')

  a.touch = 'links'

  function a:onmousemove(x, y)
    dprint('red touching at', x, y)
  end

  local c = cel.col.new(50, '#00aa00', '#0000aa')
    :link(b, 'center')

  c:addlinks {
    cel.textbutton.new('dddddddddd'),
    cel.textbutton.new('eeeeeeeeee'), 
    cel.textbutton.new('ffffffffff'),
  }

  c.touch = 'links'

  function c:onmousemove(x, y)
    dprint('green touching at', x, y)
  end
end

