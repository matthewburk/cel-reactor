local cel = require 'cel'

return function(root)
  local w, h = 50, 10
  local n = 3

  do
    local col = cel.col.new(0, '#ff00ff'):link(root, 'center')

    col.__debug = true
    --TODO this breaks because didn’t fails to render in cairo, maybe not valid utf8, and requires verification
    --that utf8 text is valid
    --cel.text.new([[A very long time ago, I was curious how to detect the strength of the bass and treble in music, in order to synchronize some graphical effects. I had no idea how to do such a thing, so I tried to figure it out,but I didn’t get very far. Eventually I learned that I needed something called a Fourier transform, so I took a trip to the library and looked it up (which is what we had to do back in those days).]])
    cel.text.new('A very long time ago, I was curious how to detect the strength of the bass and treble in music, in order to synchronize some graphical effects')
      :wrap('word')
      :link(col, 'width')

    cel.label.new(string.rep('_', 30)):link(col)

    cel.window.new(50, 50):link(col)
  end

end

