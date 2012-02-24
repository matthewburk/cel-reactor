local cel = require 'cel'

local face = cel.getface('slider')
face.color = false
face.bordercolor = cel.color.rgb(0, 1, 1)
face.borderwidth = 1
face.tickcolor = cel.color.rgb(0, 1, 1)

function face.cairodraw(_ENV, cr, f, t)
  if f.shape then
    local yr = 1.5
    cairo.rectangle(cr, t.thumbsize/2, t.h/2-yr, t.w-t.thumbsize, yr*2)

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

  cairo.set_source_color(cr, f.tickcolor)

  cairo.rectangle(cr, t.w/2, 0, 1, t.h)

  local step = t.step * ((t.w-t.thumbsize)/(t.maxvalue-t.minvalue))
  for x=step+t.thumbsize/2, t.w-t.thumbsize, step do
    cairo.save(cr)
    cairo.translate(cr, x, t.h/2)
    cairo.scale(cr, 5, 5)
    cairo.rectangle(cr, -.5, -.5, 1, 1)
    cairo.fill(cr)
    cairo.restore(cr)
  end

  return _ENV.drawlinks(cr, t)
end

local face = cel.getface('slider.thumb')
face.color = cel.color.rgb(1, .4, 0, .3) 
face.bordercolor = cel.color.rgb(0, 1, 1)
face.borderwidth = 2
