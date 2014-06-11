local cel = require 'cel'

app.window.root:setlimits(1280, 1280, 1024, 1024)

app.pencolor = cel.color.rgb8(255, 255, 255)

do --app.colors
  app.colors = {
    pink = cel.color.rgb8(255, 153, 255),
    white = cel.color.rgb8(255, 255, 255),
    black = cel.color.rgb8(0, 0, 0),
    red = cel.color.rgb8(255, 0, 0),

    blue = cel.color.rgb8(0, 0, 255),
    green = cel.color.rgb8(34, 139, 24),
    yellow = cel.color.rgb8(255, 255, 0),
    orange = cel.color.rgb8(255, 165, 0),

    brown = cel.color.rgb8(139, 69, 19),
    gray = cel.color.rgb8(111, 111, 111),
    lightgray = cel.color.rgb8(222, 222, 222),
    purple = cel.color.rgb8(160, 32, 240),
    peach = cel.color.rgb8(255, 239, 213),

    skyblue = cel.color.rgb8(0, 191, 255),
    hotpink = cel.color.rgb8(255, 20, 147),
    tan = cel.color.rgb8(188, 137, 80),

    wheat = cel.color.rgb8(245, 222, 179),
    lawngreen = cel.color.rgb8(124, 252, 0),
    
    maroon = cel.color.rgb8(176, 48, 96),
    mistyrose = cel.color.rgb8(255, 228, 225),
    blueviolet = cel.color.rgb8(138, 43, 226),
    darkgreen = cel.color.rgb8(0, 100, 0),
    midnightblue = cel.color.rgb8(25, 25, 112),
    turquoise = cel.color.rgb8(64, 224, 208),
    gold = cel.color.rgb8(255, 215, 0),
    goldenrod = cel.color.rgb8(218, 165, 32),
    rosybrown = cel.color.rgb8(188, 143, 143),
    firebrick = cel.color.rgb8(178, 34, 34),
    burntorange = cel.color.rgb8(210, 105, 30),
    saddlebrown = cel.color.rgb8(139, 69, 19),
    violetred = cel.color.rgb8(208, 32, 144),
    plum = cel.color.rgb8(221, 160, 221),
    slate = cel.color.rgb8(112, 138, 144), 
  }

  local col = cel.col.new(1)

  local row = cel.row.new(1):link(col)
  local function add(tile)
    tile:link(row)
    if row:len() == 3 then
      row = cel.row.new(1):link(col)
    end
  end

  for i, color in ipairs {
    cel.color.rgb8(255, 255, 255), 
    cel.color.rgb8(224, 224, 224),
    cel.color.rgb8(192, 192, 192),

    cel.color.rgb8(160, 160, 160),
    cel.color.rgb8(128, 128, 128),
    cel.color.rgb8(96, 96, 96),

    cel.color.rgb8(64, 64, 64),
    cel.color.rgb8(32, 32, 32),
    cel.color.rgb8(0, 0, 0),

    app.colors.mistyrose, 
    app.colors.pink, 
    app.colors.hotpink,

    app.colors.red, 
    app.colors.violetred, 
    app.colors.firebrick,

    app.colors.plum, 
    app.colors.rosybrown,
    app.colors.slate,

    app.colors.tan,
    app.colors.brown, 
    app.colors.saddlebrown, 
    
    app.colors.wheat,
    app.colors.orange,
    app.colors.burntorange,

    app.colors.yellow, 
    app.colors.gold,
    app.colors.goldenrod,

    app.colors.lawngreen, 
    app.colors.green, 
    app.colors.darkgreen,

    app.colors.turquoise, 
    app.colors.skyblue, 
    app.colors.blue, 

    app.colors.purple, 
    app.colors.blueviolet, 
    app.colors.midnightblue,

  } do

    local tile = cel.slot { face='#556677',
      cel.new(32, 32):setface {
        color = color,
      },
      link='center',
    }:setmargins(4, 4, 4, 4)
    
    add(tile)

    function tile.onmousedown()
      app.pencolor = color
      
      for i, row in col:ilinks() do
        for j, _tile in row:ilinks() do
          if _tile == tile then 
            _tile:setface('#ffffff')
          else 
            _tile:setface('#556677')
          end
        end
      end
    end
  end

  col:get(1):get(1):onmousedown()

  app.colors.cel = col
