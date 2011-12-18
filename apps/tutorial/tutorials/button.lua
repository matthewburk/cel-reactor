local cel = require 'cel'

return function(root)
pause()

--new takes w, h, face
local button = cel.button.new(100, 100):link(root, 'center')
pause()

button:unlink()

--a button defines 3 events:
button = cel.button {
  w = 10, h = 10, 
  onpress = function(self)
    print(self, 'onpress')
  end,
  onhold = function(self)
    print(self, 'onhold')
  end,
  onclick = function(self)
    print(self, 'onclick')
  end,
  
}:link(root, 'fill', 30, 30)

pause()

--A buttons description includes state, which is a userdefined value that does not affect the behavior of a button.  The state can be useful for implementing toggle buttons or checkboxes.
button:setstate('activated')
print(button:getstate())
pause()
button:setstate(nil)
print(button:getstate())
pause()
end 
