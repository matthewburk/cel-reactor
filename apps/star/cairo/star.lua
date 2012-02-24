local cel = require 'cel'

_G.app = {tool='polygon'}

local wall = cel.cel.new()



local canvas = require('cairo.canvas')():link(wall, 'fill')

local toolbox = cel.row {
  { minw=0; flex=1; link='fill';
    cel.textbutton { text = 'NEW SHAPE',
      onclick = function() canvas:newshape() end
    },
    cel.textbutton{ text = 'POLYGON',
      onclick = function() app.tool = 'polygon' end
    },
    cel.textbutton { text='FREEHAND',
      onclick = function() app.tool = 'freehand' end
    },
    cel.textbutton.new('ARC'),
  }
}

cel.col {
  link='fill';
  { flex=1,
    wall,
  },
  toolbox,
}:link(root, 'fill')

canvas:takefocus()






