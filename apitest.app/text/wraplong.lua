local cel = require 'cel'

return function(root)
  
  local source = [[hello my name is slim shady what is your's.]]

  local t = {}

  for i=1, 5000 do
    local a = math.random(#source)
    local b = a + math.random(4)
    t[#t+1]=source:sub(a, b)
  end

  local text = cel.text.new(table.concat(t, 'M'))

  root:addlinks {
    cel.window { link='fill',
      w=200, h=200,
      cel.scroll { 
        subject={
          fillwidth=true,
          text,
        }
      }
    }
  }

  dprint('textlen', text:len(), #text:gettext())
end
