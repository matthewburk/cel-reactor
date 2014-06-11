--High level overview of Cel (does not cover embedding)

--Load the cel library.
local cel = require 'cel'

--This function is called by the tutorial loader.
return function(root)
pause()

--Create a red cel 100 width 100 height
local zed = cel.new(100, 100, '#ff0000')

--Access properties of a cel, these are read-only
print('zed.w', zed.w, 'zed.h', zed.h)
pause()

--Link zed to root.
zed:link(root, 'center')
pause()

--zed cannot be moved becuase a linker (such as 'center') is always enforced.
zed:move(0, 0)
pause()

--We can change the size of zed becuase the 'center' linker only forces the
--position of zed.
zed:resize(200, 200)
pause()

--relink zed, zed will still be linked to root, but the linker will be 'left'.
zed:relink('left')
pause()

--relink with no arguments removes the linker, and now we can move zed.
zed:relink()

for i=1, 40 do
  cel.doafter(20*i, function()
    zed:moveby(1, 1)
  end)
end
pause()

--unlink zed
zed:unlink()
pause()

--Submodules of cel are loaded on demand.
--local label = require 'cel.label' is optional, I don't use it.
local label = cel.label.new('Hello World')

label:link(root, 'center')
pause()

--A row is a cel that will arrange its links in a row.
local row = cel.row.new():link(root, 'top')

for i = 1,10 do
  cel.textbutton.new(tostring(math.random(1999))):link(row)
end
pause()

row:unlink()

--A cel can be initialized from a table by calling the module that defines the
--cel as a function.
local window = cel.window {
  title = 'window';
  w = 400, h = 500; --width and height
  --If a cel is found in the array part of the table it is linked to the cel
  zed,
  --We can of course create another cel inline, a col is column.
  cel.col {
    --A string in the array part will create a label which is then linked
    'This',
    'is',
    'a',
    'column',
    cel.row {
      'This', 'is', 'a', 'row',
    },
  },
  --A table (that is not a cel) in the array part can be used to specify the
  --linker to use
  { link = 'right';
    --This col is linked to the window using the 'right' linker.
    cel.col {
      --can also put link in the hash part of the initializer, and it will be
      --the defualt applied to all cels in the array part.
      link = 'center';
      'Column', 
      'on',
      --We can override the default link of 'center'
      { link = 'left'; 'the'}, 
      'right',
    },
  },
  --A function in the array part is called, with the host as the only parameter.
  function(window)
    window:adddefaultcontrols()
  end,
}:link(root)
pause()

--When linking you can pass additional parameters to the linker.  The 
--'fill.margin' linker will add a left/right margin equal to the first param,
--and a top/bottom margin equal to teh second param.
--The two values passed to the linker are called xval and yval respectively.  
--Most of the predefined linkers will change behavior by specifying an xval or
--yval.
window:relink('fill.margin', 5, 15)
pause()

window:unlink()

--A list
local list = cel.list {
  'This', 'is', 'a', 'list',
  --You can also define onevent functions in a cel initializer table.  The 
  --onchange event is commonly implemented.
  onchange = function(list, ...)
    print('list.onchange', ...)
  end  
}:link(root, 'fill')
pause()

list:unlink()

--Any cel can be a host, here we put textbuttons into a list
local list = cel.list {
  onchange = function(list, ...)
    print('list.onchange', ...)
  end, 
  function(list)
    for i = 1,10 do
      local button = cel.textbutton.new(tostring(i)):link(list, 'width')
      --unlink the button when it is clicked, the first parmeter sent
      --to onclick is the button, so we can just point onclick right to 
      --unlink
      button.onclick = button.unlink
    end
  end
}:link(root, 'fill')
pause()

--I mean really any cels can be linked, I'll add a window to the list.
--You can even move the window around
window:link(list)
pause()

--Cels can be composed by linking, link list to a scroll to get a scrollable
--list.
cel.scroll {
  link='fill',
  --When list is linked to this scroll cel it is automatically unlinked first.
  list,
}:link(root, 'fill')
pause()
end 
