return function(root)
  local cel = require 'cel'

  local faces = {
    white = cel.colorface(cel.color.rgb(1, 1, 1)),
    gray = cel.colorface(cel.color.rgb(.3, .3, .3)),
    black = cel.colorface(cel.color.rgb(0, 0, 0)),
    red = cel.colorface(cel.color.rgb(1, 0, 0)),
    green = cel.colorface(cel.color.rgb(0, 1, 0)),
    purple = cel.colorface(cel.color.tint(cel.color.rgb(.6, 0, .7), .5)),
  }

  local function nolimits(name, w, h) 
    local grip =  cel.grip {
      w = w or 20,
      h = h or w or 20,
      link = 'center',
      face = faces.purple,
      name,
    }

    return grip:grip(grip)
  end
  local function fixedsize(name) 
    local grip = cel.grip {    
      link='center',
      face = faces.purple,
      name
    }:setlimits(30, 30, 20, 20)

    return grip:grip(grip)
  end
  local function minsize(name) 
    local grip = cel.grip {    
      link='center',
      face = faces.purple,
      name
    }:setlimits(15, nil, 15, nil)

    return grip:grip(grip)
  end

  local function newcol(linker)
    return cel.col { gap=1; 
      { link = 'center'; face = faces.gray;
        string.format('linker = %s', tostring(linker));
      },
      { flex = 1; link = 'center.height'; minh=0; face = faces.gray; maxh=2^50;
        cel.col { gap = 5; face = faces.green;
          { nolimits('1'), face = faces.red; link = linker; },
          { fixedsize('2'), face = faces.red;  link = linker; },
          { minsize('3'), face = faces.red; link = linker;  },
          { nolimits('4', 50), face = faces.red; link = linker; },
          { nolimits('5', 0, 0), face = faces.red; link = linker; },
        },
      },
      { flex = 1; link = 'center.height'; minh=0; face = faces.gray; maxh=2^50;
        cel.col { gap = 5; face = faces.green;
          { nolimits('1'), face = faces.red; link = linker; flex=1; maxh=2^50 },
          { fixedsize('2'), face = faces.red;  link = linker; flex=1; maxh=2^50 },
          { minsize('3'), face = faces.red; link = linker;  flex=1; maxh=2^50 },
          { nolimits('4', 50), face = faces.red; link = linker; flex=1; maxh=2^50 },
          { nolimits('5', 0, 0), face = faces.red; link = linker; flex=1; maxh=2^50 },
        },
      },
      { flex = 1; link = 'center.height'; minh=0; face = faces.gray; maxh=2^50;
        cel.col { gap = 5; face = faces.green;
          { nolimits('1'), face = faces.red; link = linker; minh=40; maxh=2^50 },
          { fixedsize('2'), face = faces.red;  link = linker; minh=40; maxh=2^50 },
          { minsize('3'), face = faces.red; link = linker;  minh=40; maxh=2^50 },
          { nolimits('4', 50), face = faces.red; link = linker; minh=40; maxh=2^50 },
          { nolimits('5', 0, 0), face = faces.red; link = linker; minh=40; maxh=2^50 },
        },
      },
      { flex = 1; link = 'center.height'; minh=0; face = faces.gray; maxh=2^50;
        cel.col { gap = 5; face = faces.green;
          { nolimits('1'), face = faces.red; link = linker; minh=40; flex=1; maxh=2^50 },
          { fixedsize('2'), face = faces.red;  link = linker; minh=40; flex=1; maxh=2^50 },
          { minsize('3'), face = faces.red; link = linker;  minh=40; flex=1; maxh=2^50 },
          { nolimits('4', 50), face = faces.red; link = linker; minh=40; flex=1; maxh=2^50 },
          { nolimits('5', 0, 0), face = faces.red; link = linker; minh=40; flex=1; maxh=2^50 },
        },
      },
      { flex = 1; link = 'center.height'; minh=0; face = faces.gray; maxh=2^50;
        cel.col { gap = 5; face = faces.green;
          { nolimits('1'), face = faces.red; link = linker; minh=0; flex=0; maxh=2^50 },
          { fixedsize('2'), face = faces.red;  link = linker; minh=0; flex=0; maxh=2^50 },
          { minsize('3'), face = faces.red; link = linker;  minh=0; flex=0; maxh=2^50 },
          { nolimits('4', 50), face = faces.red; link = linker; minh=0; flex=0; maxh=2^50 },
          { nolimits('5', 0, 0), face = faces.red; link = linker; minh=0; flex=0; maxh=2^50 },
        },
      },
      { flex = 1; link = 'center.height'; minh=0; face = faces.gray; maxh=2^50;
        cel.col { gap = 5; face = faces.green;
          { nolimits('1'), face = faces.red; link = linker; minh=0; flex=1; maxh=2^50 },
          { fixedsize('2'), face = faces.red;  link = linker; minh=0; flex=1; maxh=2^50 },
          { minsize('3'), face = faces.red; link = linker;  minh=0; flex=1; maxh=2^50 },
          { nolimits('4', 50), face = faces.red; link = linker; minh=0; flex=1; maxh=2^50 },
          { nolimits('5', 0, 0), face = faces.red; link = linker; minh=0; flex=1; maxh=2^50 },
        },
      },
    }
  end

  local diagram = 
    cel.row { link = 'fill'; gap=1; face = cel.colorface(cel.color.rgb(0, 0, .5));
      cel.col { gap=1;
        '';
        { flex = 1; link = 'left.center'; face = faces.gray; minh=0, maxh=2^50;
          cel.col {
            'slot minh = nil'; 
            'slot flex = 0';
          }
        };
        { flex = 1; link = 'left.center'; face = faces.gray; minh=0, maxh=2^50;
          cel.col { link = 'width';
            'slot minh = nil';
            'slot flex = 1';
            cel.text.new'\n\nflexible height is allocated unevenly'
              :justify('center')
          }
        };
        { flex = 1; link = 'left.center'; face = faces.gray; minh=0, maxh=2^50;
          cel.col {
            'slot minh = 40';
            'slot flex = 0';
          }
        };
        { flex = 1; link = 'left.center'; face = faces.gray; minh=0, maxh=2^50;
          cel.col { link = 'width';
            'slot minh = 40';
            'slot flex = 1';
            cel.text.new[[flexible height is allocated evenly]];
            
          }
        };
        { flex = 1; link = 'left.center'; face = faces.gray; minh=0, maxh=2^50;
          cel.col {
            'slot minh = 0';
            'slot flex = 0';
          }
        };
        { flex = 1; link = 'left.center'; face = faces.gray; minh=0, maxh=2^50;
          cel.col { link = 'width';
            'slot minh = 0.';
            'slot flex = 1';
            cel.text.new([[flexible height is allocated evenly  ]]):justify('right');
          }
        };
      },
      { flex = 1; minw=true, --there is an error here, increasing the width of the link doesn't flex properly, it jumps to correct
      --when its width matches the slot width
        newcol()
      },
      { flex = 1; minw=true, 
        newcol('fill')
      },
      { flex = 1;minw=true, 
        newcol('center')
      },
      { flex = 1;minw=true, 
        newcol('height')
      },
      { flex = 1;minw=true, 
        newcol('width')
      },
      { flex = 1;minw=true,
        newcol('left')
      },
      { flex = 1; minw=true,
        newcol('right')
      },
      { flex = 1; minw=true,
        newcol('top')
      },
      { flex = 1; minw=true,
        newcol('bottom')
      },
    }

  cel.scroll {
    subject = cel { link = {'fill.margin', 20};
      w = 1800, h = 1800,
      diagram,
    };
  }:link(root, 'fill')
end
