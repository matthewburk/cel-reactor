local cel = require 'cel'

local scroll = cel.getface('scroll')
scroll.textcolor = false
scroll.color = false
scroll.bordercolor = false
scroll.borderwidth = false

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
scrollbar.color = cel.color.rgb(.4, .4, .4)

--track
local track = cel.getface('scroll.bar.track')
track.select = false
track.draw = scroll.draw

--thumb
local thumb = cel.getface('scroll.bar.thumb')
thumb.color = cel.color.rgb(.2, .2, .2)
thumb.bordercolor = cel.color.rgb(0, 1, 1)
thumb.accentcolor = cel.color.rgb(0, 1, 1)
thumb.select = false

function thumb.cairodraw(_ENV, cr, f, t, size)
  local size = size or t.host.host.size

  if f.color then
    cairo.set_source_color(cr, _ENV.color)
    cairo.rectangle(cr, 0, 0, t.w, t.h)
    cairo.fill(cr)
  end

  if f.borderwidth and f.bordercolor then
    cairo.set_line_width(cr, f.borderwidth)
    cairo.set_source_color(cr, _ENV.bordercolor)
    cairo.rectangle(cr, 0, 0, t.w, t.h)
    cairo.stroke(cr)
  end

  if f.accentcolor then
    cairo.set_source_color(cr, f.accentcolor)
    cairo.save(cr)
    cairo.translate(cr, t.w/2, t.h/2)
    cairo.scale(cr, size, size)
    cairo.arc(cr, 0, 0, .1, 0, 2 * math.pi);
    cairo.fill(cr)
    cairo.restore(cr)
  end

  return _ENV.drawlinks(cr, t)
end

--incbutton
local incbutton = cel.getface 'scroll.bar.inc'
incbutton.color = cel.color.rgb(.2, .2, .2)
incbutton.bordercolor = cel.color.rgb(0, 1, 1)
incbutton.accentcolor = cel.color.rgb(0, 1, 1)
incbutton.cairodraw = function(_ENV, cr, f, t) return thumb.cairodraw(_ENV, cr, f, t, t.host.size) end

do
  local face = incbutton
  face['%pressed'] = face:new {
    color = cel.color.rgb(.4, .4, .4),
    bordercolor = cel.color.rgb(0, 1, 1),
  }

  face['%mousefocusin'] = face:new {
    color = cel.color.rgb(.4, .4, .4),
    bordercolor = cel.color.rgb(0, 1, 1),
  }
  
  do
    local face = face['%mousefocusin']

    face['%pressed'] = face:new {
      textcolor = cel.color.rgb(.2, .2, .2),
      color = cel.color.rgb(0, .8, .8),
      bordercolor = cel.color.rgb(0, 1, 1),
      borderwidth = 2,
    }
  end
end

--decbutton
local decbutton = cel.getface 'scroll.bar.dec'
decbutton.color = cel.color.rgb(.2, .2, .2)
decbutton.bordercolor = cel.color.rgb(0, 1, 1)
decbutton.accentcolor = cel.color.rgb(0, 1, 1)
decbutton.cairodraw = function(_ENV, cr, f, t) return thumb.cairodraw(_ENV, cr, f, t, t.host.size) end


do
  local face = decbutton
  face['%pressed'] = face:new {
    color = cel.color.rgb(.4, .4, .4),
    bordercolor = cel.color.rgb(0, 1, 1),
  }

  face['%mousefocusin'] = face:new {
    color = cel.color.rgb(.4, .4, .4),
    bordercolor = cel.color.rgb(0, 1, 1),
  }
  
  do
    local face = face['%mousefocusin']

    face['%pressed'] = face:new {
      textcolor = cel.color.rgb(.2, .2, .2),
      color = cel.color.rgb(0, .8, .8),
      bordercolor = cel.color.rgb(0, 1, 1),
      borderwidth = 2,
    }
  end
end


