local cel = require 'cel'

local diagram = cel.col {
  face = cel.rgbaface(0, 0, 0);
  gap = 4;
  { 
    face = cel.rgbaface(1, 1, 1);
    link='fill';
    cel.row {
      { minw = 150;
        cel.col {
          'slot properties:',
          '  minh = nil',
          '  flex = nil',
          '  face = white',
          'link properties:',
          '  linker = nil',
        },
      },
      cel.slot { face = cel.rgbaface(0, 1, 1);
        cel.text.new [[[
        The height of the slot that this link is
        in is defined by the height of the link.
        This layout works in the opposited direction
        that linkers do, which creates a chicken/egg
        problem using linkers.  The approach taken is to
        run the linker with 0 for the host height (hh).
        The height returned from the linker is adjusted to 
        the links min/max heights and the resulting height
        is used as the height of the slot.  If a cel does not
        have a minh and the slot does not have a minh and
        a linker such as 'fill' or 'height' is used the resulting
        slot will have 0 height.
        ]];
      },
    },
  },

  { minh=100;
    face = cel.rgbaface(.7, .7, .7);

    cel.row {
      { minw = 150;
        cel.col {
          'slot properties:',
          '  minh = 100',
          '  flex = nil',
          '  face = gray',
        },
      },
      cel.slot { face = cel.rgbaface(0, 1, 1);
        cel.text.new [[[
        The height of this slot is at least 100. The height of the 
        link is less.]];
      },
      { flex=1; link='center'; 'This is a col slot, white is the color of slots.',},
    },
  },
  { minh=100; flex=1; face = cel.rgbaface(1, 1, 1);
    
    cel.row {
      { minw = 150;
        cel.col {
          'slot properties:',
          '  minh = 100',
          '  flex = 1',
          '  face = white',
        },
      },
      cel.slot { face = cel.rgbaface(0, 1, 1);
        cel.text.new [[[
        The height of this slot is at least 100. The height of the 
        link is less.]];
      },
      { flex=1; link='center'; 'This is a col slot, white is the color of slots.',},
    },
  },
}

return function(root)
  diagram:link(root, 'center')
  pause()
end
