local cel = require 'cel'

return function(root)
  local w, h = 50, 10

  do --minh = 100
    local col = cel.col.new(0, cel.colorface(app.colors.white)):link(root, 'center')

    col.__debug = false 
    for i = 1, 10 do
      local grip = cel.grip.new(w, h, cel.colorface(cel.color.hsl(math.random(360), 1, .5)))
        :link(col, nil, nil, nil, {minh=100})
      grip:grip(grip)
    end

    do
      dprint(string.rep('_', 20)..'slot.minh=100')
      dprint(pcall(function()
        for i, link in col:ilinks() do
          assert(link.x == 0)
          assert(link.y == 100*(i-1), link.y)
          assert(link.w == w)
          assert(link.h == h)
        end

        assert(col.w == w, col.w)
        assert(col.h == 10*100, col.h)
      end))
      dprint('col.minh, col.maxh', col.minh, col.maxh)
    end

    do
      dprint(string.rep('_', 20)..'slot.minh=100 linker=center')
      for i, link in col:ilinks() do
        link:relink('center')
      end
      dprint(pcall(function()
        for i, link in col:ilinks() do
          assert(link.x == 0)
          assert(link.y >= 100*(i-1), link.y)
          assert(link.w == w)
          assert(link.h == h)
        end

        assert(col.w == w, col.w)
        assert(col.h == 10*100, col.h)
      end))
      dprint('col.minh, col.maxh', col.minh, col.maxh)
    end

    do
      dprint(string.rep('_', 20)..'slot.minh=100 linker=center, link.minh=150')
      for i, link in col:ilinks() do
        link:setlimits(link.minw, link.maxw, 150, link.maxh)
      end
      dprint(pcall(function()
        for i, link in col:ilinks() do
          assert(link.x == 0)
          assert(link.y >= 150*(i-1), link.y)
          assert(link.w == w)
          assert(link.h == 150 or link.maxh)
        end

        assert(col.w == w, col.w)
        assert(col.h == 10*150, col.h)
      end))
      dprint('col.minh, col.maxh', col.minh, col.maxh)
    end

    do
      dprint(string.rep('_', 20)..'slot.minh=100 linker=center, link.minh=0')
      for i, link in col:ilinks() do
        link:setlimits(link.minw, link.maxw, 0, link.maxh, nil, h)
      end
      dprint(pcall(function()
        for i, link in col:ilinks() do
          assert(link.x == 0)
          assert(link.y >= 100*(i-1), link.y)
          assert(link.w == w)
          assert(link.h == 100 or link.maxh)
        end

        assert(col.w == w, col.w)
        assert(col.h == 10*100, col.h)
      end))
      dprint('col.minh, col.maxh', col.minh, col.maxh)
    end

    col:relink('left.top')
  end

  do --minh = 100
    local w = 20
    local h = 20
    local col = cel.col.new(0, cel.colorface(app.colors.white)):link(root, 'center')

    col.__debug = false
    for i = 1, 3 do
      local grip = cel.grip.new(w, h, cel.colorface(cel.color.hsl(math.random(360), 1, .5)))
        :link(col, 'center', nil, nil, {minh=40})
      grip:grip(grip)
    end

    --col:resize(200)

    do
      dprint(string.rep('_', 20)..'slot.minh=40')
      dprint(pcall(function()
        for i, link in col:ilinks() do
          assert(link.x >= 0)
          assert(link.y >= 40*(i-1), link.y)
          assert(link.w == w, link.w)
          assert(link.h == h, link.h)
        end

        assert(col.w == 200, col.w)
        assert(col.h == 40*3, col.h)
      end))
      dprint('col.minh, col.maxh', col.minh, col.maxh)
    end
  end
end

