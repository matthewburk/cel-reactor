local cel = require 'cel'

return function(root)
  local w, h = 50, 10
  local n = 3

  local registry = {}
  local function register(cel, name)
    registry[name] = cel
  end


  do --should not be able to resize col
    cel.col { face='#ff0000',
      cel.window.new(),
      --{flex=1, 'flex=1'},
    }
    :link(root, 'center')
    :resize(300, 300)

  end


  cel.col { face='#ff0044',
    link='right',

    cel.new(400, 20, '#00ff00'):call(register, 'green'),

    --[[
    cel.label {
      text='well and good on the right'
    }:call(register, 'rightlbl'),
    --]]

    cel.textbutton {
      text='on the right',
      onclick = function(self)
        self:settext('r')
        --registry.rightlbl:settext('smll')
        registry.col1.__debug = true
        registry.green:setlimits(100, 100)
        --registry.col1.__debug = false 
      end
    },
   
    {link='center', 'center'}
  }:link(root, 'center.top')
  :call(register, 'col1')
end

