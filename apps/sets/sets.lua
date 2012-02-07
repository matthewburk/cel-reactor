local cel = require 'cel'

local appcels = cel.newset('app')

local platforms = app.newset('platforms')

platforms:newset('abc')
platforms:newset('hij')
platforms:newset('xyz')







local tabs = app.newset('tabs') --app.tabs

tabs.textbutton.new('a tab')
tabs.textbutton.new('b tab')
tabs.textbutton.new('c tab')
tabs.textbutton.new('d tab')

tabs.remove(membercel)
tabs.add(membercel)
tabs.subset.selected

tabs:apply(function(tab)
  tab.onclick = function(tab)
    tabs.selected.map(tabs.selected.exclude)

    tabs.selected.include(tab)    
    end
  end
end)


appcels:apply(function(cel)
  if cel.
end)

for 
