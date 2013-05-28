local cel = require 'cel'

return function(root)
  local w, h = 50, 50
  local cols = {}
  do
    local col = cel.col.new(0, cel.colorface(app.colors.white)):link(root, 'fill.margin', 100, 100)
    cols[#cols+1] = col

    col.__debug = true
    for i = 1, 3 do
      local flex=1
      local grip = cel.grip.new(w, h, cel.colorface(cel.color.hsl(math.random(360), 1, .5)))
        :setlimits(nil, nil, 60, 160)
        :link(col, 'fill', nil, nil, {flex=flex, maxh=true, minh=100})
      grip:grip(grip)

      cel.label.new(''..flex):link(grip)

      local label = cel.label.new(''..grip.h):link(grip, 'center')

      function grip:onresize()
        label:printf('%d', self.h)
      end
    end

    do
      dprint(1, string.rep('_', 20)..'link.minh=60 link.maxh=160 maxh=true minh=100 flex=1')
      dprint(pcall(function()
        local linksh = 0
        for i, link in col:ilinks() do
          assert(link.x == 0)
          assert(link.w == col.w)
          linksh = linksh + link.h
        end

        assert(col.h == linksh)
      end))
      dprint('col.minh, col.maxh', col.minh, col.maxh)
    end
  --[==[
    col:relink('left.top'):resize(200, 0)
    do
      dprint(pcall(function()
        local linksh = 0
        for i, link in col:ilinks() do
          assert(link.x == 0)
          assert(link.w == col.w)
          linksh = linksh + link.h
        end

        assert(col.h == linksh)
      end))
      dprint('col.minh, col.maxh', col.minh, col.maxh)
    end
  --]==]
  end

  --[==[
  do
    local col = cel.col.new(0, cel.colorface(app.colors.white)):link(root, 'fill.margin', 100, 100)
    cols[#cols+1] = col

    col.__debug = true
    for i = 1, 3 do
      local flex=i
      local grip = cel.grip.new(w, h, cel.colorface(cel.color.hsl(math.random(360), 1, .5)))
        :link(col, 'fill', nil, nil, {flex=flex})
      grip:grip(grip)
      cel.label.new(''..flex):link(grip)

      local label = cel.label.new(''..grip.h):link(grip, 'center')

      function grip:onresize()
        label:printf('%d', self.h)
      end
    end

    do
      dprint(1, string.rep('_', 20)..'flex=1,2,3')
      dprint(pcall(function()
        local linksh = 0
        for i, link in col:ilinks() do
          assert(link.x == 0)
          assert(link.w == col.w)
          linksh = linksh + link.h
        end

        assert(col.h == linksh)
      end))
      dprint('col.minh, col.maxh', col.minh, col.maxh)
    end
    col:relink('right.top'):resize(100, 100)
  end
  --]==]

  --[==[
  do
    local col = cel.col.new(0, cel.colorface(app.colors.white)):link(root, 'fill.margin', 100, 100)
    cols[#cols+1] = col

    local flex = {1}
    col.__debug = true
    for i = 1, 3 do
      local flex=flex[i]
      local grip = cel.grip.new(w, h, cel.colorface(cel.color.hsl(math.random(360), 1, .5)))
        :link(col, 'fill', nil, nil, {flex=flex})
      grip:grip(grip)
      cel.label.new(''..(flex or 0)):link(grip)

      local label = cel.label.new(''..grip.h):link(grip, 'center')

      function grip:onresize()
        label:printf('%d', self.h)
      end
    end

    do
      dprint(1, string.rep('_', 20)..'flex=1,0,0')
      dprint(pcall(function()
        local linksh = 0
        do
          local link = col:get(1)
          assert(link.x == 0)
          assert(link.w == col.w)
          assert(link.h == col.h - h*2)
          linksh = linksh + link.h
        end
        do
          local link = col:get(2)
          assert(link.x == 0)
          assert(link.w == col.w)
          assert(link.h == h)
          linksh = linksh + link.h
        end
        do
          local link = col:get(3)
          assert(link.x == 0)
          assert(link.w == col.w)
          assert(link.h == h)
          linksh = linksh + link.h
        end

        assert(col.h == linksh)
      end))
      dprint('col.minh, col.maxh', col.minh, col.maxh)
    end
  end
  --]==]

  --[==[
  do
    local root = cel.window.new(300, 300):link(root)
    local col = cel.col.new(10, cel.colorface(app.colors.black)):link(root, 'fill')
    cols[#cols+1] = col

    col.__debug = true
    for i = 1, 3 do
      local flex=1
      cols[i]:link(col, 'fill', nil, nil, {flex=flex})
    end

    do
      dprint(1, string.rep('_', 20)..'flex=1')
      dprint(pcall(function()
        local linksh = 0
        for i, link in col:ilinks() do
          assert(link.x == 0)
          assert(link.w == col.w)
          linksh = linksh + link.h
        end

        assert(col.h == linksh+20, string.format('linksh=%d, col.h=%d', linksh, col.h))
      end))
      dprint('col.minh, col.maxh', col.minh, col.maxh)
    end
  end
  --]==]
end

