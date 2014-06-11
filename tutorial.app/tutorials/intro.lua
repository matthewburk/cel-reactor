--Require the cel module.
local cel = require 'cel'

--This function is called by the tutorial loader. 
--The sandbox parameter is a cel.
return function(sandbox)
  pause()
  
  --Every cel defines a rectangle (x, y, w, h).  The units are integer pixels.
  --x, y is the coordinate of the top-left point of the cel (relative to a host 
  --cel)  w is the width and h is the height.  x increases to the right and y
  --increases down. 
  print('sandbox rectangle', sandbox.x, sandbox.y, sandbox.w, sandbox.h)
  pause()

  --Notice sandbox.x and sandbox.y are 0.  Which means it is at the top-left corner
  --of its host cel.  We can see where sandbox is relative to the
  --root cel by examining sandbox.X and sandbox.Y
  print('sandbox root position', sandbox.X, sandbox.Y)
  pause()

  --Here are some other handy properties 
  print('sandbox (relative)left', sandbox.l)
  print('sandbox (relative)right', sandbox.r)
  print('sandbox (relative)top', sandbox.t)
  print('sandbox (relative)bottom', sandbox.b)
  print('sandbox (absolute)left', sandbox.L)
  print('sandbox (absolute)right', sandbox.R)
  print('sandbox (absolute)top', sandbox.T)
  print('sandbox (absolute)bottom', sandbox.B)
  pause()

  --This is how to create a cel.
  local zed = cel.new()

  --Notice that zed does not have a root position, because it is
  --not linked to the root cel.
  print('zed', zed.x, zed.y, zed.w, zed.h)
  print('zed root position', zed.X, zed.Y)
  pause()

  --Link zed to sandbox, zed now has a root poistion becuase sandbox has a root position.
  zed:link(sandbox)
  print('zed', zed.x, zed.y, zed.w, zed.h)
  print('zed root position', zed.X, zed.Y)
  pause()

  --A cels position and size are read-only, and can only be changed by function calls.
  --Move zed to (x, y, w, h).
  zed:move(10, 10, 15, 25)
  print('zed', zed.x, zed.y, zed.w, zed.h)
  print('zed root position', zed.X, zed.Y)
  pause()

  --The host/link relationship is dynamic, sandbox became the host of zed when zed
  --was linked to sandbox.  The opposite of linking is unlinking.  This removes
  --zed from its host (sandbox).
  zed:unlink()
  print('zed', zed.x, zed.y, zed.w, zed.h)
  print('zed root position', zed.X, zed.Y)
  pause()
end
