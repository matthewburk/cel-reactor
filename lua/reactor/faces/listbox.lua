local cel = require 'cel'

local face = cel.getface('listbox')

local size = 20

face.textcolor = app.colors.black

face.layout = {
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

  list = {
    face = nil,  
    slotface = cel.colorface(app.colors.white):new(),
  },
}

do
  local face = face.layout.list.slotface

  local mousefocusin = cel.colorface(app.colors.themecomplementlight)

  function face:select(t)
    if t.mousefocusin then
      dprint('SELECTING focus face', t.id)
      return mousefocusin
    end
    return self
  end
end

do
  local face = cel.colorface(app.colors.white):new {
    mousefocuscolorface = cel.colorface(app.colors.themecomplementlight)
  }:register('@listslot')

  function face:select(t)
    if t.mousefocusin then
      return self.mousefocuscolorface
    end
    return self
  end
end
