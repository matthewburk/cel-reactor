local cel = require 'cel'

return function(root)

  local subject = cel.new(1000, 1000, '#aabbcc')

  local inner = cel.scroll {
    cel.col {
      'A', 'A', 'A', 'A', 'A', 'A', 'A', 'A', 'A', 'A', 'A', 'A', 'A', 'A', 'A', 'A', 'A', 'A', 'A', 'A', 'A', 'A', 'A',
      'A', 'A', 'A', 'A', 'A', 'A', 'A', 'A', 'A', 'A', 'A', 'A', 'A', 'A', 'A', 'A', 'A', 'A', 'A', 'A', 'A', 'A', 'A',
    },
  }:resize(300, 300)
  :link(subject, 'center')

  cel.scroll {
    subject
  }:link(root, 'fill')
  
  
end

