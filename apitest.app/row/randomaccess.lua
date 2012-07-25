local cel = require 'cel'

return function(root)

  local row = cel.row.new()

  row:flux(function()
    for i=1,10 do
      local b = cel.textbutton.new(tostring(i))

      row:insert(-5, b, 'center')

      function b:onclick()
        row:insert(i, self, 'center')
        print(i, '==', row:indexof(self))
      end
    end
  end)

  row:link(root, 'fill')

  function row:onmousedown()
  end

  function row:onmouseup()
  end

end

