local cel = require 'cel'


local dzrpf do
  local metacel, metatable = cel.newmetacel('dzrp')

  function metacel:__resize(dzrp, ow, oh)
    if dzrp.w ~= ow then
      local w = dzrp.w
      dzrp:setlimits(10, 2^20, math.max(10, 400-w), math.max(10, 400-w))
    end
  end

  do
    local _new = metacel.new
    function metacel:new(w, h, face)
      face = self:getface(face)
      local dzrp = _new(self, w, h, face)
      return dzrp
    end
  end

  dzrpf = metacel:newfactory()
end

return function(root)
  local w, h = 50, 50
  local cols = {}
  ---[==[
  do
    local root = cel.window.new(300, 300):link(root)
    local col = cel.col.new(1, cel.colorface(app.colors.red)):link(root, 'fill')

    col.__debug = true
    col:flux(function()
      for i = 1, 3 do
        cel.text.new('this will wrap'):wrap('word'):link(col, 'width')
      end
    end)
  end
  --]==]
end

