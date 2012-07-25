local cel = require 'cel'

local face = cel.getface('plot')

face.textcolor = 'current'
face.color = 'current'
face.bordercolor = false
face.borderwidth = 1
face.linewidth = 1
face.rangecolor = cel.color.rgb(1, 1, 1)
face.domaincolor = cel.color.rgb(1, 1, 1)

local _w, _h = 512, 512

face.texture = reactor.graphics.texture.create(_w, _h)
face.surface = cairo.surface.create(_w, _h)
face.cr = cairo.create(face.surface)

function face.rdraw(_ENV, f, t)
  face.cairodraw(_ENV, f.cr, f, t, _w, _h)

  reactor.graphics.updatetexture(f.texture, f.surface)

  reactor.graphics.setcolorf(1, 1, 1)
  reactor.graphics.drawtexture(f.texture, 0, 0, t.w, t.h)

  return _ENV.rdrawlinks(t)
end

local firsttime = cel.timer()

function face.cairodraw(_ENV, cr, f, t, w, h)

  w = w or t.w
  h = h or t.h

  if f.color then
    cairo.set_source_color(cr, _ENV.color)
    cairo.rectangle(cr, 0, 0, w, h)
    cairo.fill(cr)
  end

  local now = cel.timer()

  local data = t.data
  local domainsize = data.domain[2] - data.domain[1]
  local rangesize = data.range[2] - data.range[1]
  local scalew, scaleh = w/domainsize, h/rangesize

  --cairo.cel_show_textlt(cr, f.font, 10, 10, string.format("%.0f", data[data.n][2]))

  if f.rangecolor then
    cr:save()
      cr:scale(w, scaleh)
      for i = data.range[1], data.range[2], data.range.mod do
        cr:move_to(0, i)
        cr:line_to(1, i)
      end
    cr:restore()

    cairo.set_source_color(cr, f.rangecolor)
    cairo.set_line_width(cr, .5)
    cr:stroke()
  end

  --time lines
  if f.domaincolor then
    cr:save()
      cr:scale(scalew, scaleh)

      local mod = data.domain.mod 
      cr:translate(-data[1][1] % mod, 0)

      for i = -mod, domainsize, mod do
        cr:move_to(i, data.range[1])
        cr:line_to(i, data.range[2])
      end
    cr:restore()

    cairo.set_source_color(cr, f.domaincolor)
    cr:save()
      cr:set_line_width(.5)
      cr:set_dash(1, 3)
      cr:stroke()
    cr:restore()
  end

  cr:set_line_width(f.linewidth)

  cr:save()
    cr:scale(scalew, scaleh)
    cr:translate(-data[1][1], 0)
    cr:move_to(data[1][1], rangesize-data[1][2])
    cr:line_to(data[1][1], rangesize-data[1][2])

    for i = 2, #data do
      local p = data[i]
      cr:line_to(p[1], rangesize-p[2])
    end
  cr:restore()
  cr:save()
  cr:set_source_rgb(0, 1, 1)
    cr:stroke()
  cr:restore()
end

