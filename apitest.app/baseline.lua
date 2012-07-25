local cel = require 'cel'
return function(root)

  local faces = {
    cel.getface('label'):new { font = cel.loadfont('arial', 10+6) },
    cel.getface('label'):new { font = cel.loadfont('helvetica', 12+6) },
    cel.getface('label'):new { font = cel.loadfont('fiolex girls', 14+6) },
    cel.getface('label'):new { font = cel.loadfont('algerian', 16+6) },
    cel.getface('label'):new { font = cel.loadfont('arial', 18+6) },
    cel.getface('label'):new { font = cel.loadfont('bodoni mt', 20+6) },
    cel.getface('label'):new { font = cel.loadfont('dejavu sans', 22+6) },
    cel.getface('label'):new { font = cel.loadfont('arial', 24+6) },
  }

  local words = {}

  for i, face in ipairs(faces) do
    words[i] = cel.label.new('Hello', face)
  end

  for i=#words, 1, -1 do
    --words[#words+1] = cel.label.new('Goodbye', words[i].face)
  end

  words[#words+1] = cel.window.new(100, 200)
  words[#words+1] = cel.textbutton.new[[[
                                      Do
                                      re 
                                      mi 
                                      fa 
                                      so 
                                      latido]]


  local row = cel.row.new(0, cel.getface('row'):new { layout={slotface = cel.colorface(cel.color.rgb(1, 1, 1))} })

  local baseline = 0
  for i, word in ipairs(words) do
    baseline = math.max(word.getbaseline and word:getbaseline() or word.h, baseline)
  end

  for i, word in ipairs(words) do
    local lbaseline = word.getbaseline and word:getbaseline() or word.h
    word:link(row, function(hw, hh, x, y, w, h, xval, yval)
      return x, baseline - lbaseline+90, w, h
    end)
  end

  row:link(root, 'center')
end

