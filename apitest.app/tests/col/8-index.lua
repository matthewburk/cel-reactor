local cel = require 'cel'

return function(root)
  local w, h = 50, 50
  local cols = {}
  do
    local col = cel.col.new(0, cel.colorface(app.colors.red)):link(root, 'fill.margin', 100, 100)

    col.__debug = true
    for i = 1, 10 do
      cel.new(0, 0):link(col, 'width')
    end


    dprint(pcall(function()
      for i, link in col:ilinks() do
        assert(col:get(i) == link)
      end

      for i = 2, col:len()-1 do
        local link = col:get(i)
        assert(link)
        local indexoflink = col:indexof(link)
        assert(indexoflink == i, string.format('index %d i %d', indexoflink, i))
        local nextlink = col:next(link)
        assert(nextlink)
        local indexofnextlink = col:indexof(nextlink)
        assert(indexofnextlink == i+1, string.format('indexnext %d i+1 %d', indexofnextlink, i+1))
        assert(nextlink ~= link)
        assert(nextlink == col:get(i+1), string.format('i = %d', i))
      end
    end))
  end
end

