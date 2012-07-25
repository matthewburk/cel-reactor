require 'stdinit' (app.name)

reactor = {}

return function()
  function _G.lerp(a, b, p)
    return a + p * (b - a)
  end

  function _G.smoothstep(a, b, p)
    return lerp(a, b, p*p*(3-2*p))
  end

  function _G.rlerp(a, b, c)
    return (c - a)/(b - a);
  end

  if window then
    local _window = window
    local window = {}

    local observers = {}

    do
      function window:notify(event, ...)
        local t = observers[event]
        if t then
          for f in pairs(t) do
            f(self, ...)
          end
        end
      end

      function window:onevent(event, f)
        local t = observers[event] 
        if not t then
          t = {}
          observers[event] = t
        end

        t[f] = true
       
        return function()
          t[f] = nil
        end
      end

      local reservedkeys = {
        onchar='char',
        onkeydown='keydown',
        onkeyup='keyup',
        onmouseenter='mouseenter',
        onmouseexit='mouseexit',
        onmousemove='mousemove',
        onmousedoubleclick='mousedoubleclick',
        onmousedown='mousedown',
        onmouseup='mouseup',
        onmousewheel='mousewheel',
        onwindowevent='windowevent',
        oncommand='command',
        update='update',
        ondraw='draw',
      }

      setmetatable(window, 
        {
          __index=_window,
          __newindex=function(t, k, v)

            if reservedkeys[k] then
              k = reservedkeys[k]
              window:onevent(k, v)
            else
              rawset(window, k, v)
            end
          end,
      })
    end

    local cel = require 'cel' 

    local driver = cel.installdriver(
      { --mouse
        states = { up = 'up', down = 'down' },
        buttons = { left = 'left', middle = 'middle', right = 'right' },
        wheel = { up = 1, down = -1 },
      },
      { --keyboard
        states = { up = 'up', down = 'down' },
        keys = {
          ['backspace'] = 'backspace',
          ['tab'] = 'tab',
          ['enter'] = 'enter',
          ['shift'] = 'shift',
          ['ctrl'] = 'ctrl',
          ['alt'] = 'alt',
          ['pause'] = 'pause',
          ['capslock'] = 'capslock',
          ['escape'] = 'escape',
          ['space'] = 'space',
          ['pageup'] = 'pageup',
          ['pagedown'] = 'pagedown',
          ['end'] = 'end',
          ['home'] = 'home',
          ['left'] = 'left',
          ['up'] = 'up',
          ['right'] = 'right',
          ['down'] = 'down',
          ['printscreen'] = 'printscreen',
          ['insert'] = 'insert',
          ['delete'] = 'delete',
          ['0'] = '0',
          ['1'] = '1',
          ['2'] = '2',
          ['3'] = '3',
          ['4'] = '4',
          ['5'] = '5',
          ['6'] = '6',
          ['7'] = '7',
          ['8'] = '8',
          ['9'] = '9',
          ['a'] = 'a',
          ['b'] = 'b',
          ['c'] = 'c',
          ['d'] = 'd',
          ['e'] = 'e',
          ['f'] = 'f',
          ['g'] = 'g',
          ['h'] = 'h',
          ['i'] = 'i',
          ['j'] = 'j',
          ['k'] = 'k',
          ['l'] = 'l',
          ['m'] = 'm',
          ['n'] = 'n',
          ['o'] = 'o',
          ['p'] = 'p',
          ['q'] = 'q',
          ['r'] = 'r',
          ['s'] = 's',
          ['t'] = 't',
          ['u'] = 'u',
          ['v'] = 'v',
          ['w'] = 'w',
          ['x'] = 'x',
          ['y'] = 'y',
          ['z'] = 'z',
          ['numpad0'] = 'numpad0',
          ['numpad1'] = 'numpad1',
          ['numpad2'] = 'numpad2',
          ['numpad3'] = 'numpad3',
          ['numpad4'] = 'numpad4',
          ['numpad5'] = 'numpad5',
          ['numpad6'] = 'numpad6',
          ['numpad7'] = 'numpad7',
          ['numpad8'] = 'numpad8',
          ['numpad9'] = 'numpad9',
          ['multiply'] = 'multiply',
          ['add'] = 'add',
          ['subtract'] = 'subtract',
          ['decimal'] = 'decimal',
          ['divide'] = 'divide',
          ['f1'] = 'f1',
          ['f2'] = 'f2',
          ['f3'] = 'f3',
          ['f4'] = 'f4',
          ['f5'] = 'f5',
          ['f6'] = 'f6',
          ['f7'] = 'f7',
          ['f8'] = 'f8',
          ['f9'] = 'f9',
          ['f10'] = 'f10',
          ['f11'] = 'f11',
          ['f12'] = 'f12',
          ['numlock'] = 'numlock',
          ['scrolllock'] = 'scrolllock',
          ['equal'] = 'equal',
          ['comma'] = 'comma',
          ['minus'] = 'minus',
          ['period'] = 'period',
          ['semicolon'] = 'semicolon',
          ['slash'] = 'slash',
          ['graveaccent'] = 'graveaccent',
          ['openbracket'] = 'openbracket',
          ['backslash'] = 'backslash',
          ['closebracket'] = 'closebracket',
          ['apostrophe'] = 'apostrophe',
        },
      })

    local windowtoroot = function()
      local rootrect = { x = 0, y = 0, w = 0, h = 0 }

      local function handleresize()
        local w, h = driver.root.w, driver.root.h
        local x, y, aw, ah = cel.getlinker('fill.aspect')(window.w, window.h, 0, 0, w, h, w/h)
        rootrect.x = x
        rootrect.y = y
        rootrect.w = aw
        rootrect.h = ah
      end

      function driver.root:onresize()
        return handleresize()
      end

      function _window.onresize(w, h)
        window.w = w
        window.h = h
        handleresize()
        driver.root:resize(w, h)
        window:notify('resize', w, h)
      end

      return function(x, y, ...)
        x = x - rootrect.x
        y = y - rootrect.y
        x = driver.root.w/rootrect.w * x
        y = driver.root.h/rootrect.h * y
        return math.floor(x + .5), math.floor(y + .5), ...
      end
    end

    windowtoroot = windowtoroot()

    function _window.onchar(c)
      driver.char(c)
      window:notify('char', c)
    end

    function _window.onkeydown(key, rep, alt, ctrl, shift)
      if not rep then
        driver.keydown(key, alt, ctrl, shift)
      end

      driver.keypress(key, alt, ctrl, shift)
      window:notify('keydown', key, rep, alt, ctrl, shift)
    end

    function _window.onkeyup(key, alt, ctrl, shift)
      driver.keyup(key, alt, ctrl, shift)
      window:notify('keyup', key, alt, ctrl, shift)
    end

    function _window.onmouseenter()
      window:notify('mouseenter')
    end

    function _window.onmouseexit()
      window:notify('mouseexit')
    end

    function _window.onmousemove(x, y, alt, ctrl, shift)
      driver.mousemove(windowtoroot(x, y))
      window:notify('mousemove', x, y, alt, ctrl, shift)
    end

    function _window.onmousedoubleclick(button, x, y, alt, ctrl, shift)
      window:notify('mousedoubleclick', button, x, y, alt, ctrl, shift)
    end

    function _window.onmousedown(button, x, y, alt, ctrl, shift)
      driver.mousedown(windowtoroot(x, y, button, alt, ctrl, shift))
      window:notify('mousedown', button, x, y, alt, ctrl, shift)
    end

    function _window.onmouseup(button, x, y, alt, ctrl, shift)
      driver.mouseup(windowtoroot(x, y, button, alt, ctrl, shift))
      window:notify('mouseup', button, x, y, alt, ctrl, shift)
    end

    function _window.onmousewheel(delta, step, x, y, alt, ctrl, shift)
      local direction 

      if delta > 0 then
        direction = cel.mouse.wheel.up
      else
        direction =  cel.mouse.wheel.down
      end

      delta = math.abs(delta)
      for i=1,delta do
        driver.mousewheel(windowtoroot(x, y, direction, step, alt, ctrl, shift))
      end
      window:notify('mousewheel', delta, step, x, y, alt, ctrl, shift)
    end

    function _window.oncommand( command )
      driver.command(c)
      reactor.notify('command', command)
    end

    do
      local lastdrawms = 0
      function _window.draw()
        local predrawms = reactor.timermillis()
        if window.draw then
          window:draw()
        end
        local ms = reactor.timermillis()

        window:notify('draw', ms-lastdrawms, ms-predrawms)
        lastdrawms = ms
      end
    end

    function reactor.ontick(millis)
      driver.tick(millis)
    end

    do
      local names = {
        code = string.format('%s/data/fonts/%s', reactor.path, 'FixedsysExcelsiorIIIb.ttf'),
        monospace = string.format('%s/data/fonts/%s', reactor.path, '/ttf-bitstream-vera-1.10/VeraMono.ttf'),
        serif = string.format('%s/data/fonts/%s', reactor.path, '/ttf-bitstream-vera-1.10/VeraSe.ttf'),
        sansserif = string.format('%s/data/fonts/%s', reactor.path, '/ttf-bitstream-vera-1.10/Vera.ttf'),
        default = string.format('%s/data/fonts/%s', reactor.path, 'arial.ttf'),
      }

      function driver.loadfont(name, weight, slant, size)
        name = names[name] or name 

        dprint('driver.loadfont', name)

        local cr = cairo.create(cairo.surface.create(0, 0))
        local cairofont = cairo.font.create(name)

        cr:set_font_face(cairofont)
        cr:set_font_size(size)

        local ascent, descent, lineheight = cr:font_extents()
        local _, _, emwidth, emheight, emadvance = cr:text_extents(' ')

        local font = {
          cairofont = cairofont,
          name = name,
          weight = weight,
          slant = slant,
          size = size,
          lineheight = math.ceil(lineheight),
          ascent = math.ceil(ascent),
          descent = math.ceil(descent),
          emwidth = emwidth, 
          emheight = emheight,
          emadvance = emadvance,
          metrics = setmetatable({}, {__index = function(glyphmetrics, utf8codepoint)
            local xbr, ybr, w, h, xadv, yadv = cr:text_extents(utf8codepoint)      
            glyphmetrics[utf8codepoint] = {
              utf8codepoint = utf8codepoint,
              advance = xadv,
              xmin = xbr,
              xmax = xbr + w,
              ymin = ybr,
              ymax = ybr + h,
            }
            return glyphmetrics[utf8codepoint]
          end})
        }

        return font 
      end
    end

    do --driver.clipboard
      function driver.clipboard(command, data)
        if command == 'get' then
          return reactor.getclipboardtext()
        elseif command == 'put' then
          reactor.setclipboardtext(data)
        end
      end
    end

    app.window = window
    local faces = require('reactor.faces')

    function driver.root.draw()
      return faces.draw()
    end

    --TODO window.root should be linked to driver.root so we don't mess with onresize
    window.root = driver.root:takefocus() --TODO it should havefocus by default, fix bug in cel

    _window.onresize(_window.w, _window.h)
  end
end