end

do --app.tiles
  local face = cel.getface('cel'):new {
    image=false,
    color=cel.color.rgb(0, 0, 0),
  }

  function face.cairodraw(_ENV, cr, f, t)
    if f.color then
      cr:set_source_color(f.color)
      cr:rectangle(0, 0, t.w, t.h)
      cr:fill()
      if f.image then
      else
      end
    end
  end

  local function onchange(tile)
    if cel.mouse:isdown(cel.mouse.buttons.left) then
      tile.face.color = app.pencolor
      tile.face.image = app.shape
      app.tiles.dirty = true 
    elseif cel.mouse:isdown(cel.mouse.buttons.right) then
      tile.face.color = false
    end
  end

  local function t()
    local tile = cel.new(32, 32, face:new())
    tile.onmousedown = onchange
    tile.onmouseup = onchange
    tile.onmousein = onchange
    return tile
  end

  app.tiles = {
    { t(),t(),t(),t(),t(),t(),t(),t(),t(),t(),t(),t(),t(),t(),t(),t(),t(),t(),t(),t(),t(),t(),t(),t(),t(),t(),t(),t(),t(),t(),t(),t() }, 
    { t(),t(),t(),t(),t(),t(),t(),t(),t(),t(),t(),t(),t(),t(),t(),t(),t(),t(),t(),t(),t(),t(),t(),t(),t(),t(),t(),t(),t(),t(),t(),t() }, 
    { t(),t(),t(),t(),t(),t(),t(),t(),t(),t(),t(),t(),t(),t(),t(),t(),t(),t(),t(),t(),t(),t(),t(),t(),t(),t(),t(),t(),t(),t(),t(),t() }, 
    { t(),t(),t(),t(),t(),t(),t(),t(),t(),t(),t(),t(),t(),t(),t(),t(),t(),t(),t(),t(),t(),t(),t(),t(),t(),t(),t(),t(),t(),t(),t(),t() }, 
    { t(),t(),t(),t(),t(),t(),t(),t(),t(),t(),t(),t(),t(),t(),t(),t(),t(),t(),t(),t(),t(),t(),t(),t(),t(),t(),t(),t(),t(),t(),t(),t() }, 
    { t(),t(),t(),t(),t(),t(),t(),t(),t(),t(),t(),t(),t(),t(),t(),t(),t(),t(),t(),t(),t(),t(),t(),t(),t(),t(),t(),t(),t(),t(),t(),t() }, 
    { t(),t(),t(),t(),t(),t(),t(),t(),t(),t(),t(),t(),t(),t(),t(),t(),t(),t(),t(),t(),t(),t(),t(),t(),t(),t(),t(),t(),t(),t(),t(),t() }, 
    { t(),t(),t(),t(),t(),t(),t(),t(),t(),t(),t(),t(),t(),t(),t(),t(),t(),t(),t(),t(),t(),t(),t(),t(),t(),t(),t(),t(),t(),t(),t(),t() }, 
    { t(),t(),t(),t(),t(),t(),t(),t(),t(),t(),t(),t(),t(),t(),t(),t(),t(),t(),t(),t(),t(),t(),t(),t(),t(),t(),t(),t(),t(),t(),t(),t() }, 
    { t(),t(),t(),t(),t(),t(),t(),t(),t(),t(),t(),t(),t(),t(),t(),t(),t(),t(),t(),t(),t(),t(),t(),t(),t(),t(),t(),t(),t(),t(),t(),t() }, 
    { t(),t(),t(),t(),t(),t(),t(),t(),t(),t(),t(),t(),t(),t(),t(),t(),t(),t(),t(),t(),t(),t(),t(),t(),t(),t(),t(),t(),t(),t(),t(),t() }, 
    { t(),t(),t(),t(),t(),t(),t(),t(),t(),t(),t(),t(),t(),t(),t(),t(),t(),t(),t(),t(),t(),t(),t(),t(),t(),t(),t(),t(),t(),t(),t(),t() }, 
    { t(),t(),t(),t(),t(),t(),t(),t(),t(),t(),t(),t(),t(),t(),t(),t(),t(),t(),t(),t(),t(),t(),t(),t(),t(),t(),t(),t(),t(),t(),t(),t() }, 
    { t(),t(),t(),t(),t(),t(),t(),t(),t(),t(),t(),t(),t(),t(),t(),t(),t(),t(),t(),t(),t(),t(),t(),t(),t(),t(),t(),t(),t(),t(),t(),t() }, 
    { t(),t(),t(),t(),t(),t(),t(),t(),t(),t(),t(),t(),t(),t(),t(),t(),t(),t(),t(),t(),t(),t(),t(),t(),t(),t(),t(),t(),t(),t(),t(),t() }, 
    { t(),t(),t(),t(),t(),t(),t(),t(),t(),t(),t(),t(),t(),t(),t(),t(),t(),t(),t(),t(),t(),t(),t(),t(),t(),t(),t(),t(),t(),t(),t(),t() }, 
    { t(),t(),t(),t(),t(),t(),t(),t(),t(),t(),t(),t(),t(),t(),t(),t(),t(),t(),t(),t(),t(),t(),t(),t(),t(),t(),t(),t(),t(),t(),t(),t() }, 
    { t(),t(),t(),t(),t(),t(),t(),t(),t(),t(),t(),t(),t(),t(),t(),t(),t(),t(),t(),t(),t(),t(),t(),t(),t(),t(),t(),t(),t(),t(),t(),t() }, 
    { t(),t(),t(),t(),t(),t(),t(),t(),t(),t(),t(),t(),t(),t(),t(),t(),t(),t(),t(),t(),t(),t(),t(),t(),t(),t(),t(),t(),t(),t(),t(),t() }, 
    { t(),t(),t(),t(),t(),t(),t(),t(),t(),t(),t(),t(),t(),t(),t(),t(),t(),t(),t(),t(),t(),t(),t(),t(),t(),t(),t(),t(),t(),t(),t(),t() }, 
    { t(),t(),t(),t(),t(),t(),t(),t(),t(),t(),t(),t(),t(),t(),t(),t(),t(),t(),t(),t(),t(),t(),t(),t(),t(),t(),t(),t(),t(),t(),t(),t() }, 
    { t(),t(),t(),t(),t(),t(),t(),t(),t(),t(),t(),t(),t(),t(),t(),t(),t(),t(),t(),t(),t(),t(),t(),t(),t(),t(),t(),t(),t(),t(),t(),t() }, 
    { t(),t(),t(),t(),t(),t(),t(),t(),t(),t(),t(),t(),t(),t(),t(),t(),t(),t(),t(),t(),t(),t(),t(),t(),t(),t(),t(),t(),t(),t(),t(),t() }, 
    { t(),t(),t(),t(),t(),t(),t(),t(),t(),t(),t(),t(),t(),t(),t(),t(),t(),t(),t(),t(),t(),t(),t(),t(),t(),t(),t(),t(),t(),t(),t(),t() }, 
    { t(),t(),t(),t(),t(),t(),t(),t(),t(),t(),t(),t(),t(),t(),t(),t(),t(),t(),t(),t(),t(),t(),t(),t(),t(),t(),t(),t(),t(),t(),t(),t() }, 
    { t(),t(),t(),t(),t(),t(),t(),t(),t(),t(),t(),t(),t(),t(),t(),t(),t(),t(),t(),t(),t(),t(),t(),t(),t(),t(),t(),t(),t(),t(),t(),t() }, 
    { t(),t(),t(),t(),t(),t(),t(),t(),t(),t(),t(),t(),t(),t(),t(),t(),t(),t(),t(),t(),t(),t(),t(),t(),t(),t(),t(),t(),t(),t(),t(),t() }, 
    { t(),t(),t(),t(),t(),t(),t(),t(),t(),t(),t(),t(),t(),t(),t(),t(),t(),t(),t(),t(),t(),t(),t(),t(),t(),t(),t(),t(),t(),t(),t(),t() }, 
    { t(),t(),t(),t(),t(),t(),t(),t(),t(),t(),t(),t(),t(),t(),t(),t(),t(),t(),t(),t(),t(),t(),t(),t(),t(),t(),t(),t(),t(),t(),t(),t() }, 
    { t(),t(),t(),t(),t(),t(),t(),t(),t(),t(),t(),t(),t(),t(),t(),t(),t(),t(),t(),t(),t(),t(),t(),t(),t(),t(),t(),t(),t(),t(),t(),t() }, 
    { t(),t(),t(),t(),t(),t(),t(),t(),t(),t(),t(),t(),t(),t(),t(),t(),t(),t(),t(),t(),t(),t(),t(),t(),t(),t(),t(),t(),t(),t(),t(),t() }, 
    { t(),t(),t(),t(),t(),t(),t(),t(),t(),t(),t(),t(),t(),t(),t(),t(),t(),t(),t(),t(),t(),t(),t(),t(),t(),t(),t(),t(),t(),t(),t(),t() }, 
  }

  do
    local col = cel.col.new()

    for i = 1, 32 do
      app.tiles[i] = {}
      local tiles = 
      local row = cel.row.new()
      for j = 1, 32 do
        tiles[j] = t():link(row)
      end

      row:link(col)
    end

    app.tiles.cel = cel.slot { face='#995577',
      col,
      link='center',
    }:setmargins(6, 6, 6, 6):setface {color=false, bordercolor=cel.color.rgb(.9, .9, .9), borderwidth=4}

  end
