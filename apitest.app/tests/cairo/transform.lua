local cel = require 'cel'

local face = cel.getface('cel'):new()
local image = cairo.surface.create_from_png(app.path..'/data/happy.png')
local w, h = image:get_size()
local rot = 0
local scalex = 1
local scaley = 1
local offsetx = 0
local offsety = 0

function face.cairodraw(_ENV, cr, f, t)
  
  cr:save()
  cr:translate(t.w/2 + offsetx, t.h/2 + offsety)
  cr:rotate(rot* math.pi/180)
  cr:scale(math.max(scalex, 0.001), math.max(scaley, 0.001))
  cr:translate(-0.5*t.w, -0.5*t.h)
  cr:arc(0, 0, 0, 0, 0)
  cr:arc(0, 0, t.w, 0, .5*math.pi)
  cr:close_path()

  --cr:set_source_surface(image)
  --cr:paint()

  cr:rectangle(0, 0, t.w, t.h)

  cr:restore()
  cr:set_source_color(app.colors.green)
  cr:set_dash(4, 4)
  cr:set_line_width(4)
  cr:stroke()

  return _ENV.drawlinks(cr, t)
end

return function(root)
  local grip = cel.grip.new(256, 256, face)
    :setlimits(128, nil, 128, nil)
    :link(root, 'center')
    :relink()

  cel.grip.new(10, 10, cel.colorface(app.colors.green)):link(grip, 'right.top'):grip(grip, 'topright')
  cel.grip.new(10, 10, cel.colorface(app.colors.green)):link(grip, 'left.top'):grip(grip, 'topleft')
  cel.grip.new(10, 10, cel.colorface(app.colors.green)):link(grip, 'left.bottom'):grip(grip, 'bottomleft')
  cel.grip.new(10, 10, cel.colorface(app.colors.green)):link(grip, 'right.bottom'):grip(grip, 'bottomright')
  cel.grip.new(10, 10, cel.colorface(app.colors.green)):link(grip, 'right.center'):grip(grip, 'right')
  cel.grip.new(10, 10, cel.colorface(app.colors.green)):link(grip, 'left.center'):grip(grip, 'left')
  cel.grip.new(10, 10, cel.colorface(app.colors.green)):link(grip, 'center.top'):grip(grip, 'top')
  cel.grip.new(10, 10, cel.colorface(app.colors.green)):link(grip, 'center.bottom'):grip(grip, 'bottom')

  grip:grip(grip)

  cel.col { link='width', gap=5,
    cel.row { link='width',
      { link='center',
        'rotation' 
      },
      { flex=1,
        cel.slider {
          min=0, max=360, step=45, onchange = function(slider, value)
            rot = value
            grip:refresh()
          end
        }:resize(30, 30),
      },
    },
    cel.row { link='width',
      { link='center',
        'scale x' 
      },
      { flex=1,
        cel.slider {
          min=0, max=1, onchange = function(slider, value)
            scalex = value
            grip:refresh()
          end
        }:resize(30, 30),
      },
    },
    cel.row { link='width',
      { link='center',
        'scale y' 
      },
      { flex=1,
        cel.slider {
          min=0, max=1, onchange = function(slider, value)
            scaley = value
            grip:refresh()
          end
        }:resize(30, 30),
      },
    },

    cel.row { link='width',
      { link='center',
        'offset x' 
      },
      { flex=1,
        cel.slider {
          min=-256, max=256, step = 64, onchange = function(slider, value)
            offsetx = value
            grip:refresh()
          end
        }:resize(30, 30),
      },
    },

    cel.row { link='width',
      { link='center',
        'offset y' 
      },
      { flex=1,
        cel.slider {
          min=-256, max=256, step = 64, onchange = function(slider, value)
            offsety = value
            grip:refresh()
          end
        }:resize(30, 30),
      },
    },
  }:link(root, 'width.top')
  
  
end

