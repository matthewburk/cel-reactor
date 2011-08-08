local cel = require 'cel'

local kit = cel.newnamespace {
  new = function(metacel, ...)
    if metacel ~= 'cel' then
      return cel[metacel].new(...)
    else
      return cel.new(...)
    end
  end,

  compile = function(metacel, t)
    if metacel ~= 'cel' then
      return cel[metacel](t)
    else
      return cel(t)
    end
  end,
}
