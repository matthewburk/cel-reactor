local cel = require 'cel'

app.colors = {
  red=cel.color.rgb(1, 0, 0),
  yellow=cel.color.rgb(1, 1, 0),
  green=cel.color.rgb(0, 1, 0),
  blue=cel.color.rgb(0, 0, 1),

  blue5=cel.color.setsaturation(cel.color.rgb(0, 0, 1), .5),

  cyan=cel.color.rgb(0, 1, 1),
  cyan5=cel.color.setsaturation(cel.color.rgb(0, 1, 1), .5),
  cyan8=cel.color.setsaturation(cel.color.rgb(0, 1, 1), .8),

  black=cel.color.rgb(0, 0, 0),
  gray1=cel.color.rgb(.1, .1, .1),
  gray2=cel.color.rgb(.2, .2, .2),
  gray3=cel.color.rgb(.3, .3, .3),
  gray4=cel.color.rgb(.4, .4, .4),
  gray5=cel.color.rgb(.5, .5, .5),
  gray6=cel.color.rgb(.6, .6, .6),
  gray7=cel.color.rgb(.7, .7, .7),
  gray8=cel.color.rgb(.8, .8, .8),
  gray9=cel.color.rgb(.9, .9, .9),
  white=cel.color.rgb(1, 1, 1),

  
  oceanblue=cel.color.rgb8(0, 136, 204),
}

app.colors.themecolor = app.colors.oceanblue
app.colors.themebordercolor = app.colors.white
app.colors.themetextcolor = app.colors.white
app.colors.themecomplement = cel.color.getcomplement(app.colors.themecolor, nil, .6, 1)
app.colors.themecomplementlight = cel.color.getcomplement(app.colors.themecolor, nil, .8, 1)

local _ENV = {
  color = app.colors.themecolor,
  bordercolor = app.colors.themebordercolor,
  textcolor = app.colors.themetextcolor,

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
          cr:save()
          cr:rectangle(t.x, t.y, t.w, t.h)
          cr:clip()
          cr:translate(t.x, t.y)

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

          cr:restore()
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

  face.font = cel.loadfont('default', 14)
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
      cr:rectangle(0, 0, t.w, t.h)

      if f.color then
        cr:set_source_color(_ENV.color)
        cr:fill_preserve()
      end

      if f.bordercolor and f.borderwidth then
        cr:set_source_color(_ENV.bordercolor)
        cr:set_line_width(f.borderwidth)
        cr:stroke()
      end

      cr:new_path()
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
require((...)..'.listbox')
require((...)..'.grip')
require((...)..'.plot')
require((...)..'.slider')
require((...)..'.menu')
require((...)..'.accordion')

return function(cr, t, metadescription)
  assert(cr)
  _ENV.metadescription = metadescription

  local r = metadescription.updaterect

  cr:save()
  do 
    cr:rectangle(r.l, r.t, r.r-r.l, r.b-r.t)
    cr:clip()
    cr:rectangle(t.x, t.y, t.w, t.h)
    cr:clip()

    cr:translate(t.x, t.y)
    cr:rectangle(0, 0, t.w, t.h)

    cr:set_source_rgb(0, 0, 0)
    cr:fill()

    cr:set_line_width(1)

    _ENV.drawlinks(cr, t)
  end 
  cr:restore()
end

