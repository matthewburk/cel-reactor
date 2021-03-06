local cel = require 'cel'

return function(root)
  pause()
  --Create a textbutton with initial string.
  local textbutton = cel.textbutton.new('hello\n2'):link(root, 'center')
  pause()

  --The text can be changed
  textbutton:settext(textbutton:gettext() .. ' world')
  pause()

  --Wraps string.format aroud settext
  textbutton:printf('penx %d, peny %d', textbutton:getpenorigin())
  pause()

  --Create a textbutton, ${[[[} will trim the whitespace introduced by indentation in code.
  cel.textbutton.new [[[
  Its the end of the world

  as we know it, and i feel fine]] 
  :link(root, 'center')
  pause()

  --Textbutton has a minw and minh to ensure text doesn't get clipped
  print('textbutton .minw .minh', textbutton.minw, textbutton.minh)
  textbutton:resize(0, 0)
  pause()

  textbutton:settext[[


  Hello this is
  a bit of multiline text


  goodbye ...]]
  pause()

  --A Textbutton does not shrink to fit its contents
  function textbutton:onclick(textbuttton)
    --Resize the textbutton to shrink to fit
    textbutton:settext('A')--:resize(0, 0)
  end

  pause()

  textbutton:unlink()

  local textbutton = cel.textbutton {
    text = 'a text button',
    onclick = function(self) self:relink('fill') end,
  }:link(root, 'center')
  pause()
end 
