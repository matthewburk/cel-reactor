local cel = require 'cel'
local kit = setmetatable({}, {__index=cel})

do
  local textbutton = cel.textbutton
  kit.textbutton = setmetatable({},
    {
      __index = textbutton,
      __call = function(_, t)

        return textbutton(t)
      end,
    })
  kit.textbutton.new = function(...)
    return textbutton.new(...)
  end
end
