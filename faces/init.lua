local _ENV = setmetatable({}, {__index=_G})
setfenv(1, _ENV)

local cel = require 'cel'
local decodef = cel.color.decodef
local cairo = cairo

_ENV.cairo = cairo
_ENV.cr = nil
_ENV.description = nil

function cairo.cel_set_source_rgba(cr, color)
  cr:set_source_rgba(decodef(color))
end

function cairo.cel_roundrect(cr, x, y, w, h, r)
  if not r then
    cr:rectangle(x, y, w, h);
  else
    local degrees = math.pi / 180.0;
    cr:new_sub_path();
    cr:arc(x + w - r, y + r, r, -90 * degrees, 0 * degrees);
    cr:arc(x + w - r, y + h - r, r, 0 * degrees, 90 * degrees);
    cr:arc(x + r, y + h - r, r, 90 * degrees, 180 * degrees);
    cr:arc(x + r, y + r, r, 180 * degrees, 270 * degrees);
    cr:close_path();
  end
end

function cairo.cel_show_text(cr, font, x, y, text, i, j)
  i = i or 1
  j = j or #text

  if j < i then 
    return 
  end

  cr:set_font_face(font.cairofont)
  cr:set_font_size(font.size)
  cr:save()
  cr:move_to(x, y)
  cr:show_text(text, i, j)
  cr:restore()
end

--x, y specify left top of string
function cairo.cel_show_textlt(cr, font, x, y, text, i, j) 
  i = i or 1
  j = j or #text

  if j < i then 
    return 
  end

  cr:set_font_face(font.cairofont)
  cr:set_font_size(font.size)

  local xmin = font:measurebbox(text)
  cr:save()
  cr:move_to(x - xmin, y + font.ascent)
  cr:show_text(text, i, j)
  cr:restore()
end

function _ENV.updaterect(t, r)
  local ur = description.updaterect
  if r.r < ur.l or r.b < ur.t or r.l > ur.r or r.t > ur.b then
    return false
  end
  return true
end

function _ENV.drawlinks(t)
  for i = #t,1,-1 do
    local t = t[i]
    if t.refresh or updaterect(t, t.clip) then
      local face = t.face.select and t.face:select(t) or t.face
      if face.draw then 
        local _cr = cr
        cairo.save(cr)
        cairo.rectangle(cr, t.x, t.y, t.w, t.h)
        cairo.clip(cr)
        cairo.translate(cr, t.x, t.y)
        face:draw(t) 
        cr = _cr
        cairo.restore(cr)
      end
    end
  end
end

do --cel face
  local face = cel.getface('cel')

  face.font = cel.loadfont('dejavu sans mono', 12)
  face.textcolor = cel.color.encodef(1, 1, 1)
  face.fillcolor = false --cel.color.encodef(0, 0, 0)
  face.linecolor = cel.color.encodef(1, 1, 1)
  face.linewidth = false 
  face.radius = false

  function face.draw(f, t)
    local cr = face.cr or cr

    if f.fillcolor then
      cairo.cel_set_source_rgba(cr, f.fillcolor)
      cairo.cel_roundrect(cr, 0, 0, t.w, t.h, f.radius)
      cairo.fill(cr)
    end

    if f.linewidth and f.linecolor then
      cairo.set_line_width(cr, f.linewidth)
      cairo.cel_set_source_rgba(cr, f.linecolor)
      local _, offset = math.modf(f.linewidth/2)
      cairo.cel_roundrect(cr, 0 +offset, 0 + offset, t.w, t.h, f.radius)
      cairo.stroke(cr)
    end

    return drawlinks(t)
  end
end

cel.getface('col').draw = function(f, t) return drawlinks(t) end
cel.getface('row').draw = function(f, t) return drawlinks(t) end
cel.getface('col.slot').draw = function(f, t) return drawlinks(t) end
cel.getface('row.slot').draw = function(f, t) return drawlinks(t) end

local root = cel.getface('root'):new {
  texture = false,
  surface = false,
  cr = false,
  surfacew = 0,
  surfaceh = 0,
}

local function init(f, w, h)
  if f.surfacew ~= w or f.surfaceh ~= h then
    f.surfacew, f.surfaceh = w, h
    if f.texture then f.texture:destroy() end
    if f.surface then f.surface:destroy() end
    if f.cr then f.cr:destroy() end

    f.texture = reactor.graphics.texture.create(w, h)
    f.surface = cairo.surface.create(w, h)
    f.cr = cairo.create(f.surface)
    _ENV.cr = f.cr
  end
end

local function lerp(a, b, p)
  return a + p * (b - a)
end

local function smoothstep(a, b, p)
  return lerp(a, b, p*p*(3-2*p))
end

local function rlerp(a, b, c)
  return (c - a)/(b - a);
end

function root.draw(f, t)
  local tbeg = reactor.timermillis()
  init(f, t.w, t.h)
  local cr = f.cr

  cairo.save(cr)

  local ur = description.updaterect
  cairo.rectangle(cr, ur.l, ur.t, ur.r-ur.l, ur.b-ur.t)
  cairo.clip(cr)

  cairo.rectangle(cr, t.x, t.y, t.w, t.h)
  cairo.clip(cr)
  cairo.translate(cr, t.x, t.y)
  cairo.set_source_rgb(cr, 0, 0, 0)
  cairo.set_line_width(cr, 1)
  cairo.rectangle(cr, 0, 0, t.w, t.h)
  cairo.fill(cr)

  drawlinks(t)

  cairo.restore(cr)

  --[[
  cairo.set_source_rgba(cr, math.random(0, 1), math.random(0, 1), math.random(0, 1), .5)
  cairo.rectangle(cr, ur.l, ur.t, ur.r-ur.l, ur.b-ur.t)
  cairo.set_line_width(cr, 4)
  cairo.fill(cr)
  --]]
  --

   --print('cairo took', reactor.timermillis() - tbeg)


  local tbeg = reactor.timermillis()
  reactor.graphics.updatetexture(f.texture, f.surface, ur.l, ur.t, ur.r-ur.l, ur.b-ur.t)
  --print('updatetexture took', reactor.timermillis() - tbeg)



  reactor.graphics.pushmatrix()
  reactor.graphics.loadidentity()
  reactor.graphics.translate(t.w/2, t.h/2)
  --reactor.graphics.rotate(math.floor(lerp(-90, 90, rlerp(0, t.w, cel.mouse:xy()))))
  reactor.graphics.scale(t.w, t.h)
  reactor.graphics.drawtexture(f.texture, -.5, -.5, 1, 1, 0, 0, t.w, t.h)
  reactor.graphics.popmatrix()

end

require('faces.button')(_ENV)
require('faces.textbutton')(_ENV)
require('faces.text')(_ENV)
require('faces.editbox')(_ENV)
require('faces.grip')(_ENV)
require('faces.label')(_ENV)
require('faces.scroll')(_ENV)
require('faces.listbox')(_ENV)
require('faces.window')(_ENV)
require('faces.marker')(_ENV)

return {
  draw = function()
    local t, changed = cel.describe()
    reactor.graphics.pushstate2d(reactor.w, reactor.h)
    reactor.graphics.setcolor(1, 1, 1)

    _ENV.description = t
    if changed then
      root.draw(root, t.description)
    end

    reactor.graphics.popstate()
  end
}
