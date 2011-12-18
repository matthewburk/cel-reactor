---------1---------2---------3---------4---------5---------6---------7---------8
--This tutorial covers the basics of linking.  
local cel = require 'cel'

return function(root)
  pause()
  --Create a new cel that is with the with an initial width of 100 and an
  --initial height of 150. The last parameter is the face that will be used to
  --render the cel, faces will be coverd in the next tutorial. 
  local zed = cel.new(100, 150, cel.rgbaface(.5, .5, .5))
  pause()
  --At this point zed will not be drawn and the user cannot interact with it. 
  --To show zed to the user we must link it to the root cel.  

  --Here zed is linked to root.  When a cel is linked the cel that it is linking
  --to becomes its host.  Host is the term used in the cel library becuase 
  --parent implies creation which is not the case.  A cel can host any number
  --of other cels which are referred to as its links.
  --It this case root is the host of zed, and zed is a link of root.
  zed:link(root)
  pause()
  --You should be able to see a gray rectangle now, that's zed.
  
  --An important feature of linking is that any cel can be linked to any other
  --cel.  In other words there is no special cel that is not a potential host.

  --Lets create another cel and link it to zed.
  local zoe = cel.new(30, 30, cel.rgbaface(1, 0, 0))
  zoe:link(zed)
  pause()
  --You should be able to see a red rectangle in zed, that's zoe.

  --The opposite of linking is unlinking, when a cel is unlinked it will no
  --longer be shown and the user cannot interact with it.
  zed:unlink()
  pause()

  --Now use a variation of the link method that specifies where in the host
  --the link will be anchored.  
  --zed is linked to root, at (300, 0)
  zed:link(root, 300, 0)
  pause()
  --Notice that zoe is still linked to zed, because we never unlinked zoe.

  --When you want to change the position of a cel, use the move() method.
  zoe:move(10, 10)
  pause()

  --Resize zed.
  zed:resize(300, 300)
  pause()

  --The move method also accepts parameters for w, h and is the most effecient
  --method to move a cels position and resize it.  
  zed:move(root.w/3, root.h/3, root.w/3, root.h/3)
  pause()

  --Next up is automatic layout, lets move zed back to 0, 0
  zed:move(0, 0)
  pause()

  --Here we are defining a function to center a link in its host
  --hw is the host width
  --hh is the host height
  --w, h is the current dimensions of the link
  --We return a new x, y, w, h values that will center it in the host
  local function center(hw, hh, w, h)
    return (hw - w)/2, (hh - h)/2, w, h
  end

  --Now lets center zed in root.
  do
    local x, y, w, h = center(root.w, root.h, zed.w, zed.h)    
    zed:move(x, y, w, h)
  end
  pause()

  --Doing layout like this is tedious.  When root is resized zed will not be
  --centerd in root any more.
  --There is a way to do this kind of layout automatically, lets reset and do
  --it a better way.
  zed:unlink()
  zed:resize(root.w/2, root.h/4)
  pause()

  --Lets redefine center so it can be used in automatic layout.
  center = function(hw, hh, x, y, w, h)
    return (hw - w)/2, (hh - h)/2, w, h
  end

  --The center function can now be used as a linker. 
  --
  --A linker is a function that meets the following conditions.  
  --  The linker should determine the layout of a rectangle and return the
  --  resuling x, y, w, h of the rectangle.
  --  In general the linker should not have side-effects, becuase it may be
  --  called when you do not expect it.
  --
  --A linker is called with these arguments:
  --  (hw, hh, x, y, w, h, xval, yval, minw, maxw, minh, maxh)
  --  hw and hh are the width and height of the host rectangle(not cel).
  --  x, y, w, h defines the rectangle that the linker is laying out.
  --  minw, maxw, minh, maxh define the min/max dimensions of the rectangle
  --  that the linker is laying out.
  --  the meaning of xval, yval is defined by the linker.
  pause()

  --The most basic automatic layout is provided by the link and relink 
  --functions.  Here we are linking zed to root again but this time, we aren't
  --specifying an (x,y) location, but a linker function.  When a function is
  --passed as the second parameter to link it must be a linker and is called
  --to determine the initial layout of the link in the host.
  zed:link(root, center)
  pause()

  --The linker is called when the host is resized or a link is moved
  --(and in other special circumstances).
  --
  --Try resizing root and you will see the zed remains centered
  --Trying to move zed to a different location will invoke the linker, which
  --will force zed back to center.
  zed:move(0, 0)
  pause()

  --We can resize zed and its position is automatically recalculated so that
  --it remains centered
  zed:resize(zed.w + 100, zed.h + 100)
  pause()

  --The relink function is used to alter how a cel is linked, without unlinking
  --and linking the cel again.
  --Lets relink zed. If no arguments are passed to relink then the linker is
  --removed.
  zed:relink()
  pause()

  --Now zed will not automatically center when root is resized, and we can
  --freely position zed.
  zed:move(10, 10, 10, 10)
  pause()

  --Now lets relink zed using a new linker, this time we will use the xval and
  --yval linker params.

  --This linker will stretch or shrink the rectangle so that it is the same
  --width and height as the host rectangle, and then center it.
  --
  --xval and yval must be numbers or nil,
  --xval specifies the horizontal distance between the edges of the two
  --rectangles.
  --yval specifies the vertical distance between the edges of the two
  --rectangles. 
  local function edges(hw, hh, x, y, w, h, xval, yval)
    xval = xval or 0
    yval = yval or 0
    w = hw - (xval*2)
    h = hh - (yval*2)
    return center(hw, hh, x, y, w, h, 0, 0)
  end

  --relink takes a linker as the first parameter, the second and third
  --parameters are the xval and yval passed to the linker
  zed:relink(edges, 15, 30)
  pause()

  --A string can be specified for the linker instead of a function, in this
  --case cel will lookup the function by that name in its list of linkers.  Use
  --cel.addlinker(linkername, linkerfunction) to add a linker to the list.
  --Lets add our center linker and try it.  
  cel.addlinker('tutcenter', center)
  zed:relink('tutcenter')
  pause()

  --We did not use the name 'center' becuase there is already a linker
  --named 'center' in the list.  There are many predefined useful linkers,
  --so check the documentation before writing your own.  

  --The predefined 'center' linker can take numbers for xval and yval which
  --are added to x and y of the result rectangle.  Here we relink zed to root
  --so that zed is off center.
  
  --First resize zed so that this is visually obvious.  Notice that I have
  --chained the relink calls, most cel functions will return the cel to allow
  --chaining.
  zed:relink(edges, 40, 40):relink('center', 15, 5)
  pause()
end


