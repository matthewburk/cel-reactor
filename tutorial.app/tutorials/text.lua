local cel = require 'cel'

return function(root)
pause()
--A text cel is simple text with a single font and multi-line wrapping.

--new takes string, face
local text = cel.text.new 'hello world this will wrap,\n resize the window to see'

local window = cel.window.new(200, 200, 'text'):link(root, 'center'):relink()

text:link(window, 'fill')
pause()

--The text can be changed
text:settext(text:gettext() .. ' extra')
pause()

--Wraps string.format aroud settext
text:printf('%s penx %d, peny %d', text:gettext(), text:getbaseline())
pause()

--Has a minw and variable minh.
print('text limits', text.minw, text.minh, text.maxw, text.maxh)
text:resize(0, 0)
pause()

--A text is touchable (with the mouse) unlike a label.
print(text:touch(1, 1))
pause()

print(text:getline(1, 'i', 'j', 'advance', 'h'))
pause()
end 
