local cel = require 'cel'

return function(_ENV)
  setfenv(1, _ENV)

  local analog = cel.getface('analog') 

  analog.font = cel.loadfont('monospace:bold', 8)
  analog.okcolor = cel.color.encodef(0, .7, .2)
  analog.cautioncolor = cel.color.encodef(1, 1, 0)
  analog.warncolor = cel.color.encodef(1, 0, 0)
  analog.needlecolor = cel.color.encodef(1, .2, .2, .7) 

  analog.rlinewidth = .2
  analog.tickmodulate = .1
  analog.tickcolor = cel.color.encodef(0, 0, 0)
  analog.ticklabelcolor = cel.color.encodef(1, 1, 1)
  analog.tickwidth = 1

  analog.tick = {
    labelfont = cel.loadfont('gill sans mt condensed', 12),
    labelformat = function(num)
      return string.format('%02.1f', num)
    end,
    labelw = true,
    labelh = true,
  }


  analog.linewidth=3
  analog.radius=5
  analog.angle1 = (-180 - 90 + (45/2))  * (math.pi/180.0) 
  analog.angle2 = (90 -(45/2)) * (math.pi/180.0)

  do
    local _new = analog.new
    function analog:new(...)
      local new = _new(self, ...)

      return new
    end
  end


  do
    local t = analog.tick
    local advance, fonth, xmin, xmax, ymin, ymax = t.labelfont:measure(t.labelformat(.5))
    t.labelw = xmax-xmin
    t.labelh = ymax-ymin
  end

  local function lerp(a, b, p)
    return a + p * (b -a)
  end
  ---[[
  --
  local function drawneedle(f, t)
    local cr = f.cr
    local crx = f.crx

    local linewidth = math.min(t.w/3, t.h/3) * f.rlinewidth
    local xc = (t.w/2) + t.x
    local yc = (t.h/2) + t.y
    local radius = math.min(t.w/3, t.h/3) - linewidth
    local pvalue = (t.value - t.minrange)/(t.maxrange-t.minrange)

    crx:setcolor(f.needlecolor)
    cr:set_line_width(3);

    local needleat = lerp(f.angle1, f.angle2, pvalue)

    cr:new_sub_path()
    cr:arc(xc, yc, radius, needleat, needleat);
    cr:line_to(xc, yc);
    cr:stroke();
  end

  function analog.draw(f, t)
    crx:clip(t)

    if f.fillcolor then
      crx:fillrect(f.fillcolor, t.x, t.y, t.w, t.h, f.radius)
    end

    drawlinks(t)

    crx:clip(t)

    if f.pattern then
      cr:set_source(f.pattern)
      cr:paint()
      drawneedle(f, t)
    else
      cr:push_group()
      cr:save() do
        local linewidth = math.min(t.w/3, t.h/3) * f.rlinewidth
        local xc = (t.w/2) + t.x
        local yc = (t.h/2) + t.y
        local radius = math.min(t.w/3, t.h/3) - linewidth
        local angle1 = f.angle1 
        local angle2 = f.angle2

        crx:setcolor(f.okcolor)
        cr:set_line_width(linewidth);
        cr:arc(xc, yc, radius, angle1, angle2);
        cr:stroke();

        if f.cautioncolor then
          local _a1, _a2 = angle1, angle2
          local angle1 = lerp(_a1, _a2, .7)
          local angle2 = lerp(_a1, _a2, .9)
          crx:setcolor(f.cautioncolor)
          cr:arc(xc, yc, radius, angle1, angle2);
          cr:stroke();
        end

        if f.warncolor then
          local _a1, _a2 = angle1, angle2
          local angle1 = lerp(_a1, _a2, .9)
          local angle2 = lerp(_a1, _a2, 1)
          crx:setcolor(f.warncolor)
          cr:arc(xc, yc, radius, angle1, angle2);
          cr:stroke();
        end

        local pvalue = (t.value - t.minrange)/(t.maxrange-t.minrange)
       
        --majorticks
        cr:set_line_width(f.tickwidth)

        cr:set_font_face(f.tick.labelfont.nativefont)
        cr:set_font_size(f.tick.labelfont.size)

        local font = f.font
        local range = t.maxrange-t.minrange
        local tickr1 = radius + (linewidth*.48)
        local tickr2 = radius - (linewidth*.48)

        local start = t.minrange
        local tickmodulate = t.tickmodulate or f.tickmodulate
        if start ~= 0 then
          start = t.minrange - (t.minrange%tickmodulate) + tickmodulate
        end

        for i=start, t.maxrange, tickmodulate do
          local mark = lerp(angle1, angle2, (i-t.minrange)/range)
          cr:new_sub_path()
          cr:arc(xc, yc, tickr1, mark, mark);
          cr:arc(xc, yc, tickr2, mark, mark);
          --cr:line_to(xc, yc);
          crx:setcolor(f.tickcolor)
          cr:stroke();

          local s = f.tick.labelformat(i)
          local sw, sh = f.tick.labelw, f.tick.labelh
          local xoff = lerp(sw, 0, (math.cos(mark)+1)/2)
          local yoff = lerp(sh, 0, (math.sin(mark)+1)/2)

          cr:new_sub_path()
          cr:arc(xc, yc, radius + linewidth, mark, mark)
          cr:rel_move_to(-xoff, sh-yoff)
          
          crx:setcolor(f.ticklabelcolor)
          cr:show_text(s)
        end

        --pivot
        crx:setcolor(f.okcolor)
        cr:arc(xc, yc, 6.0, 0, 2*math.pi);
        cr:fill();

        if f.linewidth and f.linecolor then
          cr:set_line_width(f.linewidth)
          crx:strokerect(f.linecolor, t.x, t.y, t.w, t.h, f.radius)
        end
      end cr:restore()
      f.pattern = cr:pop_group()
      cr:set_source(f.pattern)
      cr:paint()
      drawneedle(f, t)
    end
  end
  --]]


  do --analog @memgauge
    local memgauge = analog:new {
      tickmodulate = 2048,
      tick = setmetatable({
        labelformat = function(num)
          return string.format('%02dM', num/1024)
        end,
        labelw = true,
        labelh = true,
        color = cel.color.encodef(0, 0, 0),
      }, {__index=analog.tick})
    }:register('@memgauge')

    local t = memgauge.tick
    local advance, fonth, xmin, xmax, ymin, ymax = t.labelfont:measure(t.labelformat(11))
    t.labelw = xmax-xmin
    t.labelh = ymax-ymin
  end
