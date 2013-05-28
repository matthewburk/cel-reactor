local cel = require 'cel'

return function(root)
  local w, h = 10, 50
  local n = 3

  do
    local row = cel.row.new(0, cel.colorface(app.colors.white)):link(root, 'center')

    row.__debug = false 
    for i = 1, n do
      --local window = cel.window.new(w, h, tostring(i)):link(row)
      --window:adddefaultcontrols()
      local grip = cel.grip.new(w, h, cel.colorface(cel.color.hsl(math.random(360), 1, .5))):link(row)
      grip:grip(grip)
    end

    do
      dprint(string.rep('_', 20)..'basic')
      dprint(pcall(function()
        for i, link in row:ilinks() do
          assert(link.y == 0)
          assert(link.x == w*(i-1))
          assert(link.w == w)
          assert(link.h == h)
        end

        assert(row.w == n*w, row.w)
        assert(row.h == h, row.h)
      end))
      dprint('row.minh, row.maxh', row.minh, row.maxh)
    end

    row.__debug = true 
    do 
      dprint(string.rep('_', 20)..'linkers cannot change height of cel')

      for i, link in row:ilinks() do
        link:relink('width')
      end

      dprint(pcall(function()
        for i, link in row:ilinks() do
          assert(link.y == 0)
          assert(link.x == w*(i-1))
          assert(link.w == w)
          assert(link.h == h, link.h)
        end

        assert(row.h == h, row.h)
        assert(row.w == n*w, row.w)
      end))
    end

    --[==[
    do 
      dprint(string.rep('_', 20)..'row width is 0 if linkers return 0 for width when hw is 0')

      for i, link in row:ilinks() do
        link:relink('fill')
      end

      dprint(pcall(function()
        for i, link in row:ilinks() do
          assert(link.x == 0)
          assert(link.y == h*(i-1))
          assert(link.w == 0) --because there is no cel bracing the width of the row
          assert(link.h == h)
        end

        assert(row.w == 0, row.w) --because there is no cel bracing the width of the row
        assert(row.h == 10*h, row.h)
      end))
    end

    do 
      dprint(string.rep('_', 20)..'change all linkers to return hw+5 for width')

      for i, link in row:ilinks() do
        link:relink(function(hw, hh, x, y, w, h, xval, yval, minw, maxw)
          return x, y, math.max(minw, hw)+5, 105 --h should have no effect
        end)
      end

      dprint(pcall(function()
        for i, link in row:ilinks() do
          assert(link.x == 0)
          assert(link.y == h*(i-1))
          assert(link.w == 5) --because there is no cel bracing the width of the row
          assert(link.h == h)
        end

        assert(row.w == 5, row.w) --because there is no cel bracing the width of the row
        assert(row.h == 10*h, row.h)
      end))
    end

    do 
      dprint(string.rep('_', 20)..'change all links to have minw of 50, do not change linker')

      for i, link in row:ilinks() do
        link:setlimits(50, link.maxw, link.minh, link.maxh)
      end

      dprint(pcall(function()
        for i, link in row:ilinks() do
          assert(link.x == 0)
          assert(link.y == h*(i-1))
          assert(link.w == 55) --because there is no cel bracing the width of the row
          assert(link.h == h)
        end

        assert(row.w == 55, row.w) --because there is no cel bracing the width of the row
        assert(row.h == 10*h, row.h)
      end))
    end

    do 
      dprint(string.rep('_', 20)..'change all links to have minh of 50')

      for i, link in row:ilinks() do
        link:setlimits(link.minw, link.maxw, 50, link.maxh)
      end

      dprint(pcall(function()
        for i, link in row:ilinks() do
          assert(link.x == 0)
          assert(link.y == 50*(i-1))
          assert(link.w == 55) --because there is no cel bracing the width of the row
          assert(link.h == 50)
        end

        assert(row.w == 55, row.w) --because there is no cel bracing the width of the row
        assert(row.h == 10*50, row.h)
      end))
    end

    do 
      dprint(string.rep('_', 20)..'remove linkers')

      for i, link in row:ilinks() do
        link:relink()
      end

      dprint(pcall(function()
        for i, link in row:ilinks() do
          assert(link.x == 0)
          assert(link.y == 50*(i-1))
          assert(link.w == 55) --because there is no cel bracing the width of the row
          assert(link.h == 50)
        end

        assert(row.w == 55, row.w) --because there is no cel bracing the width of the row
        assert(row.h == 10*50, row.h)
      end))
    end

    --]==]
    row:relink('left.top')
  end

  --[[
  do
    local w, h = 100, 100
    local row = cel.row.new(0, cel.colorface(app.colors.white)):link(root, 'center')

    row.__debug = false
    for i = 1, 3 do
      local window = cel.window.new(w, h, tostring(i)):link(row)
      window:adddefaultcontrols()
    end

    do
      dprint(string.rep('_', 20)..'basic')
      dprint(pcall(function()
        for i, link in row:ilinks() do
          assert(link.x == 0)
          assert(link.y == h*(i-1))
          assert(link.w == w)
          assert(link.h == h)
        end

        assert(row.w == w, row.w)
        assert(row.h == 3*h, row.h)
      end))
      dprint('row.minh, row.maxh', row.minh, row.maxh)
    end
  end
  --]]
end

