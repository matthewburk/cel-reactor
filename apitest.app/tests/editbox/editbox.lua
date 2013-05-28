local cel = require 'cel'

cel.getface('editbox.text'):new {
  font = cel.loadfont(string.format('%s/data/fonts/%s', app.path, 'filxgirl.ttf'), 24),
}:register('@filxgirl')

cel.getface('editbox.text'):new {
  font = cel.loadfont(string.format('%s/data/fonts/%s', app.path, 'crazy.ttf'), 24),
}:register('@crazy')

cel.getface('editbox.text'):new {
  font = cel.loadfont(string.format('%s/data/fonts/%s', app.path, 'linds.ttf'), 24),
}:register('@linds')

local filxgirl = cel.getface('editbox'):new {
  layout = {
    textface = cel.getface('editbox.text', '@filxgirl'),
  },
}

local crazy = cel.getface('editbox'):new {
  layout = {
    textface = cel.getface('editbox.text', '@crazy'),
  },
}

local linds = cel.getface('editbox'):new {
  layout = {
    textface = cel.getface('editbox.text', '@linds'),
  },
}

local focus

local function onfocus(c)
  focus = c
end

local function handletab(col, key, intercepted)
  if intercepted then return end

  if key == 'tab' then
    local target = col:next(focus)  
    if not target then
      target = col:get(1)
    end
    target:takefocus()
  end
end

return function(root)
  local col = cel.col { gap = 3,
    slotface = cel.colorface(app.colors.gray5),
    onkeypress = handletab,
    cel.text.new('hello'):settext(),
    cel.label.new('hello'):settext(''),
    cel.editbox.new('HELLO', 200):settext(),
    cel.editbox.new('HELLO', 200, filxgirl),
    cel.editbox.new('HELLO', 200, crazy),
    cel.editbox.new('HELLO', 200, linds),
  }:link(root, 5, 5)

  for i, link in col:ilinks() do
    link.onfocus = onfocus
  end
end

