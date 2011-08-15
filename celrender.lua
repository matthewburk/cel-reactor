local cel = require 'cel' 
local cr

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
    cr = reactor.cr
  end
end

local decodef = cel.color.decodef
local function setcolor(color)
  if not color then return false end
  local r, g, b, a = decodef(color)
  if a == 0 then return false end
  cr:set_source_rgba(r, g, b, a);
  return true
end

local function clip(t)  
  cr:reset_clip(t.l, t.t, t.r, t.b)
  cr:rectangle(t.l, t.t, t.r-t.l, t.b-t.t)
  cr:clip()
end

local _linewidth = 1
local function setlinewidth(n)
  _linewidth = n
  cr:set_line_width(n)
end

local function strokerect(x, y, w, h, r)
  x = x + (_linewidth*.5)
  y = y + (_linewidth*.5)
  w = w - _linewidth
  h = h - _linewidth

  if not r then
    cr:rectangle(x, y, w, h);
  elseif true then
    local radius = r --/ (w/h)
    local degrees = math.pi / 180.0;
    width = w
    height = h

    cr:new_sub_path();
    cr:arc (x + width - radius, y + radius, radius, -90 * degrees, 0 * degrees);
    cr:arc (x + width - radius, y + height - radius, radius, 0 * degrees, 90 * degrees);
    cr:arc (x + radius, y + height - radius, radius, 90 * degrees, 180 * degrees);
    cr:arc (x + radius, y + radius, radius, 180 * degrees, 270 * degrees);
    cr:close_path();
    
  else
    --[[
     A****BQ
    H      C
    *      *
    G      D
     F****E
    --]]
    cr:move_to(x+r,y)                      -- Move to A
    cr:line_to(x+w-r,y)                    -- Straight line to B
    cr:curve_to(x+w,y,x+w,y,x+w,y+r)       -- Curve to C, Control points are both at Q
    cr:line_to(x+w,y+h-r)                  -- Move to D
    cr:curve_to(x+w,y+h,x+w,y+h,x+w-r,y+h) -- Curve to E
    cr:line_to(x+r,y+h)                    -- Line to F
    cr:curve_to(x,y+h,x,y+h,x,y+h-r)       -- Curve to G
    cr:line_to(x,y+r)                      -- Line to H
    cr:curve_to(x,y,x,y,x+r,y)             -- Curve to A
  end
  
  cr:stroke()
end

local function fillrect(x, y, w, h, r)
  if not r then
    cr:rectangle(x, y, w, h);
  elseif true then
    local radius = r --/ (w/h)
    local degrees = math.pi / 180.0;
    width = w
    height = h

    cr:new_sub_path();
    cr:arc (x + width - radius, y + radius, radius, -90 * degrees, 0 * degrees);
    cr:arc (x + width - radius, y + height - radius, radius, 0 * degrees, 90 * degrees);
    cr:arc (x + radius, y + height - radius, radius, 90 * degrees, 180 * degrees);
    cr:arc (x + radius, y + radius, radius, 180 * degrees, 270 * degrees);
    cr:close_path();
  else
    --[[
     A****BQ
    H      C
    *      *
    G      D
     F****E
    --]]
    
    cr:move_to(x+r,y)                      -- Move to A
    cr:line_to(x+w-r,y)                    -- Straight line to B
    cr:curve_to(x+w,y,x+w,y,x+w,y+r)       -- Curve to C, Control points are both at Q
    cr:line_to(x+w,y+h-r)                  -- Move to D
    cr:curve_to(x+w,y+h,x+w,y+h,x+w-r,y+h) -- Curve to E
    cr:line_to(x+r,y+h)                    -- Line to F
    cr:curve_to(x,y+h,x,y+h,x,y+h-r)       -- Curve to G
    cr:line_to(x,y+r)                      -- Line to H
    cr:curve_to(x,y,x,y,x+r,y)             -- Curve to A
  end

  cr:fill()
end

local function fillarc(x, y, r, angle1, angle2)
  cr:arc(x, y, r, angle1, angle2);
  cr:fill()
end

local function translate(x, y)
  cr:translate(x, y)
end

local function save()
  cr:save()
end

local function restore()
  cr:restore()
end

local function scale(w, h)
  cr:scale(w, h)
end

local function fillstring(font, x, y, text, i, j)
  i = i or 1
  j = j or #text

  if j < i then 
    return 
  end

  cr:set_font_face(font.nativefont)
  cr:set_font_size(font.size)
  cr:save()
  cr:move_to(x, y)
  cr:show_text(text, i, j)
  cr:restore()
end

--x, y specify left top of string
local function fillstringlt(font, x, y, text, i, j)      
  i = i or 1
  j = j or #text

  if j < i then 
    return 
  end

  cr:set_font_face(font.nativefont)
  cr:set_font_size(font.size)

  if font.bbox.xmin ~= 0 then
    local xmin = font:measurebbox(text) --TODO must avoid this
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
      driver.hook.drawroot(t)
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

driver.hook = {
  root = driver.root:newroot():link(driver.root, 'edges');

  drawroot = function(t)
    t.description.face:draw(t.description)
  end;

  graphics = {
    setcolor = setcolor,
    fillrect = fillrect,
    strokerect = strokerect,
    setlinewidth = setlinewidth,
    clip = clip,
    fillstring = fillstring,
    fillstringlt = fillstringlt,
    setfont = setfont,
    scale = scale,
    fillarc = fillarc,
    translate = translate,
    save = save,
    restore = restore,
  };
}

require('cel.faces.cel')(driver.hook.graphics)
require('cel.faces.button')(driver.hook.graphics)
require('cel.faces.textbutton')(driver.hook.graphics)
require('cel.faces.label')(driver.hook.graphics)
require('cel.faces.text')(driver.hook.graphics)
require('cel.faces.grip')(driver.hook.graphics)
require('cel.faces.scroll')(driver.hook.graphics)
require('cel.faces.window')(driver.hook.graphics)

return driver.hook
