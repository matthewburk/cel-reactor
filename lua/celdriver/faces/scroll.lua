local cel = require 'cel'

return function(_ENV)
  setfenv(1, _ENV)

  local scroll = cel.getface('scroll')
  scroll.textcolor = false
  scroll.fillcolor = false
  scroll.linecolor = false
  scroll.linewidth = false

  scroll.flow = {
    scroll = cel.flows.linear(100);
    showybar = cel.flows.linear(500);
    hideybar = cel.flows.linear(100);
    showxbar = cel.flows.linear(500);
    hidexbar = cel.flows.linear(100);
  }

  local size = 20
  scroll.layout = {
    stepsize = 20,
    ybar = {
      align = 'right',
      size = size, 
      track = {
        size = size,
        link = {'fill.margin', 0, size},
        thumb = {
          minsize = 20,
          size = size,
        };
      },
      decbutton = {
        size = size,
        link = 'width.top',
      },
      incbutton = {
        size = size,
        link = {'width.bottom'},
      },
    },
    xbar = {
      align = 'bottom',
      size = size,
      track = {
        size = size,
        link = {'fill.margin', size, 0},
        thumb = {
          minsize = 10,
          size = size,
        },
      },
      decbutton = {
        size = size,
        link = {'left.height'},
      },
      incbutton = {
        size = size,
        link = {'right.height'},
      },
    },
  }

  --scroll.draw = function(f, t) return drawlinks(t) end

  --scrollbar
  local scrollbar = cel.getface('scroll.bar')
  scrollbar.fillcolor = cel.color.encodef(.4, .4, .4)

  --track
  local track = cel.getface('scroll.bar.track')
  track.select = false
  track.draw = scroll.draw

  --thumb
  local thumb = cel.getface('scroll.bar.thumb')
  thumb.fillcolor = cel.color.encodef(.2, .2, .2)
  thumb.linecolor = cel.color.encodef(0, 1, 1)
  thumb.accentcolor = cel.color.encodef(0, 1, 1)
  thumb.select = false

  function thumb.draw(f, t, size)
    local size = size or t.host.host.size

    if f.fillcolor then
      cairo.extcel_set_source_color(cr, f.fillcolor)
      cairo.ext_roundrect(cr, 0, 0, t.w, t.h, f.radius)
      cairo.fill(cr)
    end

    if f.linewidth and f.linecolor then
      cairo.set_line_width(cr, f.linewidth)
      cairo.extcel_set_source_color(cr, f.linecolor)
      cairo.ext_roundrect(cr, 0, 0, t.w, t.h, f.radius)
      cairo.stroke(cr)
    end

    if f.accentcolor then
      cairo.extcel_set_source_color(cr, f.accentcolor)
      cairo.save(cr)
      cairo.translate(cr, t.w/2, t.h/2)
      cairo.scale(cr, size, size)
      cairo.arc(cr, 0, 0, .1, 0, 2 * math.pi);
      cairo.fill(cr)
      cairo.restore(cr)
    end

    return drawlinks(t)
  end

  --incbutton
  local incbutton = cel.getface 'scroll.bar.inc'
  incbutton.fillcolor = cel.color.encodef(.2, .2, .2)
  incbutton.linecolor = cel.color.encodef(0, 1, 1)
  incbutton.accentcolor = cel.color.encodef(0, 1, 1)
  incbutton.draw = function(f, t) return thumb.draw(f, t, t.host.size) end

  do
    local face = incbutton
    face['%pressed'] = face:new {
      fillcolor = cel.color.encodef(.4, .4, .4),
      linecolor = cel.color.encodef(0, 1, 1),
    }

    face['%mousefocusin'] = face:new {
      fillcolor = cel.color.encodef(.4, .4, .4),
      linecolor = cel.color.encodef(0, 1, 1),
    }
    
    do
      local face = face['%mousefocusin']

      face['%pressed'] = face:new {
        textcolor = cel.color.encodef(.2, .2, .2),
        fillcolor = cel.color.encodef(0, .8, .8),
        linecolor = cel.color.encodef(0, 1, 1),
        linewidth = 2,
      }
    end
  end

  --decbutton
  local decbutton = cel.getface 'scroll.bar.dec'
  decbutton.fillcolor = cel.color.encodef(.2, .2, .2)
  decbutton.linecolor = cel.color.encodef(0, 1, 1)
  decbutton.accentcolor = cel.color.encodef(0, 1, 1)
  decbutton.draw = function(f, t) return thumb.draw(f, t, t.host.size) end

  do
    local face = decbutton
    face['%pressed'] = face:new {
      fillcolor = cel.color.encodef(.4, .4, .4),
      linecolor = cel.color.encodef(0, 1, 1),
    }

    face['%mousefocusin'] = face:new {
      fillcolor = cel.color.encodef(.4, .4, .4),
      linecolor = cel.color.encodef(0, 1, 1),
    }
    
    do
      local face = face['%mousefocusin']

      face['%pressed'] = face:new {
        textcolor = cel.color.encodef(.2, .2, .2),
        fillcolor = cel.color.encodef(0, .8, .8),
        linecolor = cel.color.encodef(0, 1, 1),
        linewidth = 2,
      }
    end
  end
end


