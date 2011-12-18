---------1---------2---------3---------4---------5---------6---------7---------8
--This tutorial introduces the basics of Cel.
--If you ended up here without reading any other documentation you should 
--know that Cel is the proper name of the library.  Following the Lua 
--tradition the module is called 'cel' all lowercase.  Cel allows you to 
--create controls/widgets called cels.  The name cel is short for (c)ontrol
--(el)ement.  Cel uses composition liberally to create more complex cels.  Cel
--is designed to be "embedded" into a host application (such as Love) that 
--provides user input and rendering.  These tutorials do not go over the
--embedding process, see TODO url for embedding instructions.

--Require the cel module.  Cel does not use the 5.1 module system, so we must
--store the reference.
local cel = require 'cel'

--This function is called by the tutorial loader. 
return function(root)
  pause()
  --root is a a cel. There is ultimately one true root cel, we do not have
  --access to the real root cel (by design).  We are effectively in a sandbox
  --and the root cel we are using is not the real root.  NOTE: the sandbox is
  --pretty weak, its not too hard to break out of it, with Lua 5.2 it should be
  --possible to create a strong sandbox.

  --Every cel defines a rectangle (x, y, w, h).  The units are integer pixels.
  --x, y is the coordinate of the top-left point of the cel (relative to a host 
  --cel)  w is the width and h is the height.  x increases to the right and y
  --increases down.
  
  --Lets examine root
  print('root rectangle', root.x, root.y, root.w, root.h)
  pause()

  --notice root.x and root.y are 0.  Which means it is at the top-left corner
  --of its host cel.  We can see where root is on the screen (relative to the
  --real root cel to be precise) by examining root.X and root.Y
  print('root screen position', root.X, root.Y)
  pause()

  --Here are some other handy properties 
  print('root (relative)left', root.l)
  print('root (relative)right', root.r)
  print('root (relative)top', root.t)
  print('root (relative)bottom', root.b)
  print('root (absolute)left', root.L)
  print('root (absolute)right', root.R)
  print('root (absolute)top', root.T)
  print('root (absolute)bottom', root.B)
  pause()
  --This is how to create a new cel.
  local zed = cel.new()

  --Lets examine zed
  print('zed', zed.x, zed.y, zed.w, zed.h)
  print('zed screen position', zed.X, zed.Y)
  pause()

  --Notice that zed does not have a screen position, that is because it is
  --not linked to the root cel.  Linking a cel puts it into another cel. Lets
  --link zed to root.
  zed:link(root)
  print('zed', zed.x, zed.y, zed.w, zed.h)
  print('zed screen position', zed.X, zed.Y)
  pause()

  --Now zed has a screen position.  Linking will be explained in detail in a 
  --later tutorial, for now you need that linking creates a container/containee
  --relationship (parent/child in terms of the tree structure).  Cel uses the
  --term host for a container/parent and the term link for a containee/child.
  --EVERY cel is a potential host and can be linked to by another cel.

  --The host/link relationship is dynamic, root became the host of zed when zed
  --was linked to root.  The opposite of linking is unlinking, which removes
  --the the cel from its host.
  zed:unlink()
  print('zed', zed.x, zed.y, zed.w, zed.h)
  print('zed screen position', zed.X, zed.Y)


  --Important note, a cels properties are read-only, changes always happen
  --through function calls.  
  --
  --If you are confused about when to use ':' vs '.' to call a function remember
  --that zed:link(root) is sugar for zed.link(zed, root) and consult the api
  --docs.  All cel functions that operate on an instance of a cel take the cel
  --as the first parameter.  Modules have only a single instance and will always
  --use dot notation.
  pause()
end
