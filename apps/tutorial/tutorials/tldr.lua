--The abridged overview.

--Cel is the name of the library, all moudles in Cel are lowercase.
local cel = require 'cel'

--This function is called by the tutorial loader.
return function(root)
pause()

--create a red cel 100px width 100px height
local zed = cel.new(100, 100, cel.rgbaface(1, 0, 0))

--access properties of a cel, these are read-only
print('zed.w', zed.w, 'zed.h', zed.h)
pause()

--link cels (put zed inside root), the link (zed) is centered in the host(root).
zed:link(root, 'center')
pause()

--A linker (such as 'center') is enforced continuously, until it is removed.
--So we can't move zed off-center
zed:move(0, 0)
pause()

--can change the size of zed though
zed:resize(200, 200)
pause()

--relink a cel (the cel was centered, now on the left)
zed:relink('left')
pause()

--relink with no arguments removes linker
zed:relink()

--now we can move zed around unrestrained
for i=1, 40 do
  cel.doafter(100*i, function()
    zed:moveby(1, 1)
  end)
end
pause()

--unlink zed
zed:unlink()
pause()

--Submodules of cel are loaded on demand.  
--label is a submodule of cel.  it defines a label.
local label = cel.label.new('Hello World')

label:link(root, 'center')
pause()

--row is a cel whose links will be arranged in a row.
--By default it will resize to fit all links
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

--When linking you can pass additional parameters to the linker.  The 'fill' 
--linker will add a left/right margin equal to the first param, and a top/bottom
--margin equal to teh second param.
window:relink('fill')
pause()

--The two values passed to the linker are called xval and yval respectively.  
--Most of the predefined linkers will change behavior by specifying an xval or
--yval.
window:relink('fill', 5, 15)
pause()

window:unlink()

--A regular listbox 
local listbox = cel.listbox {
  'This', 'is', 'a', 'regular', 'text-based', 'listbox',
  --You can also define onevent functions in a cel initializer table.  The 
  --onchange event is commonly implemented.
  onchange = function(listbox, ...)
    print('listbox.onchange', ...)
  end  
}:link(root, 'fill')
pause()

listbox:unlink()

--Any cel can be a host, here we put textbuttons into a listbox
local listbox = cel.listbox {
  onchange = function(listbox, ...)
    print('listbox.onchange', ...)
  end, 
  function(lb)
    for i = 1,100 do
      local button = cel.textbutton.new(tostring(i)):link(lb, 'width')
      --unlink the button when it is clicked, the first parmeter sent
      --to onclick is the button, so we can just point onclick right to 
      --unlink
      button.onclick = button.unlink
    end
  end
}:link(root, 'fill')
pause()

--I mean really any cels can be linked, I'll add a window to the listbox.
--You can event move the window around
window:link(listbox)
listbox:scrollto(0, math.huge)
pause()



pause()
end 
