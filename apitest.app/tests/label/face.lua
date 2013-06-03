local cel = require 'cel'

local function loadfont(name, size)
  return cel.loadfont(string.format('%s/data/fonts/%s', app.path, name), size)
end

cel.getface('label'):new {
  font = loadfont('filxgirl.ttf', 24),
}:register('@filxgirl')

cel.getface('label'):new {
  font = loadfont('crazy.ttf', 24),
}:register('@crazy')

cel.getface('label'):new {
  font = loadfont('linds.ttf', 24),
}:register('@linds')

local label = cel.label.new('Changing face')
local input = cel.editbox.new('', 200)

function input:onkeydown(key)
  if key == 'enter' then
    local size = self:gettext()

    local face = cel.getface(label.metacel, size)

    dprint(label.metacel)
    if not face then
      face = cel.getface(label.metacel):new {
        font = cel.loadfont('arial', tonumber(size))
      }:register(size)
    end
    dprint(face, size)
    label:setface(face)
  end
end

return function(root)
  local col = cel.col { gap = 3,
    label, 
    input,
  }:link(root, 5, 5)
end

