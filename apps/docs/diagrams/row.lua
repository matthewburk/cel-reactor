local cel = require 'cel'

local function nolimits(w, h) return cel.button.new(w or 100, h or w or 100) end
local function fixedsize() return cel.label.new('fixedsize') end
local function minsize() return cel.text.new [[[
                                minw and minh
                                no maxw or maxh]] end

local function newrow(linker)
  return cel.col {
    { link = 'fill'; face = cel.rgbaface(1, 1, 1);
      string.format('linker = %s', tostring(linker));
    },
    { flex = 1; link = 'center.top';
      cel.row { gap = 1; face = cel.rgbaface(1, 1, 0);
        { nolimits(), face = cel.rgbaface(1, 0, 0); link = linker; },
        { fixedsize(), face = cel.rgbaface(1, 0, 0);  link = linker; },
        { minsize(), face = cel.rgbaface(1, 0, 0); link = linker;  },
        { nolimits(200), face = cel.rgbaface(1, 0, 0); link = linker; },
      },
    },
  }
end

local function newcol(linker)
  return cel.col {
    { link = 'fill'; face = cel.rgbaface(1, 1, 1);
      string.format('linker = %s', tostring(linker));
    },
    { flex = 1; link = 'center.top';
      cel.col { gap = 1; face = cel.rgbaface(1, 1, 0);
        { nolimits(), face = cel.rgbaface(1, 0, 0); link = linker; },
        { fixedsize(), face = cel.rgbaface(1, 0, 0);  link = linker; },
        { minsize(), face = cel.rgbaface(1, 0, 0); link = linker;  },
        { nolimits(200), face = cel.rgbaface(1, 0, 0); link = linker; },
      },
    },
  }
end

local diagram = cel.row { link = 'center';
  
  { flex = 1; 
    cel.col { link = 'center';
      { flex = 1;
        newrow()
      },
      { flex = 1;
        newrow('fill')
      },
      { flex = 1;
        newrow('center')
      },
      { flex = 1;
        newrow('height')
      },
      { flex = 1;
        newrow('width')
      },
      { flex = 1;
        newrow('left')
      },
      { flex = 1;
        newrow('right')
      },
      { flex = 1;
        newrow('top')
      },
      { flex = 1;
        newrow('bottom')
      },
    },
  },
  { flex = 5; 
    cel.row { link = 'center';
      { flex = 1;
        newcol()
      },
      { flex = 1;
        newcol('fill')
      },
      { flex = 1;
        newcol('center')
      },
      { flex = 1;
        newcol('height')
      },
      { flex = 1;
        newcol('width')
      },
      { flex = 1;
        newcol('left')
      },
      { flex = 1;
        newcol('right')
      },
      { flex = 1;
        newcol('top')
      },
      { flex = 1;
        newcol('bottom')
      },
    },
  },
}

return diagram
