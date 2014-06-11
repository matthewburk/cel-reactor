local cel = require 'cel'

return function(root)
pause()

--new takes string, face
local label = cel.label.new('hello'):link(root, 'center')
pause()

--The text can be changed
label:settext(label:gettext() .. ' world')
pause()

--Wraps string.format aroud settext
label:printf('penx %d, peny %d', label:getpenorigin())
pause()

--Cannot be resized, the size of a label is determined by its text and layout.
print('label limits', label.minw, label.minh, label.maxw, label.maxh)
label:resize(0, 0)
pause()

--A label is not touchable (with the mouse).
print(label:touch(1, 1))

--TODO add .font as cel property maybe ... MAYBE
pause()
end 
