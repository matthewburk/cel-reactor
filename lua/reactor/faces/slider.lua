local cel = require 'cel'

local face = cel.getface('slider')
face.color = false
face.bordercolor = cel.color.rgb(0, 1, 1)
face.borderwidth = 1
face.tickcolor = cel.color.rgb(0, 1, 1)

function face.cairodraw(_ENV, cr, f, t)
  if f.shape then
    local yr = 1.5
    cr:rectangle(t.thumbsize/2, t.h/2-yr, t.w-t.thumbsize, yr*2)

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

  cr:set_source_color(f.tickcolor)

  cr:rectangle(t.w/2, 0, 1, t.h)

  local step = t.step * ((t.w-t.thumbsize)/(t.maxvalue-t.minvalue))
  for x=step+t.thumbsize/2, t.w-t.thumbsize, step do
    cr:save()
    cr:translate(x, t.h/2)
    cr:scale(5, 5)
    cr:rectangle(-.5, -.5, 1, 1)
    cr:fill()
    cr:restore()
  end

  return _ENV.drawlinks(cr, t)
end

local face = cel.getface('slider.thumb')
face.color = cel.color.rgb(1, .4, 0, .3) 
face.bordercolor = cel.color.rgb(0, 1, 1)
face.borderwidth = 2
