--Yes I did, but you may have missed how awsome they are. 
local cel = require 'cel'

return function(root)
  pause()
  --The linkers we have used up to this point have been mundane.  Every gui 
  --library has some way to align top/bottom/left/right/center and variations
  --of those.  These are useful, so much that there are predefined linkers
  --for doing just that.  But cel linkers can do much more.
  
  --To demonstrate another useful way to use a linker we will use a grip.
  --A grip is a simple cel that can 'grip' cels (including itself) and then
  --move them when the mouse is moved the grip will move the gripped cel.
  local grip = cel.grip.new(100, 100)
  local zed = cel {
    w = 300; h = 300; face = cel.rgbaface(1, 1, 0, .5);
    { link = 'fill'; grip},
    { link = 'center'; 'THIS CEL IS THE GRIP TARGET'},
  }:link(root)

  --grip zed
  grip:grip(zed)

  --now drag zed around with the mouse.
  pause()

  --a grip has other modes as well, this will move the top-right corner of the
  --cel.  
  grip:relink('right.top'):resize(20, 20)
  grip:grip(zed, 'topright')
  pause()

  --A grip is a useful building block, but we are here to learn about linkers.
  --You may have noticed that draggin the grip around you can reduce zed's size
  --to 0.  We can change that with a linker.

  --first center and resize zed
  zed:resize(300, 300):relink('center')

  zed:relink(function(hw, hh, x, y, w, h)
    w = math.max(w, grip.w)
    h = math.max(h, grip.h)
    return x, y, w, h
  end)

  --We are not letting the size of zed get smaller than the grip now, try it out
  pause()

  --You may not have expected zed's bottom to move, with a change to the
  --linker, we can fix that

  --first center and resize zed
  zed:resize(300, 300):relink('center')

  zed:relink(function(hw, hh, x, y, w, h)
    local minw = math.max(w, grip.w)
    local minh = math.max(h, grip.h)
    local oy = h-minh 
    return x, y+oy, minw, minh
  end)

  --The right way to do this is to use the xval and yval parameters of the
  --linker.
  
  --first center and resize zed
  zed:resize(300, 300):relink('center')

  zed:relink(function(hw, hh, x, y, w, h, xval, yval)
    local minw = math.max(w, xval)
    local minh = math.max(h, yval)
    local oy = h-minh 
    return x, y+oy, minw, minh
  end,
  grip.w, --xval
  grip.h  --yval
  )

  --The linker is run when the parameters passed to the linker change, the size
  --of the grip changing will not cause the linker to run. Depending on an
  --upvalue is possible, but not recommended, becuase a linker is expected
  --to give the same results for the same parameters.
  pause()

  --Here is another useful linker, this will keep zed inside of root

  --first center and resize zed
  zed:resize(300, 300):relink('center')

  --regrip
  grip:relink('fill'):grip(zed)

  zed:relink(function(hw, hh, x, y, w, h)
    if w > hw then w = hw end
    if h > hh then h = hh end

    if x <= 0 then 
      x = 0
    elseif x + w > hw then
      x = hw - w
    end

    if y <= 0 then
      y = 0
    elseif y + h > hh then
      y = hh - h
    end

    return x, y, w, h
  end)

  --The predefined linker 'fence' does this as well

  pause()
end
