local cel = require 'cel'

return function(root)

  local col = cel.col.new()

  col:flux(function()
    for i=1,10 do
      local b = cel.textbutton.new(tostring(i))

      col:insert(-5, b, 'center')

      function b:onclick()
        col:insert(i, self, 'center')
        print(i, '==', col:indexof(self))
      end
    end
  end)

  col:link(root, 'fill')

  function col:onmousedown()
  end

  function col:onmouseup()
  end

end

