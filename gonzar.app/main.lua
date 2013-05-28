require 'stdinit'

local gtk=require 'gtk'

gtk.root:setlimits(640, 640, 960, 960)

local canvas=gtk.mutexpanel.new(640, 960)
  :link(gtk.root, 'fill')

canvas.deck=require 'deck'
  :link(canvas, 'fill')

canvas.board=require 'board'
  :link(canvas, 'fill')


function app.update()
  return 10
end
