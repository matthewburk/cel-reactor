--This tutorial covers the basics of linking.  
local cel = require 'cel'

return function(root)
  pause()
  --Create a 100 x 150 cel.  The last parameter is a face that will draw the cel as a gray rectangle.
  local zed = cel.new(100, 150, '#777777')
  pause()

  --At this point zed will not be drawn and the user cannot interact with it. 
  --To show zed to the user we must link it to the root cel.  

  --Link zed to root.
  zed:link(root)
  pause()

  --An important feature of linking is that any cel can be linked to any other cel.  
  --Lets create another cel and link it to zed.
  local zoe = cel.new(30, 30, '#ff0000')
  zoe:link(zed)
  pause()

  --The opposite of linking is unlinking, when a cel is unlinked it will no
  --longer be shown and the user cannot interact with it.
  zed:unlink()
  pause()

  --Now use a variation of the link method that specifies where in the host
  --the link will be anchored.  
  --zed is linked to root, at (300, 0)
  zed:link(root, 300, 0)
  pause()

  --When you want to change the position of a cel, use the move() method.
  --x, y set to (10, 10) but width and height will not change
  zoe:move(10, 10)
  pause()

  --Resize zed, short for zed:move(nil, nil, 300, 300)
  zed:resize(300, 300) 
  pause()

  --Set x, y, w, h of zed.
  zed:move(root.w/3, root.h/3, root.w/3, root.h/3)
  pause()

  --Next up is automatic layout, lets move zed back to 0, 0
  zed:move(0, 0)
  pause()

  --Here we are defining a function to center a link in its host.  
  --hw is the host width, hh is the host height, w, h is the current dimensions of the link.
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

  --Doing layout like this is tedious.  When root is resized zed will not be,
  --linker functions solve this problem.
  --reset
  zed:unlink()
  pause()

  --Link zed to root using a linker.  This linker will center zed.
  zed:link(root, function(hw, hh, x, y, w, h)
    return (hw - w)/2, (hh - h)/2, w, h
  end)
  pause()

  --The function passed to link is called a linker. 
  --
  --A linker is called with these arguments:(hostw, hosth, x, y, w, h, xval, yval, minw, maxw, minh, maxh).
  --A linker must return x, y, w, h of the rectangle.
  --A linker should not have side-effects, becuase it may be called when you do not expect it.
  --Parameters x, y, w, h defines the rectangle that the linker is laying out.
  --Parameters xval and yval meaning is defined by the linker.
  --Parameters minw, maxw, minh, maxh define the min/max dimensions of the rectangle that the linker is laying out.
  pause()

  --The linker is called when the link is initially made and when host is resized or a link is moved.  Essentially 
  --any changes to the parameters to a linker will cause cel to call the linker to get the x, y, w, h for the linked
  --cel.
  --Try resizing root and you will see the zed remains centered.  And trying to move zed to the top left corner will
  --not work either.
  zed:move(0, 0)
  pause()

  --We can resize zed and its position is automatically recalculated so that
  --it remains centered.
  zed:resize(zed.w + 100, zed.h + 100)
  pause()

  --The relink function is used to alter how a cel is linked, without unlinking
  --and linking the cel again.
  --If no arguments are passed to relink then the linker is removed.
  zed:relink()
  pause()

  --Now zed will not automatically center when root is resized, and we can
  --freely position zed.
  zed:move(10, 10, 10, 10)
  pause()

  --A string can be specified for the linker instead of a function, in this
  --case cel will lookup the function by that name in its list of linkers.
  --The 'center' linker is supplied by cel.
  --cel:relink takes a linker as the first parameter (the host does not change).
  zed:relink('center')
  pause()

  --The 'center' linker will offset from centerx by xval and centery by yval.  There parameters come after the linker
  --in both cel:relink() and cel:link().
  --This will center zed offset 100 to the right of center and 100 above center.
  zed:relink('center', 100, -100)
  pause()

  --fill host
  zed:relink('fill')
  pause()

  --fill host but leave a margin of 10
  zed:relink('fill.margin', 10)
  pause()

  --fill host but leave an x margin of 10 and y margin of 40
  zed:relink('fill.margin', 10, 40)
  pause()

  --align to right of host
  --size and y unconstrained.
  zed:relink('right')
  pause()

  --align to right.bottom of host.  
  --size unconstrained.
  zed:relink('right.bottom')
  zed:resize(200, 200)
  pause()
  --end
end


