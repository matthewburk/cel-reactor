local gtk = require 'gtk'

return gtk.row {
  gtk.textbutton.new 'DECK',
  gtk.textbutton.new 'B',
  gtk.textbutton.new 'C',
  gtk.textbutton.new 'D',
}