end


local altimeter = ctk.getface('altimeter') 

altimeter.radius = false
altimeter.fillcolor = false
altimeter.linewidth = 1
altimeter.linecolor = ctk.color.encodef(1, 0, 0)

altimeter.backgroundcolor = ctk.color.encodef(.1, .1, .1)
altimeter.bgpattern = cairo.pattern.create_radial(0, 0, .5, 0, 0, 0)
altimeter.bgpattern:add_color_stop(0, 0, 0, 0, .5)
altimeter.bgpattern:add_color_stop(.2, .07, .07, .07, 1)

altimeter.minorticklength = .1 --* radius
al timeter.minortickwidth = 1.5 
altimeter.minortickcount = 50
altimeter.minortickcolor = ctk.color.encodef(1, 1, 1)

altimeter.majorticklength = .15 --* radius
altimeter.majortickwidth = 3 
altimeter.majortickcount = 10 
altimeter.majortickcolor = ctk.color.encodef(1, 1, 1)
altimeter.majorticktextcolor = ctk.color.shade(.1, ctk.color.encodef(1, 1, 1))

altimeter.pivotradius = .05 --* radius
altimeter.needle100radius = .9 --* radius
altimeter.needle1kradius = .6 --* radius
altimeter.needle10kradius = 1 --* radius

altimeter.pivotcolor = ctk.color.encodef(0, 0, 0)
altimeter.needle100color = ctk.color.encodef(1, 1, 1)
altimeter.needle1kcolor = ctk.color.shade(.1, ctk.color.encodef(1, 1, 1))
altimeter.needle10kcolor = ctk.color.shade(.2, ctk.color.encodef(1, 1, 1))

