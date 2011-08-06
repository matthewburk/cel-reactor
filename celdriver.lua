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

do
  local function initgraphics(w, h)
    if reactor.w ~= w or reactor.h ~= h then
      reactor.w = w
      reactor.h = h
      if reactor.texture then reactor.texture:destroy() end
      if reactor.surface then reactor.surface:destroy() end
      if reactor.cr then reactor.cr:destroy() end
      reactor.texture = reactor.graphics.texture.create(w, h)
      reactor.surface = cairo.surface.create(w, h)
      reactor.cr = cairo.create(reactor.surface)
    end
  end

  function reactor.load()
    initgraphics(reactor.graphics.getwidth(), reactor.graphics.getheight())
    driver.root:resize(reactor.w, reactor.w)

    if driver.hook.load then
      driver.hook.load()
    end
  end

  function reactor.resized(nw, nh)
    initgraphics(nw, nh)
    driver.root:resize(nw, nh)
  end
end

function reactor.draw()
  local w, h = reactor.w, reactor.h
  reactor.graphics.pushstate2d(w,h)
  reactor.graphics.setcolor(1, 1, 1)

  do
    local t, altered = cel.describe()
    if altered then
      local cr = reactor.cr
      cr:set_source_rgb(0, 0, 0)
      cr:rectangle(0, 0, w, h)
      cr:fill()

      cr:save()
      cr:set_line_width(1)
      cel.face.get().cr = cr
      driver.hook.drawroot(cr, t)
      cr:restore()
      reactor.graphics.updatetexture(reactor.texture, reactor.surface)
    end
  end

  reactor.graphics.drawtexture(reactor.texture, 0, 0, w, h)
  reactor.graphics.popstate()
end

function reactor.update(fps)
  driver.timer(reactor.timermillis());
end

do
  local namemap = {
    code = 'fixedsys',
    monospace = 'courier new',
    serif = 'times new roman',
    sansserif = 'arial',
    default = 'arial'
  }

  function driver.loadfont(name, weight, slant, size)
    name = namemap[name] or name 

    local surface = cairo.surface.create(0, 0)
    local nativefont = cairo.font.face_create(name, slant, weight)
    local cr = cairo.create(surface)

    cr:set_font_face(nativefont)
    cr:set_font_size(size)

    local font = {
      nativefont = nativefont;
    }

    --[==[ native textmetrics
    function font:measure(text, i, j)
      if not text or #text < 1 then
        return 0, 0
      end
      local xbr, ybr, w, h, xadv, yadv = cr:text_extents(text, i, j)
      return w, h 
    end

    function font:measurebbox(text, i, j)
      if not text or #text < 1 then
        return 0, 0, 0, 0
      end
      local xbr, ybr, w, h, xadv, yadv = cr:text_extents(text, i, j)
      return xbr, xbr + w, -(ybr + h), -ybr
    end

    function font:measureadvance(text, i, j)
      if not text or #text < 1 then
        return 0
      end
      local xbr, ybr, w, h, xadv, yadv = cr:text_extents(text, i, j)
      return xadv
    end
    --]==]

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

    local function newglyph(fontmetrics, glyph)
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
    end

    font.metrics = setmetatable({}, {__index = newglyph})

    function font.print(font, cr, x, y, text, i, j)
      i = i or 1
      j = j or #text
      if j < i then return end
      cr:set_font_face(font.nativefont)
      cr:set_font_size(size)
      cr:save()
      cr:move_to(x, y)
      cr:show_text(text, i, j)
      cr:restore()
    end

    --x, y specify left top of string
    function font.printlt(font, cr, x, y, text, i, j)      
      i = i or 1
      j = j or #text
      if j < i then return end

      cr:set_font_face(font.nativefont)
      cr:set_font_size(size)

      if font.bbox.xmin ~= 0 then
        local xmin = font:measurebbox(text) --TODO must avoid this shit
        cr:save()
        cr:move_to(x - xmin, y + font.bbox.ymax)
        cr:show_text(text, i, j)
        cr:restore()
      else
        cr:save()
        cr:move_to(x, y + font.bbox.ymax)
        cr:show_text(text, i, j)
        cr:restore()
      end
    end

    return font 
  end
end

function driver.clipboard(command, data)
  if command == 'get' then
    return reactor.clipboard.get()
  elseif command == 'put' then
    reactor.clipboard.put(data)
  end
end

do
  local decodef = cel.color.decodef

  local function setcolor(cr, color)
    if not color then return false end

    local r, g, b, a = decodef(color)

    if a == 0 then return false end

    cr:set_source_rgba(r, g, b, a);
    return true
  end

  local function clip(cr, t)  
    cr:reset_clip(t.l, t.t, t.r, t.b)
    cr:rectangle(t.l, t.t, t.r-t.l, t.b-t.t)
    cr:clip()
  end

  local function strokerect(cr, x, y, w, h, r)
    cr:rectangle(x+.5, y+.5, w-1, h-1);
    cr:stroke()
  end

  local function fillrect(cr, x, y, w, h, r)
    cr:rectangle(x, y, w, h);
    cr:fill()
  end

  local function drawlinks(face, t)
    for i = #t,1,-1 do
      local t = t[i]
      t.face:draw(t)
    end
  end

  local face = cel.face {
    font = cel.loadfont(),
    textcolor = cel.color.encodef(1, 1, 1),
    fillcolor = false,
    linecolor = false,
    draw = function(self, t)
      local cr = self.cr
      if setcolor(cr, self.fillcolor) then
        clip(cr, t.clip)
        fillrect(cr, t.x, t.y, t.w, t.h)
      end
      if setcolor(cr, self.linecolor) then
        clip(cr, t.clip)
        strokerect(cr, t.x, t.y, t.w, t.h)
      end
      return drawlinks(self, t)
    end
  }

  driver.hook = {
    root = driver.root:newroot():link(driver.root, 'edges');
    drawroot = function(cr, t)
      t.description.face:draw(t.description)
    end;

    graphics = {
      setcolor = setcolor,
      fillrect = fillrect,
      strokerect = strokerect,
      clip = clip,
    };
  }
end

return driver.hook
