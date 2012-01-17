local cel = require 'cel'

local function lerp(a, b, p)
  return a + p * (b -a)
end

return function(_ENV)
  setfenv(1, _ENV)

  local airspeed = cel.getface('airspeed') 

  airspeed.radius = false
  airspeed.fillcolor = false
  airspeed.linewidth = 1
  airspeed.linecolor = cel.color.rgb(1, 0, 0)

  airspeed.backgroundcolor = cel.color.rgb(.1, .1, .1)
  airspeed.bgpattern = cairo.pattern.create_radial(0, 0, .5, 0, 0, 0)
  airspeed.bgpattern:add_color_stop(0, 0, 0, 0, 1)
  airspeed.bgpattern:add_color_stop(.2, .07, .07, .07, 1)

  airspeed.a1 = -math.pi/2 + math.pi/6 
  airspeed.a2 = -math.pi/2 + math.pi * 2 - (math.pi/6)
  airspeed.min = 35 --should be a multiple of mod1
  airspeed.max = 210 --should be a multiple of mod1

  airspeed.mod1 = 5 --smallest
  airspeed.mod2 = 10 --mid
  airspeed.mod3 = 20 --large

  airspeed.mod1length = .1 --* radius
  airspeed.mod1width = 1.5 
  airspeed.mod1color = cel.color.rgb(1, 1, 1)

  airspeed.mod2length = .15 --* radius
  airspeed.mod2width = 3 
  airspeed.mod2color = cel.color.rgb(1, 1, 1)

  airspeed.mod3length = .20 --* radius
  airspeed.mod3width = 3 
  airspeed.mod3color = cel.color.rgb(0, 1, 1)
  airspeed.mod3textcolor = cel.color.shade(.1, cel.color.rgb(1, 1, 1))

  airspeed.ticksradius = .5
  airspeed.pivotradius = .4
  airspeed.needleradius = .9 --* radius

  airspeed.pivotcolor = cel.color.rgb(0, 0, 0)
  airspeed.needlecolor = cel.color.shade(.1, cel.color.rgb(1, 1, 1))

  function airspeed.draw(f, t)
    if f.fillcolor then
      cairo.extcel_set_source_color(cr, f.fillcolor)
      cairo.ext_roundrect(cr, t.x, t.y, t.w, t.h, f.radius)
    end

    if f.linewidth and f.linecolor then
      cairo.set_line_width(cr, f.linewidth)
      cairo.extcel_set_source_color(cr, f.linecolor)
      cairo.ext_roundrect(cr, t.x, t.y, t.w, t.h, f.radius)
      cairo.stroke(cr)
    end

    drawlinks(t)

    cr:save() 
    do
      local xc = (t.w/2) + t.x
      local yc = (t.h/2) + t.y
      local r = math.min(t.w, t.h)/2
      local a1 = airspeed.a1
      local a2 = airspeed.a2

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

      local rpivot = r * f.pivotradius
      local rticks = r * f.ticksradius
      local rmod1 = rticks + r * f.mod1length
      local rmod2 = rticks + r * f.mod2length
      local rmod3 = rticks + r * f.mod3length
  
      cr:set_line_join('round')

      local mod1count = math.floor((f.max-f.min)/f.mod1)
      local mod2count = math.floor((f.max-f.min)/f.mod2)
      local mod3count = math.floor((f.max-f.min)/f.mod3)

      do --mod1s
        for i = 0, mod1count do
          local a = lerp(a1, a2, i/mod1count)
          cr:new_sub_path()
          cr:arc(xc, yc, rticks, a, a)
          cr:arc(xc, yc, rmod1, a, a)
        end

        cairo.extcel_set_source_color(cr,f.mod1color)
        cr:set_line_width(f.mod1width)
        cr:stroke()
      end

      do --mod2s
        local trim = (f.min % f.mod2)/f.mod1 --number or mod1 before first mod2
        local a1 = lerp(a1, a2, trim/mod1count) --adjust starting angle for mod2

        for i = 0, mod2count do
          local a = lerp(a1, a2, i/mod2count)
          cr:new_sub_path()
          cr:arc(xc, yc, rticks, a, a)
          cr:arc(xc, yc, rmod2, a, a)
        end

        cairo.extcel_set_source_color(cr,f.mod2color)
        cr:set_line_width(f.mod2width)
        cr:stroke()
      end

      do --mod3s text
        local firsttickvalue = f.mod3 * math.ceil(f.min/f.mod3)
        local lasttickvalue = f.mod3 * math.floor(f.max/f.mod3)
        local trim = (firsttickvalue - f.min)/f.mod1 --number of mod1 before first mod3
        local a1 = lerp(a1, a2, trim/mod1count) --adjust starting angle for mod3
        local a2 = lerp(a1, a2, lasttickvalue/f.max)

        cr:select_font_face('gill sans mt condensed', nil, 'normal')
        cr:set_font_size(48 * r/200)
        cairo.extcel_set_source_color(cr, f.mod3textcolor)

        local mod3countf = (f.max-f.min)/f.mod3

        for i = 0, mod3count do
          local a = lerp(a1, a2, i/(mod3count))

          local s = tostring(firsttickvalue + f.mod3 * i)
          local _, ybearing, sw, sh = cr:text_extents(s)
          local xoff = lerp(sw, 0, (math.cos(a)+1)/2)
          local yoff = lerp(sh, 0, (math.sin(a)+1)/2)

          cr:save()
            cr:new_sub_path()
            cr:arc(xc, yc, rmod3, a, a)
            cr:rel_move_to(-xoff, sh-yoff)
            cr:show_text(s)
          cr:restore()

          cr:new_sub_path()
          cr:arc(xc, yc, rticks, a, a)
          cr:arc(xc, yc, rmod3, a, a)

          cairo.extcel_set_source_color(cr,f.mod3color)
          cr:set_line_width(f.mod3width)
          cr:stroke()
        end
      end
      --[[

      do --mod2s text
        cr:select_font_face('gill sans mt condensed', nil, 'bold')
        cr:set_font_size(64 * r/200)
        cairo.extcel_set_source_color(cr, f.mod2textcolor)
        local _, ybearing, sw, sh = cr:text_extents('0123456789')
        sw = sw/10
        for i = 0, f.mod2count-1 do
          local a = lerp(a1, a2, i/f.mod2count)
          cr:save()

            local s = tostring(i)
            cr:new_sub_path()
            cr:arc(xc-sw/2, yc-ybearing/2, rmod2-.5*math.sqrt(sw*sw + sh*sh), a, a)
            cr:show_text(s)
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
          cr:arc(xc, yc, rneedle, needle - .75 * math.pi*2/f.mod1count, needle + .75 * math.pi*2/f.mod1count)
          cr:arc(xc, yc, rmod2, needle, needle)
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
          cr:arc(xc, yc, rpivot, needle - .75 * math.pi*2/f.mod1count, needle - .75 * math.pi*2/f.mod1count)
          cr:arc(xc, yc, .75*rneedle, needle - .9 * math.pi*2/f.mod1count, needle - .9 * math.pi*2/f.mod1count)
          cr:arc(xc, yc, rneedle, needle, needle)
          cr:arc(xc, yc, .75*rneedle, needle + .9 * math.pi*2/f.mod1count, needle + .9 * math.pi*2/f.mod1count)
          cr:arc(xc, yc, rpivot, needle + .75 * math.pi*2/f.mod1count, needle + .75 * math.pi*2/f.mod1count)
          cr:close_path()
          
          cairo.extcel_set_source_color(cr,f.needle1kcolor)
          cr:set_line_width(2)
          cr:stroke_preserve()
          cr:fill()
        end

        do --needle100 sword shape
          local rneedle = rneedle100
          print('100', (altitude % 1000) / 1000, lerp(0, math.pi*2, (altitude % 1000) / 1000))
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
      --]]
    end 
    cr:restore()
  end
end