end

app.window.root:addlinks {
  link = 'fill';
    { sandbox, link = 'fill'},
}

--[[
local subject = nil

local function loadtest(path)
    if subject then
      sandbox:clear(subject)
      subject = nil
    end

    if not subject then
      subject =  cel.new()
      subject:link(sandbox, 'fill')
      sandbox:select(subject)

      local sub = assert(dofile(path))
      local begtime = app.getelapsedtime()
      sub(subject)
      dprint(name, ' TIME = ', (app.getelapsedtime() - begtime)/1000)
    else
      sandbox:select(subject)
    end
end

do
  local lfs = require 'lfs'

  local function loadtests(path)
    local list = cel.col.new()

    for file in lfs.dir(path) do
      if file ~= "." and file ~= ".." then
        if string.match(file, '(%a-%.lua)$') then
          local button = cel.textbutton.new(file):link(list, 'width', 10, 0)
          
          function button:onclick()
            loadtest(path..'/'..file)
          end         
        end
      end
    end

    return list
  end

  function loadheaders(path, accordion)
    for file in lfs.dir(path) do
      if file ~= "." and file ~= ".." then

        local attr = lfs.attributes (path..'/'..file)      
        if attr.mode == "directory" then
          local header = cel.textbutton.new(file)
          local list = loadtests(path..'/'..file)
          accordion:add(header, list)

          function header:onclick()
            accordion:toggleselect(self)
          end
        end
      end
    end

    return accordion
  end
end

local list = loadheaders(app.path..'/tests', cel.accordion.new())
--]]




app.tiles.cel:link(app.window.root, 'center')
app.colors.cel:link(app.window.root, 'right.top', 8, 8)
