local gtk = require 'gtk'

local deck = require 'deck'

local board = gtk.cel.new()

local cards = deck.cards

--[[
gtk.col { link='center',
  gtk.row { cards[1], cards[2], cards[3], cards[4], },
  gtk.row { cards[5], cards[6], cards[7], cards[8], },
  gtk.row { cards[9], cards[10], cards[11], cards[12], },
  gtk.row { cards[13], cards[14], cards[15], cards[16], },
}:link(board, 'fill')
--]]

return board
