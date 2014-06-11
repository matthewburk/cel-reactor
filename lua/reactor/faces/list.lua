local cel = require 'cel'
local face = cel.getface('list')

local slotface = cel.getface('cel'):new()

do
  local mousefocus = cel.getface('cel', '#f04400')

  function slotface:select(t)
    if t.mousefocusin then
      return mousefocus
    else
      return self
    end
  end
end


face.layout = {
  slotface = '#aabbcc',
  currentslotface = cel.getface('cel', '#ff8822'),
  selectedslotface = '#338822',
}

--[[
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
--]]
