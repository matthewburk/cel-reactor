local cel = require 'cel'

local function lerp(a, b, p)
  return a + p * (b -a)
end

return function(_ENV)
  setfenv(1, _ENV)

  local altimeter = cel.getface('altimeter') 

  altimeter.radius = false
  altimeter.fillcolor = false
  altimeter.linewidth = 1
  altimeter.linecolor = cel.color.rgb(1, 0, 0)

  altimeter.backgroundcolor = cel.color.rgb(.1, .1, .1)
  altimeter.bgpattern = cairo.pattern.create_radial(0, 0, .5, 0, 0, 0)
  altimeter.bgpattern:add_color_stop(0, 0, 0, 0, 1)
  altimeter.bgpattern:add_color_stop(.15, .07, .07, .07, 1)

  altimeter.minorticklength = .1 --* radius
  altimeter.minortickwidth = 1.5 
  altimeter.minortickcount = 50
  altimeter.minortickcolor = cel.color.rgb(1, 1, 1)

  altimeter.majorticklength = .15 --* radius
  altimeter.majortickwidth = 3 
  altimeter.majortickcount = 10 
  altimeter.majortickcolor = cel.color.rgb(1, 1, 1)
  altimeter.majorticktextcolor = cel.color.shade(.1, cel.color.rgb(1, 1, 1))

  altimeter.pivotradius = .05 --* radius
  altimeter.needle100radius = .9 --* radius
  altimeter.needle1kradius = .6 --* radius
  altimeter.needle10kradius = 1 --* radius

  altimeter.pivotcolor = cel.color.rgb(0, 0, 0)
  altimeter.needle100color = cel.color.rgb(1, 1, 1)
  altimeter.needle1kcolor = cel.color.shade(.1, cel.color.rgb(1, 1, 1))
  altimeter.needle10kcolor = cel.color.shade(.2, cel.color.rgb(1, 1, 1))

  local function show_text_center(cr, s, xb, yb, w, h)
    local cx = w/2 + xb 
    local cy = h/2 + yb 
    cairo.rel_move_to(cr, -cx, -cy)
    cairo.show_text(cr, s)
  end
  function altimeter.draw(f, t)
    if f.fillcolor then
      cairo.extcel_set_source_color(cr, f.fillcolor)
      cairo.ext_roundrect(cr, 0, 0, t.w, t.h, f.radius)
    end

    if f.linewidth and f.linecolor then
      cairo.set_line_width(cr, f.linewidth)
      cairo.extcel_set_source_color(cr, f.linecolor)
      cairo.ext_roundrect(cr, 0, 0, t.w, t.h, f.radius)
      cairo.stroke(cr)
    end

    drawlinks(t)

    cr:save() 
    do
      local xc = (t.w/2)
      local yc = (t.h/2)
      local r = math.min(t.w, t.h)/2
      local a1 = -math.pi/2
      local a2 = -math.pi/2 + math.pi * 2

      do --background
        cr:save()
          cr:translate(xc, yc)
          cr:scale(r*2, r*2)
          cr:set_source(f.bgpattern)
          cr:arc(0, 0, .5, 0, math.pi*2)
          cr:fill()
        cr:restore()

        cr:save()
          cr:translate(xc, yc)
          cr:scale(r, r)
          cr:arc(0, 0, .5, 0, math.pi*2)
        cr:restore()
        cr:set_line_width(1)
        cr:set_source_rgb(0, 0, 0)
        cr:stroke_preserve()
        cr:set_source_rgb(.08, .08, .08)
        cr:fill()
      end

      r = r - 5

      local rminortick = r - r * f.minorticklength
      local rmajortick = r - r * f.majorticklength
  
      cr:set_line_join('round')

      do --minorticks
        for i = 0, f.minortickcount do
          local a = lerp(a1, a2, i/f.minortickcount)
          cr:new_sub_path()
          cr:arc(xc, yc, r, a, a)
          cr:arc(xc, yc, rminortick, a, a)
        end

        cairo.extcel_set_source_color(cr,f.minortickcolor)
        cr:set_line_width(f.minortickwidth)
        cr:stroke()
      end

      do --majorticks
        for i = 0, f.majortickcount do
          local a = lerp(a1, a2, i/f.majortickcount)
          cr:new_sub_path()
          cr:arc(xc, yc, r, a, a)
          cr:arc(xc, yc, rmajortick, a, a)
        end

        cairo.extcel_set_source_color(cr,f.majortickcolor)
        cr:set_line_width(f.majortickwidth)
        cr:stroke()
      end

      do --majorticks text
        --cr:select_font_face('gill sans mt condensed', 'normal', 'normal')
        cr:select_font_face('wingdings', 'normal', 'normal')
        cr:set_font_size(64 * r/200)
        cairo.extcel_set_source_color(cr, f.majorticktextcolor)
        for i = 0, f.majortickcount-1 do
          local a = lerp(a1, a2, i/f.majortickcount)
          cr:save()

            local s = tostring(i)
            cr:new_sub_path()
            cr:arc(xc, yc, rmajortick*.85, a, a)
            show_text_center(cr, s, cr:text_extents(s))
          cr:restore()
        end
      end

      do
        local altitude = math.floor(t.altitude + .5)
        local rpivot = r * f.pivotradius
        local rneedle100 = r * f.needle100radius
        local rneedle1k = r * f.needle1kradius
       local rneedle10k = r * f.needle10kradius

        do --needle10k
          local rneedle = rneedle10k
          local needle = lerp(a1, a2, (altitude % 100000) / 100000)

          --neck
          cr:new_sub_path()
          cr:arc(xc, yc, rneedle, needle, needle)
          cr:arc(xc, yc, rpivot, needle, needle)

          --head
          cr:new_sub_path()
          cr:arc(xc, yc, rneedle, needle - .75 * math.pi*2/f.minortickcount, needle + .75 * math.pi*2/f.minortickcount)
          cr:arc(xc, yc, rmajortick, needle, needle)
          cr:close_path()

          cairo.extcel_set_source_color(cr,f.needle10kcolor)
          cr:set_line_width(1 )
          cr:stroke_preserve()
          cr:fill()

           --foot
          cr:new_sub_path()
          cr:arc(xc, yc, .75 * rneedle1k, needle, needle)
          cr:arc(xc, yc, rpivot, needle, needle)
          cr:set_line_width(5)
          cr:save()
            cr:set_line_cap('round')
           ;  cr:stroke()
          cr:restore()
        end

        

        do --needle1k tie shape
         local rneedle = rneedle1k
          local needle = lerp(a1, a2, (altitude % 10000) / 10000)
          cr:new_sub_path()
          cr:arc(xc, yc, rpivot, needle - .75 * math.pi*2/f.minortickcount, needle - .75 * math.pi*2/f.minortickcount)
          cr:arc(xc, yc, .75*rneedle, needle - .9 * math.pi*2/f.minortickcount, needle - .9 * math.pi*2/f.minortickcount)
          cr:arc(xc, yc, rneedle, needle, needle)
          cr:arc(xc, yc, .75*rneedle, needle + .9 * math.pi*2/f.minortickcount, needle + .9 * math.pi*2/f.minortickcount)
          cr:arc(xc, yc, rpivot, needle + .75 * math.pi*2/f.minortickcount, needle + .75 * math.pi*2/f.minortickcount)
          cr:close_path()
          
          cairo.extcel_set_source_color(cr,f.needle1kcolor)
          cr:set_line_width(2)
          cr:stroke_preserve()
          cr:fill()
        end

        do --needle100 sword shape
          local rneedle = rneedle100
          local needle = lerp(0, math.pi*2, (altitude % 1000) / 1000)
          cr:save()
            cr:translate(xc, yc)
            cr:rotate(needle)
            local hw = 5/2 --halfwidth
            cr:move_to(-hw, 0)
            cr:line_to(-hw, -rneedle*.9)
            cr:line_to(0, -rneedle)
            cr:line_to(hw, -rneedle*.9)
            cr:line_to(hw, 0)
            cr:close_path()

            cairo.extcel_set_source_color(cr,f.needle100color)
            cr:set_line_width(2)
            cr:stroke_preserve()
             cr:fill()
          cr:restore()

        end

        do --pivot
          cr:arc(xc, yc, rpivot*1.5, 0, 2*math.pi)
          cairo.extcel_set_source_color(cr,f.pivotcolor)
          cr:fill()
        end
      end
    end 
    cr:restore()
  end
end

