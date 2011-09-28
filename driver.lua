local M = {}

local cel = require 'cel' 

local driver = cel.installdriver(
  {
    buttons = { left = 1, middle = 2, right = 3, },
    states = { unknown = 'unknown', normal = 'normal', pressed = 'pressed', },
    wheeldirection = { up = 1, down = -1, },
  },
  {
    keys = setmetatable({}, {__index = function(t, k, v) return k end}),
    keystates = { unknown = 'unknown', normal = 'normal', pressed = 'pressed', }
  })
  
function reactor.mousepressed(x, y, button, alt, ctrl, shift)
  driver.mousedown(x, y, button, alt, ctrl, shift)
end

function reactor.mousereleased(x, y, button, alt, ctrl, shift)
  driver.mouseup(x, y, button, alt, ctrl, shift)
end

function reactor.mousewheel(delta, step)
  local direction 

  if delta > 0 then
    direction = cel.mouse.wheeldirection.up
  else
    direction =  cel.mouse.wheeldirection.down
  end

  local x, y = cel.mouse:xy()

  delta = math.abs(delta)
  for i=1,delta do
    driver.mousewheel(x, y, direction, step)
  end
end

function reactor.mousemove(x, y)
  driver.mousemove(x, y)
end

function reactor.keypressed(key, alt, ctrl, shift, autorepeat)
  if autorepeat then
    driver.keypress(key, alt, ctrl, shift)
  else
    driver.keydown(key, alt, ctrl, shift)
  end
end

function reactor.keyreleased(key)
  driver.keyup(key)
end

function reactor.character(c)
  driver.char(c)
end

function reactor.command(c)
  driver.command(c)
end

function reactor.load()
  driver.root:resize(reactor.graphics.getwidth(), reactor.graphics.getheight())
  if M.load then
    M.load(reactor.graphics.getwidth(), reactor.graphics.getheight())
  end
end

function reactor.resized(nw, nh)
  driver.root:resize(reactor.graphics.getwidth(), reactor.graphics.getheight())
end

function reactor.draw()
  reactor.graphics.pushstate2d(reactor.graphics.getwidth(), reactor.graphics.getheight())
  reactor.graphics.setcolor(1, 1, 1)

  if M.draw then
    M.draw(cel.describe())
  end

  reactor.graphics.popstate()
end

do
  local lastfps
  function reactor.update(fps)
    if fps ~= lastfps then
      lastfps = fps
      print('fps', fps)
    end
    driver.timer(reactor.timermillis());
  end
end

function driver.clipboard(command, data)
  if command == 'get' then
    return reactor.clipboard.get()
  elseif command == 'put' then
    reactor.clipboard.put(data)
  end
end

local celfontfaces = {
  code = 'fixedsys',
  monospace = 'courier new',
  serif = 'times new roman',
  sansserif = 'arial',
  default = 'arial'
}
function driver.loadfont(name, weight, slant, size)
  name = celfontfaces[name] or name 

  local surface = cairo.surface.create(0, 0)
  local nativefont = cairo.font.face_create(name, slant, weight)
  local cr = cairo.create(surface)

  cr:set_font_face(nativefont)
  cr:set_font_size(size)

  local font = {
    nativefont = nativefont,
    name=name,
    weight=weight,
    slant=slant,
    size=size,
  }

  local charset = 
  [[ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghifklmnopqrstuvwxyz`1234567890-=~!@#$%^&*()_+[]\\{}|;:\'"<>?,./]]

  local xbr, ybr, w, h, xadv, yadv = cr:text_extents(charset)

  local ymin = -(ybr + h)
  local ymax = -ybr

  local xmin = 32000 
  local xmax = -32000 
  for i = 1, #charset do
    local xbr, ybr, w, h, xadv, yadv = cr:text_extents(charset:sub(i, i))
    if xbr < xmin then xmin = xbr end
    if xbr + w > xmax then xmax = xbr + w end
  end

  font.bbox = {
    xmin = xmin,
    xmax = xmax,
    ymin = ymin,
    ymax = ymax,
  }

  do
    local ascent, descent, height = cr:font_extents()
    font.lineheight = height
    font.ascent = ascent
    font.descent = descent

    if ascent > font.bbox.ymax then
      --this is not acceptable, cel algorithms need to look as ascent instaed of 
      --looking at bbox alone
      print('useing ascent as ymax for', name, weight, slant, size)
      font.bbox.ymax = ascent
    end
  end

  font.metrics = setmetatable({}, {__index = function(fontmetrics, glyph)
    local char = string.char(glyph)
    local xbr, ybr, w, h, xadv, yadv = cr:text_extents(char)      

    fontmetrics[glyph] = {
      glyph = glyph,
      char = char,
      advance = xadv,
      xmin = xbr,
      xmax = xbr + w,
      ymin = -(ybr + h),
      ymax = -ybr,
    }

    return fontmetrics[glyph]
  end})

  return font 
end

M.root = driver.root:newroot():link(driver.root, 'edges')
M.root:takefocus()

return M
