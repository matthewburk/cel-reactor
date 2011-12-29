local cel = require 'cel' 

local driver = cel.installdriver(
  {
    buttons = {
      left = 'left',
      middle = 'middle',
      right = 'right', 
    },
    states = {
      up = 'up',
      down = 'down',
    },
    wheel = {
      up = 1,
      down = -1,
    },
  },
  {
    keys = {
      ['backspace'] = 'backspace',
      ['tab'] = 'tab',
      ['enter'] = 'enter',
      ['shift'] = 'shift',
      ['ctrl'] = 'ctrl',
      ['alt'] = 'alt',
      ['pause'] = 'pause',
      ['capslock'] = 'capslock',
      ['escape'] = 'escape',
      ['space'] = 'space',
      ['pageup'] = 'pageup',
      ['pagedown'] = 'pagedown',
      ['end'] = 'end',
      ['home'] = 'home',
      ['left'] = 'left',
      ['up'] = 'up',
      ['right'] = 'right',
      ['down'] = 'down',
      ['printscreen'] = 'printscreen',
      ['insert'] = 'insert',
      ['delete'] = 'delete',
      ['0'] = '0',
      ['1'] = '1',
      ['2'] = '2',
      ['3'] = '3',
      ['4'] = '4',
      ['5'] = '5',
      ['6'] = '6',
      ['7'] = '7',
      ['8'] = '8',
      ['9'] = '9',
      ['a'] = 'a',
      ['b'] = 'b',
      ['c'] = 'c',
      ['d'] = 'd',
      ['e'] = 'e',
      ['f'] = 'f',
      ['g'] = 'g',
      ['h'] = 'h',
      ['i'] = 'i',
      ['j'] = 'j',
      ['k'] = 'k',
      ['l'] = 'l',
      ['m'] = 'm',
      ['n'] = 'n',
      ['o'] = 'o',
      ['p'] = 'p',
      ['q'] = 'q',
      ['r'] = 'r',
      ['s'] = 's',
      ['t'] = 't',
      ['u'] = 'u',
      ['v'] = 'v',
      ['w'] = 'w',
      ['x'] = 'x',
      ['y'] = 'y',
      ['z'] = 'z',
      ['numpad0'] = 'numpad0',
      ['numpad1'] = 'numpad1',
      ['numpad2'] = 'numpad2',
      ['numpad3'] = 'numpad3',
      ['numpad4'] = 'numpad4',
      ['numpad5'] = 'numpad5',
      ['numpad6'] = 'numpad6',
      ['numpad7'] = 'numpad7',
      ['numpad8'] = 'numpad8',
      ['numpad9'] = 'numpad9',
      ['multiply'] = 'multiply',
      ['add'] = 'add',
      ['subtract'] = 'subtract',
      ['decimal'] = 'decimal',
      ['divide'] = 'divide',
      ['f1'] = 'f1',
      ['f2'] = 'f2',
      ['f3'] = 'f3',
      ['f4'] = 'f4',
      ['f5'] = 'f5',
      ['f6'] = 'f6',
      ['f7'] = 'f7',
      ['f8'] = 'f8',
      ['f9'] = 'f9',
      ['f10'] = 'f10',
      ['f11'] = 'f11',
      ['f12'] = 'f12',
      ['numlock'] = 'numlock',
      ['scrolllock'] = 'scrolllock',
      ['equal'] = 'equal',
      ['comma'] = 'comma',
      ['minus'] = 'minus',
      ['period'] = 'period',
      ['semicolon'] = 'semicolon',
      ['slash'] = 'slash',
      ['graveaccent'] = 'graveaccent',
      ['openbracket'] = 'openbracket',
      ['backslash'] = 'backslash',
      ['closebracket'] = 'closebracket',
      ['apostrophe'] = 'apostrophe',
    },
    states = { 
      up = 'up', 
      down = 'down', 
    }
  })

  local rootrect = {
    x = 0,
    y = 0,
    w = 0,
    h = 0,
  }

function reactor.roottowindow(x, y)
  return x, y
end

function reactor.windowtoroot(x, y, ...)
  x = x - rootrect.x
  y = y - rootrect.y
  x = driver.root.w/rootrect.w * x
  y = driver.root.h/rootrect.h * y
  return math.floor(x + .5), math.floor(y + .5), ...
end

function reactor.mousedown(x, y, button, alt, ctrl, shift)
  driver.mousedown(reactor.windowtoroot(x, y, button, alt, ctrl, shift))
end

function reactor.mouseup(x, y, button, alt, ctrl, shift)
  driver.mouseup(reactor.windowtoroot(x, y, button, alt, ctrl, shift))
end

function reactor.mousewheel(x, y, delta, step, alt, ctrl, shift)
  local direction 

  if delta > 0 then
    direction = cel.mouse.wheel.up
  else
    direction =  cel.mouse.wheel.down
  end

  delta = math.abs(delta)
  for i=1,delta do
    driver.mousewheel(reactor.windowtoroot(x, y, direction, step, alt, ctrl, shift))
  end
end

function reactor.mousemove(x, y)
  driver.mousemove(reactor.windowtoroot(x, y))
end

function reactor.keydown(key, alt, ctrl, shift)
  driver.keydown(key, alt, ctrl, shift)
end

function reactor.keypress(key, alt, ctrl, shift)
  driver.keypress(key, alt, ctrl, shift)
end

function reactor.keyup(key, alt, ctrl, shift)
  driver.keyup(key, alt, ctrl, shift)
end

function reactor.character(c)
  driver.char(c)
end

function reactor.command(c)
  driver.command(c)
end

function reactor.tick(millis)
  driver.tick(millis)
end

function driver.clipboard(command, data)
  if command == 'get' then
    return reactor.clipboard.get()
  elseif command == 'put' then
    reactor.clipboard.put(data)
  end
end

do
  local celfontnames = {
    code = 'fixedsys',
    monospace = 'courier new',
    serif = 'times new roman',
    sansserif = 'arial',
    default = 'arial',
  }

  function driver.loadfont(name, weight, slant, size)
    name = celfontnames[name] or name 

    local cr = cairo.create(cairo.surface.create(0, 0))
    local cairofont = cairo.font.face_create(name, slant, weight)

    cr:set_font_face(cairofont)
    cr:set_font_size(size)

    local ascent, descent, lineheight = cr:font_extents()

    local font = {
      cairofont = cairofont,
      name = name,
      weight = weight,
      slant = slant,
      size = size,
      lineheight = lineheight,
      ascent = ascent,
      descent = descent,
      metrics = setmetatable({}, {__index = function(glyphmetrics, glyph)
        local char = string.char(glyph)
        local xbr, ybr, w, h, xadv, yadv = cr:text_extents(char)      
        glyphmetrics[glyph] = {
          glyph = glyph,
          char = char,
          advance = xadv,
          xmin = xbr,
          xmax = xbr + w,
          ymin = ybr,
          ymax = ybr + h,
        }
        return glyphmetrics[glyph]
      end})
    }

    return font 
  end
end

local stretch = cel.getlinker('fixedaspectstretch') 

local faces = require((...)..'.faces')

return {
  resize = function(w, h)
    local x, y, aw, ah = stretch(reactor.w, reactor.h, 0, 0, w, h, w/h)
    rootrect.x = x
    rootrect.y = y
    rootrect.w = aw
    rootrect.h = ah
    driver.root:resize(w, h)
    driver.root:refresh()
  end,

  draw = faces.draw,

  root = driver.root:newroot():link(driver.root, 'edges'):takefocus(),
}
