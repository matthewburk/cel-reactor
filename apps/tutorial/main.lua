require 'stdinit'
require 'strict'

local celdriver = require 'celdriver'
local cel = require 'cel'

---[[
celdriver.resize(1920/1.5, 1080/1.5)

function reactor.resized()
  celdriver.resize(1920/1.5, 1080/1.5)
end
--]]

function reactor.keydown(key, ...)
  celdriver.keydown(key, ...)
  if key == 'space' then
    cel.printdescription()
  elseif key == 'f1' then
    reactor.fullscreen(true)
  elseif key == 'f2' then
    reactor.fullscreen(false)
  elseif key == 'escape' then
    reactor.quit()
  end
end

do --faces
  cel.getface('cel'):new {
    fillcolor = cel.color.rgb(0, 1, 1),
    linecolor = false,
  }:register('@divider')

  cel.getface('listbox'):new {
    color = cel.color.rgb8(250, 250, 250),
    flow = {
      scroll = cel.flows.constant(500),
      showybar = cel.flows.linear(300),
      hideybar = cel.flows.linear(100),
      showxbar = cel.flows.linear(100),
      hidexbar = cel.flows.linear(100),
    },
  }:register('@code')

  cel.getface('text'):new {
    textcolor = cel.color.rgb8(116, 96, 116),
    font = cel.loadfont('monospace', 12*72/96),
    fillcolor = false, --cel.color.rgb(.9, .9, .95),
  }:register('@comment')

  cel.getface('label'):new {
    textcolor = cel.color.rgb8(6, 38, 60),
    font = cel.loadfont('code', 12),
    fillcolor = false,
  }:register('@code')

  cel.getface('slot'):new {
    linewidth = 1,
    linecolor = cel.color.rgb8(221, 221, 221),
    fillcolor = cel.color.rgb8(245, 244, 238),
  }:register('@commentbox')
end

local tut = {}

local newboard
do
  local metacel, metatable = cel.newmetacel('board')

  function metatable.print(board, ...)
    return tut.printbuffer:print(...)
  end

  function metatable.clear(board)
    for link in pairs(board.links) do
      link:unlink()
    end
  end

  function metacel:onlink(board, link)
    board.links[link] = link 
  end

  function metacel:onunlink(board, link)
    board.links[link] = nil 
  end

  do
    local _new = metacel.new
    function metacel:new(w, h, face)
      local board = _new(self, w, h, face) 
      board.links = {}
      return board
    end
  end
  
  newboard = function()
    return metacel:new()
  end
end

function tut:start()
  self.run = coroutine.create(self.run, self)
  self:resume()
end

function tut:resume()
  if self.run then
    local ok, msg = coroutine.resume(self.run, self)

    if not ok then
      error(msg)
    end

    if coroutine.status(self.run) == 'dead' then
      self.run = nil
    end
  end
end

function tut:pause()
  coroutine.yield(true)
end

local function loadtut(tut, name)
  tut.window:settitle(name)
  if tut.window.listbox then
    tut.window.listbox:unlink()
  end
  tut.window.listbox = cel.listbox.new(0, 0, '@code')
  tut.window.listbox:link(tut.window, 'fill')

  local listbox = tut.window.listbox

  do
    local firstpause = true
    local lines = {}
    local header = lines
    local commentbox 

    for line in io.lines('tutorials/' .. name .. '.lua') do
      
      local iscomment, comment = string.match(line, '^(%s*)%-%-(.*)')
      if iscomment then
        if not commentbox then
          commentbox = cel.text.new(comment, '@comment')
          local font = cel.getface('label', '@code').font
          local slothost = cel.slot.new(font:measureadvance(iscomment), 0, 5)
          local slot = cel.slot.new(5, 5, 5, 5, 0, 0, '@commentbox'):link(slothost, 'width')
            

          lines[#lines + 1] = slothost
          commentbox:link(slot, 'width')
        else
          commentbox:settext(commentbox:gettext() ..' '.. comment)
        end
      elseif string.find(line, 'pause()', 1, true) then
        commentbox = nil
        if firstpause then
          firstpause = false
        else
          local button = cel.textbutton.new('CONTINUE ...')
          lines[#lines + 1] = button

          function button:onclick()
            local i = listbox:indexof(self)
            self:unlink()
            listbox:selectall(true)
            local hbar = cel.new(2, 1, '@divider'):link(listbox, 'width', 10)
            listbox:flux(function()
              for i, line in ipairs(button.lines) do
                line:link(listbox, 'width')
              end
            end)
            listbox:scrollto(0, hbar.y)
            tut:resume()
          end

          button.lines = {}
          lines = button.lines
        end
      else
        commentbox = nil
        lines[#lines + 1] = cel.label.new(line, '@code') 
      end
    end
    do
      local button = cel.textbutton.new('Next Tutorial')
      lines[#lines + 1] = button

      function button:onclick()
        tut:resume()
      end
    end

    listbox:flux(function()
      for i, line in ipairs(header) do
        line:link(listbox, 'width')
      end
    end)
  end

  local func = require('tutorials/' .. name)

  local funcenv = setmetatable(
    { _print = print, 
      print = function(...)
        tut.board:print(...)
      end,
      pause = tut.pause,
    }, 
    {__index=_G})

  setfenv(func, funcenv)
  func(tut.board)
  tut.board:clear()
end

function tut:run()
  loadtut(self, 'tldr')
  loadtut(self, 'intro')
  loadtut(self, 'faces')
  loadtut(self, 'autolayout')
  loadtut(self, 'linking')
  loadtut(self, 'did i mention linkers')
  loadtut(self, 'metacels and factorys')
  --metacels
  loadtut(self, 'textbutton')
  loadtut(self, 'text')
  loadtut(self, 'button')
  loadtut(self, 'label')
  loadtut(self, 'textbutton')
  self:reset()
end


do
  tut.printbuffer = cel.printbuffer.new()
  tut.board = newboard()

  tut.window = cel.window {
    function(window)
      local button = cel.button {
        w = 24, h = 24,
        onclick = function()
          if window:getstate() == 'maximized' then
            window:restore()
          else
            window:maximize()
          end
        end
      }
      window:addcontrols(button, 'right')
    end,
  }

  cel { link = 'fill';
    cel.row { link = 'fill';
      { flex=1; minw=0;
        tut.window 
      },

      { flex=1; minw=0;
        cel.col { link = 'fill';
          { flex=2; 
            tut.board;
          },

          cel.new(1,1, cel.colorface(cel.color.rgb(1, 1, 1)));

          { flex=1; 
            tut.printbuffer;
          },
        },
      },
    }
  }:link(celdriver.root, 'fill')

  tut:start()
end

