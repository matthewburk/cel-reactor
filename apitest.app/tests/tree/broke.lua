local cel = require 'cel'

return function(root)

  local slot = cel.col.new(0, '#ff00ff')
  local col = cel.col {
    face = '#ff0000',
    'a',
      'abcd',
  }:link(slot, 'width')

  cel.slot {
    link='fill',
  cel.window { w=300, h=300, title='tree',
    link='fill',
    cel.scroll { link='fill', cel { slot } },
  }:adddefaultcontrols()
}:link(root, 'center'):relink()
    

    dprint('slot.linker', slot.linker)
    slot.__debug = true
  col:get(2):unlink()
end