function altimeter.draw(f, t)
  local cr = f.cr
  local crx = f.crx

  crx:clip(t)

  if f.fillcolor then
    crx:fillrect(f.fillcolor, t.x, t.y, t.w, t.h, f.radius)
  end

  if f.linecolor and f.li newidth then
    cr:set_line_width(f.linewidth)
    crx:strokerect(f.linecolor, t.x, t.y, t.w, t.h, f.radius)
  end

  drawlinks(t)

  crx:clip(t)

  cr:save() 
  do
    local xc = (t.w/2) + t.x
    local yc = (t.h/2) + t.y
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
& nbsp;
    cr:set_line_join('round')

    do --minorticks
      for i = 0, f.minortickcount do
        local a = lerp(a1, a2, i/f.minortickcount)
        cr:new_sub_path()
        cr:arc(xc, yc, r, a, a)
        cr:arc(xc, yc, rminortick, a, a)
      end

      crx:setcolor(f.minortickcolor)
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

      crx:setcolor(f.majortickcolor)
      cr:set_line_wid th(f.majortickwidth)
      cr:stroke()
    end

    do --majorticks text
      cr:select_font_face('gill sans mt condensed', nil, 'bold')
      cr:set_font_size(64 * r/200)
      crx:setcolor(f.majorticktextcolor)
      local _, ybearing, sw, sh = cr:text_extents('0123456789')
      sw = sw/10
      for i = 0, f.majortickcount-1 do
        local a = lerp(a1, a2, i/f.majortickcount)
        cr:save()

          local s = tostring(i)
          cr:new_sub_path()
          cr:arc(xc-sw/2, yc-ybearing/2, rmajortick-.5*math.sqrt(sw*sw + sh*sh), a, a)
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
     & nbsp;  cr:arc(xc, yc, rneedle, needle, needle)
        cr:arc(xc, yc, rpivot, needle, needle)

        --head
        cr:new_sub_path()
        cr:arc(xc, yc, rneedle, needle - .75 * math.pi*2/f.minortickcount, needle + .75 * math.pi*2/f.minortickcount)
        cr:arc(xc, yc, rmajortick, needle, needle)
        cr:close_path()

        crx:setcolor(f.needle10kcolor)
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
        cr:arc(xc, yc, .75*rneed le, needle - .9 * math.pi*2/f.minortickcount, needle - .9 * math.pi*2/f.minortickcount)
        cr:arc(xc, yc, rneedle, needle, needle)
        cr:arc(xc, yc, .75*rneedle, needle + .9 * math.pi*2/f.minortickcount, needle + .9 * math.pi*2/f.minortickcount)
        cr:arc(xc, yc, rpivot, needle + .75 * math.pi*2/f.minortickcount, needle + .75 * math.pi*2/f.minortickcount)
        cr:close_path()
        
        crx:setcolor(f.needle1kcolor)
        cr:set_line_width(2)
        cr:stroke_preserve()
        cr:fill()
      end

      do --needle100 sword shape
        local rneedle = rneedle100
        local needle = lerp(a1, a2, (altitude % 1000) / 1000)
        cr:save()
          cr:translate(xc, yc)
          cr:rotate(needle)
          local hw = 5/2 --halfwidth
    &nbs p;     cr:move_to(-hw, 0)
          cr:line_to(-hw, -rneedle*.9)
          cr:line_to(0, -rneedle)
          cr:line_to(hw, -rneedle*.9)
          cr:line_to(hw, 0)
          cr:close_path()

          crx:setcolor(f.needle100color)
          cr:set_line_width(2)
          cr:stroke_preserve()
           cr:fill()
        cr:restore()

      end

      do --pivot
        cr:arc(xc, yc, rpivot*1.5, 0, 2*math.pi)
        crx:setcolor(f.pivotcolor)
        cr:fill()
      end
    end
  end 
  cr:restore()
end

