local cel = require 'cel'
--require 'profiler'
return function(root)
  root {
    cel.window {
      w = 400, h = 400,
      function(window)
        window:adddefaultcontrols()
        WINDOW = window
      end,
      cel.listbox {
        link = {'edges'},
        --cel.window.new(300, 300),
        function(self)
          self:settopborder(cel.textbutton.new('the top'))
          local _new = cel.textbutton.new
          local new = function(...)
            local button = _new(...)
            button.onclick = button.unlink
            return button
          end
          new = cel.textbutton.new
          local width = cel.getlinker('width') 
          for i = 1, 3000 do
            new('hello'):link(self, 'right')
          end
        --self.onchange = function(self, item, index, change)
        --  print(self, item, index, change)
        --end
        end,
      },
    }
  }

  --[[
  profiler.start('listboxmeta.out')
  for i = 1, 1 do
    startmillis = reactor.timermillis()
    WINDOW:moveby(0, 0, 500, 0)
    endmillis = reactor.timermillis()
    print('move took = ', endmillis - startmillis)
  end
  profiler.stop()
  --]]
end

