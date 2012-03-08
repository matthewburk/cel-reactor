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

local celreactor = {}

function celreactor.roottowindow(x, y)
  return x, y
end

function celreactor.windowtoroot(x, y, ...)
  x = x - rootrect.x
  y = y - rootrect.y
  x = driver.root.w/rootrect.w * x
  y = driver.root.h/rootrect.h * y
  return math.floor(x + .5), math.floor(y + .5), ...
end

function celreactor.mousedown(x, y, button, alt, ctrl, shift)
  driver.mousedown(celreactor.windowtoroot(x, y, button, alt, ctrl, shift))
end

function celreactor.mouseup(x, y, button, alt, ctrl, shift)
  driver.mouseup(celreactor.windowtoroot(x, y, button, alt, ctrl, shift))
end

function celreactor.mousewheel(x, y, delta, step, alt, ctrl, shift)
  local direction 

  if delta > 0 then
    direction = cel.mouse.wheel.up
  else
    direction =  cel.mouse.wheel.down
  end

  delta = math.abs(delta)
  for i=1,delta do
    driver.mousewheel(celreactor.windowtoroot(x, y, direction, step, alt, ctrl, shift))
  end
end

function celreactor.mousemove(x, y)
  driver.mousemove(celreactor.windowtoroot(x, y))
end

function celreactor.keydown(key, alt, ctrl, shift)
  driver.keydown(key, alt, ctrl, shift)
end

function celreactor.keypress(key, alt, ctrl, shift)
  driver.keypress(key, alt, ctrl, shift)
end

function celreactor.keyup(key, alt, ctrl, shift)
  driver.keyup(key, alt, ctrl, shift)
end

function celreactor.character(c)
  driver.char(c)
end

function celreactor.command(c)
  driver.command(c)
end

function celreactor.tick(millis)
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

local stretch = cel.getlinker('fill.aspect') 

local faces = require((...)..'.faces')

function celreactor.resize(w, h)
  local x, y, aw, ah = stretch(reactor.w, reactor.h, 0, 0, w, h, w/h)
  rootrect.x = x
  rootrect.y = y
  rootrect.w = aw
  rootrect.h = ah
  driver.root:resize(w, h)
  driver.root:refresh()
end

celreactor.draw = faces.draw

celreactor.root = driver.root:takefocus()

function celreactor.resized()
  celreactor.resize(reactor.w, reactor.h)
end


reactor.resized = celreactor.resized
reactor.mousedown = celreactor.mousedown
reactor.mouseup = celreactor.mouseup
reactor.mousewheel = celreactor.mousewheel
reactor.mousemove = celreactor.mousemove
reactor.keydown = celreactor.keydown
reactor.keypress = celreactor.keypress
reactor.keyup = celreactor.keyup
reactor.character = celreactor.character
reactor.command = celreactor.command
reactor.tick = celreactor.tick
reactor.draw = celreactor.draw

celreactor.resize(reactor.w, reactor.h)

--TODO make celreactor read-only
return celreactor
