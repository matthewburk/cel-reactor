require 'stdinit'

local celdriver = require 'celdriver'
local cel = require 'cel'

--make cairo and cel always use 640x960 surface regardless of window size
celdriver.resize(640, 960)
function reactor.resized()
  celdriver.resize(640, 960)
end


do
  _G.drawtime = 0
  local lastdrawms = 0
  function reactor.draw()    
    celdriver.draw()
    local ms = reactor.timermillis()
    _G.drawtime = math.max(_G.drawtime, ms-lastdrawms)
    lastdrawms = ms
  end
end

local plots = cel.window {
  w = 400, h = 400,  
  function(window)
    local latency = cel.plot.new(0, 0, function(time)
      local r = _G.drawtime
      _G.drawtime = 0
      return r or 1 
    end)

    latency:setrange(0, 50, 10)
    latency:setdomain(-5000, 0, 1000)
    latency:setpollinterval(16)
    latency:start()

    local memcount = cel.plot.new(0, 0, function(time) return collectgarbage('count') end)
    memcount:setrange(0, 1024*8, 1024)
    memcount:setdomain(-60000 , 0, 5000) 
    memcount:setpollinterval(100)
    memcount:start()


    cel.col {
      link = 'fill';
      'latency',
      { flex=1; minh=0;
        latency,
      },
      'collectgarbage "count"',
      { flex=1; minh=0;
        memcount,
      }
    }:link(window, 'fill')
  end
}

function reactor.keydown(key, ...)
  celdriver.keydown(key, ...)
  if key == 'space' then
    cel.printdescription()
  elseif key == 'f1' then
    reactor.fullscreen(true)
  elseif key == 'f2' then
    reactor.fullscreen(false)
  elseif key == 'f9' then
    plots:link(celdriver.root, 'center'):relink() 
  elseif key == 'escape' then
    reactor.quit()
  end
end

cel.getface('cel').font = cel.loadfont('arial', 24)
cel.getface('editbox').textcolor = cel.color.rgb(0, 0, 0)

do --menu
  local slots = {}

  for i=1, 5 do
    local hue = math.random(0, 360)
    slots[#slots+1] = cel.new(0, 0, cel.colorface(cel.color.hsl(hue, 1, .3)))
    slots[#slots+1] = cel.new(0, 0, cel.colorface(cel.color.hsl(hue, .9, .4)))
    slots[#slots+1] = cel.new(0, 0, cel.colorface(cel.color.hsl(hue, .8, .5)))
    slots[#slots+1] = cel.new(0, 0, cel.colorface(cel.color.hsl(hue, .7, .6)))
  end

  local grid = cel.col {
    { flex=1, minh=0, link='fill',
      cel.row {
        { flex=1, minw=0, link='fill',
          slots[1], slots[2], slots[3], slots[4], 
        },
      },
      cel.row {
        { flex=1, minw=0, link='fill',
          slots[5], slots[6], slots[7], slots[8], 
        },
      },
      cel.row {
        { flex=1, minw=0, link='fill',
          slots[9], slots[10], slots[11], slots[12], 
        },
      },
      cel.row {
        { flex=1, minw=0, link='fill',
          slots[13], slots[14], slots[15], slots[16], 
        },
      },
      cel.row {
        { flex=1, minw=0, link='fill',
          slots[17], slots[18], slots[19], slots[20], 
        },
      },
    },
  }:link(celdriver.root, 'fill')

  local nitems = 0
  function grid:additem(item, linker)
    nitems = nitems + 1
    item:link(slots[nitems], linker)
    return item
  end

  grid:additem(cel.label.new('A label'), 'center')
  grid:additem(cel.text.new('Text can have multiple lines'), 'fill')
  grid:additem(cel.editbox.new('Edit me', 200), {'width.center', 5})
  grid:additem(cel.textbutton.new('Holy cow\nits a text\nbutton'), 'center')
  grid:additem(cel.window{title='window'}, {'fill.margin', 20})
    :relink('fence')
    :adddefaultcontrols()

  do
    local list = cel.listbox {
      'this', 
      'is', 
      'a',
      'listbox',
      { link= 'width',
        cel.editbox.new('an editbox'),
      }
    }

    grid:additem(list, {'fill.margin', 20})
  end

  do --a slot can is a cel with an margin, the margin cannot be breached, hmm hard to explain shortly
    local slot = cel.slot {
      margin = { l=10, r=15, t=20, b=25 },
      
      function(slot)
        cel.new(0, 0, cel.colorface(cel.color.rgb(1, 1, 1))):link(slot, 'fill')
      end
    }

    grid:additem(slot, 'fill')
  end

  do --simple time display
    local time = cel.text.new(os.date()):justify('center')

    cel.doafter(500, function()
      time:settext(os.date())
      return 500--repeat again in 500ms
    end)
    
    grid:additem(time, 'width.center')
  end

  do
    local imageface = cel.getface('cel'):new {
      surface = false,
      stretch = false,

      cairodraw = function(_ENV, cr, f, t)
        if f.surface then
          cairo.save(cr)

          if f.stretch then
            local sw, sh = f.surface:get_size()
            cairo.scale(cr, t.w/sw, t.h/sh)
          end
          cairo.rectangle(cr, 0, 0, t.w, t.h)
          cairo.set_source_surface(cr, f.surface)
          cairo.fill(cr)

          cairo.restore(cr)
        end

        return _ENV.drawlinks(cr, t)
      end
    }

    local images = {
      cairo.surface.create_from_png('./images/fishtank.png'),
      cairo.surface.create_from_png('./images/art.png'),
      cairo.surface.create_from_png('./images/glyph.png'),
      cairo.surface.create_from_png('./images/happy.png'),
    }

    for i, image in ipairs(images) do
      local scroll = cel.scroll {
        subject = cel {
          face = imageface:new { surface=images[i] }
        }:resize(images[i]:get_size()),

        { link='center',
          'Hello!',
        },
      }
      grid:additem(scroll, 'fill')
    end
  end
end
