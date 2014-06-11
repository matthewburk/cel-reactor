local cel = require 'cel'

local optionface = cel.getface('textbutton'):new {
  layout = {
    padding = {
      l=function(w, h, font) return font.metrics['M'].advance end,
      r=function(w, h, font) return font.metrics['M'].advance*2 end,
      t=function(w, h, font) return h*.35 end,
    },
  }
}:register('@option')

cel.getface('menu'):new {
  layout={
    menuslot={
      face=cel.getface('cel')--:new(), --TODO why does this not work unless i create a new face
    }
  },
}:register('@simple')

return function(root)

  local optionbtn = cel.textbutton.new('option 1', '@option')

  cel.new(optionbtn.h/2, optionbtn.h/2, '#ffffbb')
    :link(optionbtn, 'right.center', optionbtn.h/4)
    .touch = false 

  optionbtn.menu = cel.menu {
    face='@simple',
    cel.textbutton.new('option 1'),
    'option 2', 
    cel.textbutton.new('option 3'),
  }

  function optionbtn:onclick()
    local x, y = cel.translate(self, 0, self.h, root)
    self.menu:showat(x, y, root)
  end

  function optionbtn.menu:onchoose(item)
    self:unlink()
    optionbtn:settext(item:gettext())
  end

  optionbtn:link(root, 'center')
end
