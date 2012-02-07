local cel = require 'cel'

do --extended cairo functions
  local torgb = cel.color.torgb

  function cairo.set_source_color(cr, color)
    cairo.set_source_rgba(cr, torgb(color))
  end

  function cairo.drawstring(cr, font, x, y, text, i, j)
    i = i or 1
    j = j or #text

    if j < i then 
      return 
    end

    cairo.set_font_face(cr, font.cairofont)
    cairo.set_font_size(cr, font.size)
    cairo.save(cr)
    cairo.move_to(cr, x, y)
    cairo.show_text(cr, text, i, j)
    cairo.restore(cr)
  end

  --x, y specify left top of string
  function cairo.drawstringlt(cr, font, x, y, text, i, j) 
    i = i or 1
    j = j or #text

    if j < i then 
      return 
    end

    cairo.set_font_face(cr, font.cairofont)
    cairo.set_font_size(cr, font.size)

    local xmin = font:measurebbox(text)
    cairo.save(cr)
    cairo.move_to(cr, x - xmin, y + font.ascent)
    cairo.show_text(cr, text, i, j)
    cairo.restore(cr)
  end
end


local _ENV = {
  color = cel.color.rgb(0, 0, 0),
  bordercolor = cel.color.rgb(1, 1, 1),
  textcolor = cel.color.rgb(1, 0, 0),
  description = false,
}

do --drawlinks
  --TODO need to fix dirty rect stystem, it does not work in all cases
  local function updaterect(t, r)
    local ur = description.updaterect
    if r.r < ur.l or r.b < ur.t or r.l > ur.r or r.t > ur.b then
      return false
    end
    return true
  end

  function _ENV.drawlinks(cr, t)
    for i = #t,1,-1 do
      local t = t[i]
      if true or t.refresh or updaterect(t, t.clip) then 
        local face = t.face.select and t.face:select(t) or t.face
        if face.cairodraw then 
          cairo.save(cr)
          cairo.rectangle(cr, t.x, t.y, t.w, t.h)
          cairo.clip(cr)
          cairo.translate(cr, t.x, t.y)

          local color, bordercolor, textcolor = _ENV.color, _ENV.bordercolor, _ENV.textcolor

          if face.color and face.color ~= 'current' then
            _ENV.color = face.color
          end
          if face.textcolor and face.textcolor ~= 'current' then
            _ENV.textcolor = face.textcolor
          end
          if face.bordercolor and face.bordercolor ~= 'current' then
            _ENV.bordercolor = face.bordercolor
          end

          face.cairodraw(_ENV, cr, face, t) 
          _ENV.color, _ENV.bordercolor, _ENV.textcolor = color, bordercolor, textcolor

          cairo.restore(cr)
        end
      end
    end
  end
end

do --cel face
  local face = cel.getface('cel')

  face.font = cel.loadfont('code', 12)
  face.color = 'current'
  face.bordercolor = 'current' 
  face.textcolor = false
  face.borderwidth = 1 
  face.shape = false

  function face.cairodraw(_ENV, cr, f, t)
    if f.color then
      cairo.rectangle(cr, 0, 0, t.w, t.h)

      if f.border then
        cairo.set_source_color(cr, _ENV.color)
        cairo.fill_preserve(cr)
        cairo.set_source_color(cr, _ENV.bordercolor)
        cairo.stroke(cr)
      else
        cairo.set_source_color(cr, _ENV.color)
        cairo.fill(cr)
      end
    end

    return _ENV.drawlinks(cr, t)
  end
end

require((...)..'.label')
require((...)..'.text')
require((...)..'.button')
require((...)..'.textbutton')
require((...)..'.editbox')
require((...)..'.window')
require((...)..'.scroll')
require((...)..'.grip')


do
  local stretch = cel.getlinker('fill.aspect') 
  local texture
  local surface
  local cr
  local surfacew = 0
  local surfaceh = 0

  return {
    draw = function()
      reactor.graphics.pushstate2d(reactor.w, reactor.h)
      reactor.graphics.setcolor(1, 1, 1)

      local description = cel.describe()
      local t = description.description

      if surfacew ~= t.w or surfaceh ~= t.h then
        surfacew, surfaceh = t.w, t.h
        if texture then texture:destroy() end
        if surface then surface:destroy() end
        if cr then cr:destroy() end

        texture = reactor.graphics.texture.create(t.w, t.h)
        surface = cairo.surface.create(t.w, t.h)
        cr = cairo.create(surface)
      end

      local r = description.updaterect

      do cairo.save(cr)
        cairo.rectangle(cr, r.l, r.t, r.r-r.l, r.b-r.t)
        cairo.clip(cr)
        cairo.rectangle(cr, t.x, t.y, t.w, t.h)
        cairo.clip(cr)

        cairo.translate(cr, t.x, t.y)
        cairo.rectangle(cr, 0, 0, t.w, t.h)

        cairo.set_source_rgb(cr, 0, 0, 0)
        cairo.fill(cr)

        cairo.set_line_width(cr, 1)

        _ENV.drawlinks(cr, t)
      end cairo.restore(cr)

      reactor.graphics.updatetexture(texture, surface, r.l, r.t, r.r-r.l, r.b-r.t)

      do
        local x, y, aw, ah = stretch(reactor.w, reactor.h, 0, 0, t.w, t.h, t.w/t.h)

        if x > 0 then
          reactor.graphics.fillrect(0, 0, x, ah)
          reactor.graphics.fillrect(x+aw, 0, x+1, ah)
        elseif y > 0 then
          reactor.graphics.fillrect(0, 0, aw, y)
          reactor.graphics.fillrect(0, y+ah, aw, y+1)
        end

        reactor.graphics.drawtexture(texture, x, y, aw, ah, 0, 0, t.w, t.h)
      end

      reactor.graphics.popstate()
    end
  }
end
--[[
function _ENV.lerp(a, b, p)
  return a + p * (b - a)
end

function _ENV.smoothstep(a, b, p)
  return lerp(a, b, p*p*(3-2*p))
end

function _ENV.rlerp(a, b, c)
  return (c - a)/(b - a);
end

function cairox.roundrect(cr, x, y, w, h, r)
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
--]]
