local cel = require 'cel'

do --extended cairo functions
  local torgb = cel.color.torgb

  function cairo.set_source_color(cr, color)
    cairo.set_source_rgba(cr, torgb(color))
  end

  function cairo.drawstring(cr, font, x, y, text)
    cairo.set_font_face(cr, font.cairofont)
    cairo.set_font_size(cr, font.size)
    cairo.save(cr)
    cairo.move_to(cr, x, y)
    cairo.show_text(cr, text)
    --cairo.show_text(cr, text, i, j)
    cairo.restore(cr)
  end

  --x, y specify left top of string
  function cairo.drawstringlt(cr, font, x, y, text) 
    local _, _, xmin = font:measure(text)
    cairo.set_font_face(cr, font.cairofont)
    cairo.set_font_size(cr, font.size)
    cairo.save(cr)
    cairo.move_to(cr, x - xmin, y + font.ascent)
    cairo.show_text(cr, text)
    cairo.restore(cr)
  end

  function cairo.roundrect(cr, x, y, w, h, r)
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
--[[
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
end

local _ENV = {
  color = cel.color.rgb(0, 0, 0),
  bordercolor = cel.color.rgb(1, 1, 1),
  textcolor = cel.color.tint(cel.color.rgb(0, 1, 1), .7),
  metadescription = false,
  X=0,
  Y=0,
}

do --drawlinks
  --TODO need to fix dirty rect stystem, it does not work in all cases
  local function updaterect(t, r)
    local ur = _ENV.metadescription.updaterect
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

          local X,Y = _ENV.X, _ENV.Y
          _ENV.X = _ENV.X + t.x
          _ENV.Y = _ENV.Y + t.y
          face.cairodraw(_ENV, cr, face, t) 
          _ENV.X = X
          _ENV.Y = Y
          _ENV.color, _ENV.bordercolor, _ENV.textcolor = color, bordercolor, textcolor

          cairo.restore(cr)
        end
      end
    end
  end
end

do --rdrawlinks
  function _ENV.rdrawlinks(t)
    for i = #t,1,-1 do
      local t = t[i]
      local face = t.face.select and t.face:select(t) or t.face
      if face.rdraw then
        app.window.graphics.pushmatrix()
        app.window.graphics.clipltrb(t.clip.l, t.clip.t, t.clip.r, t.clip.b)
        --TODO set clip
        app.window.graphics.translate(t.x, t.y)

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

        face.rdraw(_ENV, face, t) 
        _ENV.color, _ENV.bordercolor, _ENV.textcolor = color, bordercolor, textcolor

        app.window.graphics.popmatrix() 
      end
    end
  end
end

do --cel face
  local face = cel.getface('cel')

  face.font = cel.loadfont('default', 12)
  face.color = false
  face.bordercolor = false
  face.textcolor = false
  face.borderwidth = false
  face.shape = 'rect'
  face.image = {
    texture = app.window.graphics.texture.create(32, 32),
    l = 2,
  }

  assert(face.image.texture)

  do
    local surface = cairo.surface.create(32, 32)
    local cr = cairo.create(surface)
    cr:rectangle(0, 0, 32, 32)
    cr:set_line_width(2)
    cr:set_source_rgb(1, 1, 1)
    cr:stroke()

    surface:flush()
    app.window.graphics.updatetexture(face.image.texture, surface:get_data())
    cr:destroy()
    surface:destroy()
  end

  function face.rdraw(_ENV, f, t)
    if f.image then
      --if f.color then
        app.window.graphics.setcolor(_ENV.color)
      --end
      app.window.graphics.draw9grid(f.image.texture, 0, 0, t.w, t.h, f.image.l)
    end

    return _ENV.rdrawlinks(t)
  end
  
  function face.cairodraw(_ENV, cr, f, t)
    if f.shape then
      cairo.rectangle(cr, 0, 0, t.w, t.h)

      if f.color then
        cairo.set_source_color(cr, _ENV.color)
        cairo.fill_preserve(cr)
      end

      if f.bordercolor and f.borderwidth then
        cairo.set_source_color(cr, _ENV.bordercolor)
        cairo.set_line_width(cr, f.borderwidth)
        cairo.stroke(cr)
      end

      cairo.new_path(cr)
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
require((...)..'.plot')
require((...)..'.slider')
require((...)..'.menu')

return function(cr, t, metadescription)
  _ENV.metadescription = metadescription

  local r = metadescription.updaterect

  cr:save()
  do 
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
  end 
  cr:restore()
end

