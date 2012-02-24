local cel = require 'cel'

return function(root)
  root:addlinks {
    cel.window {
      w = 400, h = 400,
      function(window)
        window:adddefaultcontrols()
        WINDOW = window
      end,
      link = 'fill',

      cel.listbox {
        --cel.window.new(300, 300),
        function(self)
          self.onchange = function(self, item, index, change)
          print(self, item, index, change)
        end

          local _new = cel.textbutton.new
          local new = function(...)
            local button = _new(...)
            button.onclick = button.unlink
            return button
          end
          new = cel.text.new
          local width = cel.getlinker('width') 
          for i = 1, 100 do
            new('The purpose of this test is to see how wrapping text affects performace when laid out in a sequence.'):link(self, width)
            new('It seems that the sequence will resize a few times before settling on a width.'):link(self, width)
            cel.textbutton.new(tostring(self:len())):link(self, width)
            cel.window.new(200, 200):adddefaultcontrols():link(self)
          end
        
        end,
      },
    }
  }

end

