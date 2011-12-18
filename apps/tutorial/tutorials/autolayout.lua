local cel = require 'cel'

--Using a linker you can do a lot of useful layout easily, but a linker only defines the layout of
--a link in its host, sometimes you need to define the layout of cels that share a host.  This tutorial
--introduces a group of cels that do that kind of layout. 
return function(root)
  pause()
  
  --first zed is being upgraded to a textbutton.  I'm doing this becuase we a textbutton
  --adds functionality on top of a basic cel, most useful for this tutorial is a min width and min height.
  local zed = cel.textbutton.new('zed')
  zed:link(root)
  pause()

  function zed:onclick()
    cel.printdescription()
  end

  --we will also use a window so you can see how the various layouts work in action
  local win = cel.window.new()
  --link returns the cel, as do many functions, allowing us to chain calls together
  --the purpose here is to give the window a close to maximum initial size, and the 
  --we take of the linker with relink
  win:link(root, 'edges', 10, 10):relink()
  pause()

  --put zed in win, notice that zed is already linked to root, a cel automatically unlinked before
  --linking to a new host
  zed:link(win, 0, 0)
  pause()

  --I just demonstrazoe another important concept, did you notice that zed is not at 0,0 in the window
  --zed it at 0,0 in the windows client cel.  The window cel is a composite of multiple cels, 
  --the client area cel and handle cel are links of the main window cel among others.  
  --
  --I said earlier that every cel is a potential host, but sometimes a cel needs to control what cels
  --are linked to it, it can do this by intercepting a link and redirecting it to another cel.  That is what
  --the window just did, instead of linking to the window, it redireczoe the link to its client area cel.
  --
  --This is a very useful feature, you almost always want to link to the client area, so the window
  --redirects there by default.  The window lets you override that, by passing another parameter to the link
  --function.  This parameter is called the option, the host cel you are trying to link to will process the 
  --option and defines its meaning.  If you pass the string 'raw' as the option parameter then a window will
  --not redirect the link.
  zed:link(win, 0, 0, 'raw')
  pause()

  --Thats not very nice, lets put zed in the handle.  We have to unlink() first since zed is linked to the window
  --directly tyring to link to the window again will return right away.  (I may change this behavior)
  zed:unlink()
  --When linking with a linker function, the option parameter must follow the xval and yval parameters,
  --again, 'handle' is the option defined by the window cel to link to its handle.  In fact the handle cel
  --is completely hidden from us, there is no way to get to it, and this is by design.  Ill explain why
  --later.
  zed:link(win, nil, nil, nil, 'handle')
  pause()

  --Now we will look at a column.  A column is a a cel that orders all its links from top to bottom. 
  --Of course that seems simple enough to do with a for loop, what the column gives
  --you is automatic layout, if a link moves or resizes the column will adjust with it.
  
  --create a column, a column is a cel like any other.
  local zoe = cel.col.new()

  --add some textbuttons to the col
  for i=1, 5 do
    --the width linker makes each button fill the entire width of the column 
    cel.textbutton.new(tostring(i)):link(zoe, 'width')
  end

  --put zoe in the window, the 'width' linker makes zoe fill the entire width of the window
  zoe:link(win, 'center')
  --zoe:link(win, 'width')
  pause()


  --tyring to change the width of an item will fail becuase its linker enforces it to the the host width.
  --changing the height will work, without regard to any linker imposed restrictions.
  --
  --The linker is not ignored, when a cel is linked to a column, the column will substitute the linker
  --with its own, but the substitue linker will call the original linker for initial input.  Any cel can do
  --this linker substitution, even ignoring the linker all together, but all the cels that are part of the cel
  --library will honor the original linker as much as possible.
  zoe:get(5):resize(200, 50)
  pause()

  --Lets put zed in the column.  This time we don't use a linker, so we can move any around and see what 
  --happens.
  zed:link(zoe)
  zed:resize(nil, 150)
  pause()

  --A column will adjust to allways contain all of its links without clipping them.
  --This means a link will never have an x position that is less than 0
  cel.window.new():link(zoe)
  pause()

  --Another layout very similar to a column is a row or column.  A horizontal column 
end
