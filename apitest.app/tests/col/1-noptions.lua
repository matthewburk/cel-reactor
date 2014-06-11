local cel = require 'cel'

return function(root)
  local w, h = 50, 10
  local n = 3

  do
    local col = cel.col.new(0, '#ffffff'):link(root, 'center')

    col.__debug = false
    for i = 1, n do
      --local window = cel.window.new(w, h, tostring(i)):link(col)
      --window:adddefaultcontrols()
      local grip = cel.grip.new(w, h, cel.color.hsl(math.random(360), 1, .5)):link(col)
      grip:grip(grip)
    end

    do
      dprint(string.rep('_', 20)..'basic')
      dprint(pcall(function()
        for i, link in col:ilinks() do
          assert(link.x == 0)
          assert(link.y == h*(i-1))
          assert(link.w == w)
          assert(link.h == h)
        end

        assert(col.w == w, col.w)
        assert(col.h == n*h, col.h)
      end))
      dprint('col.minh, col.maxh', col.minh, col.maxh)
    end

    col.__debug = true 
    do 
      dprint(string.rep('_', 20)..'linkers cannot change height of cel')

      for i, link in col:ilinks() do
        link:relink('height')
      end

      dprint(pcall(function()
        for i, link in col:ilinks() do
          assert(link.x == 0)
          assert(link.y == h*(i-1))
          assert(link.w == w)
          assert(link.h == h)
        end

        assert(col.w == w, col.w)
        assert(col.h == n*h, col.h)
      end))
    end

    --[==[
    do 
      dprint(string.rep('_', 20)..'col width is 0 if linkers return 0 for width when hw is 0')

      for i, link in col:ilinks() do
        link:relink('fill')
      end

      dprint(pcall(function()
        for i, link in col:ilinks() do
          assert(link.x == 0)
          assert(link.y == h*(i-1))
          assert(link.w == 0) --because there is no cel bracing the width of the col
          assert(link.h == h)
        end

        assert(col.w == 0, col.w) --because there is no cel bracing the width of the col
        assert(col.h == 10*h, col.h)
      end))
    end

    do 
      dprint(string.rep('_', 20)..'change all linkers to return hw+5 for width')

      for i, link in col:ilinks() do
        link:relink(function(hw, hh, x, y, w, h, xval, yval, minw, maxw)
          return x, y, math.max(minw, hw)+5, 105 --h should have no effect
        end)
      end

      dprint(pcall(function()
        for i, link in col:ilinks() do
          assert(link.x == 0)
          assert(link.y == h*(i-1))
          assert(link.w == 5) --because there is no cel bracing the width of the col
          assert(link.h == h)
        end

        assert(col.w == 5, col.w) --because there is no cel bracing the width of the col
        assert(col.h == 10*h, col.h)
      end))
    end

    do 
      dprint(string.rep('_', 20)..'change all links to have minw of 50, do not change linker')

      for i, link in col:ilinks() do
        link:setlimits(50, link.maxw, link.minh, link.maxh)
      end

      dprint(pcall(function()
        for i, link in col:ilinks() do
          assert(link.x == 0)
          assert(link.y == h*(i-1))
          assert(link.w == 55) --because there is no cel bracing the width of the col
          assert(link.h == h)
        end

        assert(col.w == 55, col.w) --because there is no cel bracing the width of the col
        assert(col.h == 10*h, col.h)
      end))
    end

    do 
      dprint(string.rep('_', 20)..'change all links to have minh of 50')

      for i, link in col:ilinks() do
        link:setlimits(link.minw, link.maxw, 50, link.maxh)
      end

      dprint(pcall(function()
        for i, link in col:ilinks() do
          assert(link.x == 0)
          assert(link.y == 50*(i-1))
          assert(link.w == 55) --because there is no cel bracing the width of the col
          assert(link.h == 50)
        end

        assert(col.w == 55, col.w) --because there is no cel bracing the width of the col
        assert(col.h == 10*50, col.h)
      end))
    end

    do 
      dprint(string.rep('_', 20)..'remove linkers')

      for i, link in col:ilinks() do
        link:relink()
      end

      dprint(pcall(function()
        for i, link in col:ilinks() do
          assert(link.x == 0)
          assert(link.y == 50*(i-1))
          assert(link.w == 55) --because there is no cel bracing the width of the col
          assert(link.h == 50)
        end

        assert(col.w == 55, col.w) --because there is no cel bracing the width of the col
        assert(col.h == 10*50, col.h)
      end))
    end

    --]==]
    col:relink('left.top')
  end

  --[[
  do
    local w, h = 100, 100
    local col = cel.col.new(0, '#ffffff'):link(root, 'center')

    col.__debug = false
    for i = 1, 3 do
      local window = cel.window.new(w, h, tostring(i)):link(col)
      window:adddefaultcontrols()
    end

    do
      dprint(string.rep('_', 20)..'basic')
      dprint(pcall(function()
        for i, link in col:ilinks() do
          assert(link.x == 0)
          assert(link.y == h*(i-1))
          assert(link.w == w)
          assert(link.h == h)
        end

        assert(col.w == w, col.w)
        assert(col.h == 3*h, col.h)
      end))
      dprint('col.minh, col.maxh', col.minh, col.maxh)
    end
  end
  --]]
end

