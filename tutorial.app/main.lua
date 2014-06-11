require 'strict'

local cel=require 'cel'

do --faces
  cel.getface('cel'):new {
    color=cel.color.rgb(0, 1, 1),
    bordercolor=false,
  }:register('@divider')

  cel.getface('text'):new {
    textcolor=cel.color.rgb(.08, .1, .1),
    font=cel.loadfont('sans', 16 *72/96),
    color=false, 
  }:register('@comment')

  cel.getface('text'):new {
    textcolor=cel.color.rgb8(6, 38, 60),
    font=cel.loadfont('code', 12),
    color=false,
  }:register('@code')
end

local printbuffer=cel.printbuffer.new()
local board=cel.panel.new() 
local window=cel.window.new():adddefaultcontrols()

local function loadtut(run, name)
  local filename = app.path..'/tutorials/' .. name .. '.lua'
  board:clear()
  local root=cel.new():link(board, 'fill')

  window:settitle(name)
  if window.listbox then
    window.listbox:unlink()
  end

  window.listbox=cel.scroll.new()
    :link(window, 'fill')

  local list=cel.list.new(0, 0):setface {color='#ff0000', layout={gap=10}}
    :link(window.listbox, 'fill')

  local panels={}

  local pad = cel.text.new('', '@code').h/2

  local function newpanel(comment, code)
    local panel = cel.row.new(0)

    local commentslot = cel.slot.new(400, nil, '#ffffff')
      :setmargins(0, pad, 0, pad)
      :link(panel, 'height')
      --:setface(cel.color.hsl(math.random(360), 1, .5))

    local codeslot = cel.slot.new(0, 0, '#eeeeff')
      :setmargins(0, pad, 0, pad)
      :link(panel, 'fill', 0, 0, {flex=1, minw=true})

    panel.comment = cel.text.new(comment, '@comment'):wrap('word')
      :link(commentslot, 'width.top', 10)

    panel.code = cel.text.new(code, '@code')
      :link(codeslot, 'top')

    return panel
  end

  do
    local panel

    for line in io.lines(filename) do
      local iscomment, comment=string.match(line, '^(%s*)%-%-(.*)')

      if iscomment then
        if not panel or panel.complete then
          panel = newpanel(comment, '')
          panels[#panels+1] = panel
        else
          panel.comment:settext(panel.comment:gettext() ..' '.. comment)
        end
      elseif not panel and (#line == 0 or line == string.match(line, '%s+')) then
      elseif string.find(line, 'pause()', 1, true) then
        panel = cel.textbutton.new('CONTINUE ...')
        panels[#panels+1] = panel
        panel.index = #panels
        panel.pause = true

        function panel:onclick()
          local sti = list:indexof(self)

          list:flux(function()
            self:unlink()
            cel.new(2, 2, '#eeeeff'):link(list, 'width')

            for i=self.index+1, #panels do
              local panel = panels[i]
              panel:link(list, 'width')
              if panel.pause then
                break
              end
            end
          end)

          dprint('scrolltocel', list:get(sti), sti)
          window.listbox:scrolltocel(list:get(sti), 'top')
          run()
        end

        panel = nil
      else
        if panel then
          panel.code:settext(panel.code:gettext() .. line .. '\n')
          panel.complete = true
        else
          panel = newpanel('', line)
          panel.complete = true
          panels[#panels+1] = panel 
        end
      end
    end

  end

  do
    local panel = cel.textbutton.new('FINISH')
    panels[#panels+1] = panel

    function panel:onclick()
      panel:unlink()
      run()
    end
  end

  list:flux(function()
    local dobreak
    for i, panel in ipairs(panels) do
      panel:link(list, 'width')
      if panel.pause then
        if dobreak then
          break
        else
          panel:unlink()
          dobreak = true
        end
      end
    end
  end)

  local func=dofile(filename)

  local funcenv=setmetatable(
    { _print=print, 
      print=function(...)
        printbuffer:print(...)
      end,
      pause=function() coroutine.yield(true) end
    }, 
    {__index=_G})

  setfenv(func, funcenv)
  printbuffer.list:clear()
  func(root)
  root:unlink()
end



do
  local function runtut(txtbtn)
    local run=coroutine.wrap(function(run)
      loadtut(run, txtbtn:gettext())
    end)

    run(run)
  end

  local function initbtn(txtbtn)
    txtbtn.onclick = runtut
  end

  cel { link='fill',
    cel.row { link='fill',
      cel.col {
        link='width',
        cel.textbutton.new('intro'):call(initbtn),
        cel.textbutton.new('linking'):call(initbtn),
        cel.textbutton.new('faces'):call(initbtn),
        cel.textbutton.new('autolayout'):call(initbtn),
        cel.textbutton.new('metacels'):call(initbtn),

        cel.textbutton.new('label'):call(initbtn),
        cel.textbutton.new('grip'):call(initbtn),

        cel.textbutton.new('text'):call(initbtn),
        cel.textbutton.new('button'):call(initbtn),
        cel.textbutton.new('textbutton'):call(initbtn),
        cel.textbutton.new('tldr'):call(initbtn),
      },

      { flex=1, link='fill', 
        cel.col { link='fill', 
          window:resize(800, 600),
          {flex=1,
            cel.row { {flex=1, link='fill', board, printbuffer} }
          }
        },
      },
    }
  }:link(app.window.root, 'fill')
end

