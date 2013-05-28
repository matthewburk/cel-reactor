local cel = require 'cel'

return function(root)
  local source = [[Chuzk dksa fkdla ielkjda dfjlk eiwzfavnm]]

  local t = {}

  for i=1, 5000 do
    local a = math.random(#source)
    local b = a + math.random(4)
    t[#t+1]=source:sub(a, b)
  end

  root:addlinks {
    cel.window { 
      w=200, h=200,
      link='fill',

      cel.scroll { 
        subject={
          fillwidth=true,
          cel.text.new(table.concat(t, ' ')):wrap('word'),
        }
      }
    }
  }
end
