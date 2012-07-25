local cel = require 'cel'

return function(root)

  cel.window {
    w = root.w/2;
    h = root.h/2;
    link = 'fill';
    cel.listbox {
      link = 'width';
      cel.editbox.new('HELLO', 200),
      cel.editbox.new('HELLO', 200),
      cel.editbox.new('HELLO', 200),
      cel.editbox.new('HELLO', 200),
      cel.editbox.new('HELLO', 200),
      cel.editbox.new('HELLO', 200),
      cel.editbox.new('HELLO', 200),
      cel.editbox.new('HELLO', 200),
      cel.editbox.new('HELLO', 200),
      cel.editbox.new('HELLO', 200),
    }
  }:link(root, 'center'):relink()
 
  cel.window {
    w = root.w/2;
    h = root.h/2;
    link = 'fill';
    cel.editbox {
      filter=cel.editbox.filters.number,
      text='1.29',
      w = 300,
    },

  }:link(root, 'center'):relink()
end

