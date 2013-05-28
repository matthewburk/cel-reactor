local cel = require 'cel'

--make root cel a fixed size, it will scale, by default it is size to app.window size
--app.window.root:setlimits(nil, nil, 1200, 1200)

cel.col { face = cel.colorface(app.colors.red),
  __debug = true,
  '1', '2', '3',
}:link(app.window.root, 'center')
