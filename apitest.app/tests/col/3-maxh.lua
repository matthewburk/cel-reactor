local cel = require 'cel'

return function(root)
  local w, h = 50, 50
  local maxh = 40 

  do 
    local col = cel.col.new(0, cel.colorface(app.colors.white))
      :link(root, 'center')

    col.__debug = true
    for i = 1, 10 do
      local grip = cel.grip.new(w, h, cel.colorface(cel.color.hsl(math.random(360), 1, .5)))
      grip:grip(grip)

      grip:link(col, nil, nil, nil, {minh=10, maxh=maxh})

      cel.new(20, 20, cel.colorface(cel.color.rgb(0, 0, 0)))
        :link(grip, 'fill.margin', 10)
    end

    do
      dprint(1, string.rep('_', 20)..'slot.maxh=', maxh)
      dprint(pcall(function()
        for i, link in col:ilinks() do
          assert(link.x == 0)
          assert(link.y == maxh*(i-1), string.format('%s %s %s', i, maxh*(i-1), link.y))
          assert(link.w == w)
          assert(link.h == h)
        end

        assert(col.w == w, col.w)
        assert(col.h <= 10*maxh, col.h)
      end))
      dprint('col.minh, col.maxh', col.minh, col.maxh)
    end

    do
      dprint(2, string.rep('_', 20)..'slot.maxh=', maxh, 'link.minh=100')
      dprint(pcall(function()
        for i, link in col:ilinks() do
          link:setlimits(nil, nil, 100, 200):relink('bottom')
          assert(link.h == 100)
          assert(link.b == maxh*(i), string.format('%s %s %s', i, maxh*(i), link.b))
        end
      end))

      assert(col.w == w, col.w)
      assert(col.h <= 10*maxh, col.h)
      dprint('col.minh, col.maxh', col.minh, col.maxh)
    end

    do
      dprint(3, string.rep('_', 20)..'slot.maxh=', maxh, 'link.minh=100', 'linker=center')
      dprint(pcall(function()
        for i, link in col:ilinks() do
          link:relink('center')
          assert(link.h == 100)
        end
      end))

      assert(col.w == w, col.w)
      assert(col.h <= 10*maxh, col.h)
      dprint('col.minh, col.maxh', col.minh, col.maxh)
    end

    do
      dprint(4, string.rep('_', 20)..'slot.maxh=', maxh, 'link.minh=100', 'linker=nil')
      dprint(pcall(function()
        for i, link in col:ilinks() do
          link:relink()
          assert(link.h == 100)
        end
      end))

      assert(col.w == w, col.w)
      assert(col.h <= 10*maxh, col.h)
      dprint('col.minh, col.maxh', col.minh, col.maxh)
    end

    --[==[
    --]==]
  end


end

