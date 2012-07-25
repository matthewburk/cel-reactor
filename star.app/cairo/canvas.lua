local cel = require 'cel'

local rot = 0
cel.doafter(100, function()
  rot = rot + .1 % 360
  return 100
end)
do
  local face = cel.getface('cel'):new()
  face.linecolor = cel.color.rgb(0, 1, 1)

  function face.cairodraw(_ENV, cr, f, t)
    cairo.set_source_color(cr, f.linecolor)

    local shapes = t.appstatus

    local nshapes = #shapes

    for i, shape in ipairs(shapes) do
      local points = shape.points

      cr:save()

      if i ~= nshapes then
        cairo.translate(cr, t.w/2, t.h/2)
        cairo.rotate(cr, rot * math.pi/180)
        cairo.translate(cr, -t.w/2, -t.h/2)
      end

      for j = 1, #points, 10 do
        cr:move_to(points[j], points[j+1])

        for n=j+2, j+20, 2 do
          local x, y = points[n], points[n+1]
          if x and y then
            cr:line_to(x, y)
          end
        end

        local h, s, l, a = cel.color.tohsl(shape.color)
        cairo.set_source_color(cr, cel.color.hsl((h+(10*(j/20))) % 360, s, l, a))
        cr:fill_preserve()

        cairo.set_source_color(cr, shape.linecolor)
        cr:set_line_width(shape.linewidth)
        cr:stroke()
      end

      cr:restore()
    end
  end

  face:register('@poly')
end

return function()
  local canvas = cel.grip.new(0, 0, '@poly')

  canvas.shapes = {}

  canvas:setappstatus(canvas.shapes)

  local function makenewshape(canvas)
    canvas.shapes[#canvas.shapes+1] = {
      points = {},
      color = cel.color.rgb8(204, 39, 201),
      linecolor = cel.color.rgb(1, 1, 0),
      linewidth = 2,
    }

    return canvas.shapes[#canvas.shapes]
  end

  local function currentshape(canvas) 
    return canvas.shapes[#canvas.shapes] or makenewshape(canvas)
  end

  function canvas:onmousedown(button, x, y)
    if button == 'left' and app.tool == 'polygon' then
      local shape = currentshape(self)
      local points = shape.points

      local n = #points
      points[n+1]=x
      points[n+2]=y
      self:refresh()
    end
  end

  function canvas:onmousemove(x, y)
    if cel.mouse:isdown('left') and app.tool == 'freehand' then
      local shape = currentshape(self)
      local points = shape.points
      local n = #points
      points[n+1]=x
      points[n+2]=y
      self:refresh()

      if n > 10^2*3 then
        table.remove(points, 1)
        table.remove(points, 1)
      end
    end
  end

  function canvas:onkeypress(key)
    if key == 'delete' then
      local shape = currentshape(self)
      shape.points = {}
    elseif key == 'backspace' then
      local shape = currentshape(self)
      local points = shape.points
      points[#points] = nil
      points[#points] = nil
    elseif key == 'up' then
      local shape = currentshape(self)
      local h, s, l, a = cel.color.tohsl(shape.color)
      shape.color = cel.color.hsl(h + 10, s, l, a)
    end
    self:refresh()
  end

  function canvas:onmousewheel(dir, x, y)
    local shape = currentshape(self)
    local h, s, l, a = cel.color.tohsl(shape.color)

    if dir == cel.mouse.wheel.up then
      shape.color = cel.color.hsl(h + 10, s, l, a)
    else
      shape.color = cel.color.hsl(h - 10, s, l, a)
    end
    self:refresh()
  end

  function canvas:newshape()
    makenewshape(self)
    return self
  end

  return canvas
end
