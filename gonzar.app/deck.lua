local gtk = require 'gtk'

local cardsize=160

gtk.getface('text'):new {
  font=gtk.loadfont('fancy', 48)
}:register('@title')

gtk.getface('text'):new {
  font=gtk.loadfont('fancy', 38)
}:register('@subtitle')

local panel = gtk.cel.new()
local cards = {size=160, margin=9}

local function newcustomface(source)
  local face =  gtk.newpattern(source)

  local w, h = face.w, face.h
  local size = cardsize - cards.margin*2 - 2

  if w > h then
    face:resize(size, size*h/w)
  else
    face:resize(size*w/h, size)
  end

  return gtk.cel.new(face.w, face.h, face)
end

do --@card
  local face = gtk.getface('cel'):new {
    borderwidth=4,
    bordercolor=app.colors.black,
    color=app.colors.oceanblue,
  }:register('@card')

  local touching = face:new {
    bordercolor=app.colors.white,
  }

  function face.select(f, t)
    if t.mousefocusin  then
      return touching
    end
    return f
  end
end

do --@cardlabel 
  local face = gtk.getface('label'):new {
    font=gtk.loadfont('arial:bold', 40),
    textcolor=app.colors.white,
  }:register('@cardlabel')
end


local function newcard(cardface, background)
  local card = gtk.cel.new(cardsize, cardsize, '@card')

  gtk.cel.new(cardsize, cardsize, background):link(card, 'fill.margin', cards.margin)

  if cardface then
    cardface:link(card, 'center')
  end

  return card
end

for i = 1, 10 do
  local card1 = newcard(gtk.label.new(tostring(i), '@cardlabel'))
  local card2 = newcard(gtk.label.new(tostring(i), '@cardlabel'))

  card1.onmousein = card1.raise
  card2.onmousein = card2.raise

  card1.twin = card2
  card2.twin = card1

  cards[#cards+1] = card1
  cards[#cards+1] = card2
end

panel.cards = cards

local title = gtk.text.new('Memories', '@title')

local function xfan(hw, hh, x, y, w, h, p, yval)
  yval = yval or 0
  local left = 0
  local right = hw-w

  return lerp(left, right, p), yval, w, h
end

local deck = gtk.col { link='width', gap=3,
  gtk.cel { h=cardsize+10, 
    { link={xfan, 0/4, math.random(5,10)}, cards[1] },
    { link={xfan, 1/4, math.random(5)}, cards[3] },
    { link={xfan, 2/4, math.random(5,10)}, cards[5] },
    { link={xfan, 3/4, math.random(5)}, cards[7] },
    { link={xfan, 4/4, math.random(5,10)}, cards[9] },
  },
  gtk.cel { h=cardsize+10,
    { link={xfan, 0/4, math.random(10) }, cards[11] },
    { link={xfan, 1/4, math.random(10)}, cards[13] },
    { link={xfan, 2/4, math.random(10)}, cards[15] },
    { link={xfan, 3/4, math.random(10)}, cards[17] },
    { link={xfan, 4/4, math.random(10)}, cards[19] },
  },
}:resize(cardsize*4)

local subtitle = gtk.text.new('Desgin a card', '@subtitle')

local backgrounds = gtk.scroll {
  stepsize = cardsize,

  subject = gtk.slot {
    gtk.col {
      gtk.cel.new(cardsize, cardsize/2, gtk.colorface(app.colors.blue)),
      function(col)
        for i, name in ipairs {
          'data/square.png',
          'data/perfmetal.png',
          'data/block.png',
          'data/diamond.png',
          'data/horizontal.png',
          'data/lined.png',
          'data/lines.png',
          'data/pattern001-dark.png',
          'data/pattern001-light.png',
          'data/pattern002-dark.png',
          'data/pattern002-light.png',
          'data/pattern003-dark.png',
          'data/pattern003-light.png',
          'data/pattern004-dark.png',
          'data/pattern004-light.png',
          'data/pattern005-dark.png',
          'data/pattern005-light.png',
          'data/pattern006-dark.png',
          'data/pattern006-light.png',
        } do
          newcard(nil, gtk.newpattern(name)):link(col)
        end
      end,
      gtk.cel.new(cardsize, cardsize/2, gtk.colorface(app.colors.blue)),
    },
    function(slot)
      local grip = gtk.grip.new()
        :link(slot, 'fill')
        :grip(slot)
        :sethidden(true)

      function grip:ongrab()
        slot:endflow()
      end

      function grip:onrelease()
        slot:flow(gtk.flows.linear(100), 0, math.floor(slot.y/cardsize + .5)*cardsize)
      end
    end,
  }
}:resize(cardsize, cardsize*2)

local preview = gtk.slot {
  newcard(newcustomface('gonzar.app/images/eagle.png'))  
}

local foregrounds = gtk.scroll {
  stepsize = cardsize,

  subject = gtk.slot {
    gtk.col {
      gtk.cel.new(cardsize, cardsize/2, gtk.colorface(app.colors.blue)),
      function(col)
        for i, name in ipairs {
          'gonzar.app/images/crowned_crane.png',
          'gonzar.app/images/animals.png',
          'gonzar.app/images/european-bear.png',
          'gonzar.app/images/catdog.png',
          'gonzar.app/images/ladybug.png',
          'gonzar.app/images/bird.png',
          'gonzar.app/images/fish.png',
          'gonzar.app/images/eagle.png',
          'gonzar.app/images/goose.png',
          'gonzar.app/images/sparrow.png',
          'gonzar.app/images/swordfish.png',
          'gonzar.app/images/goldfish.png',
          'gonzar.app/images/jellyfish.png',
          'gonzar.app/images/grasshopper.png',
          'gonzar.app/images/mantis.png',
          'gonzar.app/images/butterfly.png',
          'gonzar.app/images/frog.png',
          'gonzar.app/images/snake.png',
        } do
          newcard(newcustomface(name)):link(col)
        end
      end,
      gtk.cel.new(cardsize, cardsize/2, gtk.colorface(app.colors.blue)),
    },
    function(slot)
      gtk.grip.new()
        :link(slot, 'fill')
        :grip(slot)
        :sethidden(true)
    end,
  }
}:resize(cardsize, cardsize*2)

local menu = gtk.row {
  'A', 'B', 'NEXT'
}

panel:addlinks { link='center',
  gtk.col { link='center',
    title, 
    deck,
    subtitle,
    gtk.row { link='center', gap=cardsize/2,
      backgrounds, preview, foregrounds,
    },
  },
  {link='bottom', menu},
}

return panel
