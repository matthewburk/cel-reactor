return function(root)
  local cel = require 'cel'

  local menu = cel.menu {
    [[This is a popup menu.]],
    [[It has multiple submenus]],
    cel.text.new [[[
    Like all cels you can
    put any cel in here.]],

    cel.menu.divider,

    { submenu = 'text',
      cel.text {
        --[[
        face=cel.assertface('text', '@redborder', {
          borderwidth=2,
          bordercolor=cel.color.rgb(1, 0, 0),
        }),
        --]]

        face=cel.getface('text'):new {
          borderwidth=2,
          bordercolor=cel.color.rgb(1, 0, 0),
        },

        text=[[[
        This is a 
        left      
        justified text cel.]],
      },

      cel.text.new [[[
      This is a 
      right 
      justified text cel.]]
        :justify('right'),

      cel.text.new [[[
      This is a 
      center
      justified text cel.]]:justify('center'),
    },

    { submenu = cel.textbutton.new('buttons'),
      cel.textbutton.new [[[
      this is
      a button]],
      {link='left', cel.textbutton.new 'left'},
      {link='right', cel.textbutton.new 'right'},
      {link='center', cel.textbutton.new 'center'},

      { submenu = cel.textbutton.new('in a row'),
        cel.row {
          cel.textbutton.new '1',
          cel.textbutton.new '2',
          cel.textbutton.new '3',
        },
      },
      { submenu = cel.textbutton.new('in a col'),
        cel.col {
          cel.textbutton.new '1',
          cel.textbutton.new '2',
          cel.textbutton.new '3',
        },
      },
    },

    { submenu = cel.editbox.new 'editbox',
      cel.editbox.new 'a',
      cel.editbox.new 'b',
      { submenu = cel.textbutton.new('submenu2'),
        '1',
        '2',
        '3',
      },
    },

    { submenu = 'This is silly',
      cel.window {
        w=200, h=200,
        title='This is silly',
        link = 'center',
        'right click',

        function(window)
          window:setlimits(window.w, nil, window.h, nil)
          local menu = cel.menu {
            'See',
            'I told you',
          }

          function menu:onchoose(item)
            self:unlink()
            dprint(item)
          end

          function window:onmousedown(button, x, y)
            if button == cel.mouse.buttons.right then
              x, y = cel.translate(self, x, y, root)
              menu:showat(x+1, y+1, root)
            end
          end
        end,
      },
    },
  }

  local window = cel.window.new()
    :settitle('This window has a popup menu')
    :link(root, 'fill.margin', 50)
    :relink()

  cel.text.new [[[
  Right click anywhere on the window
  to show a popup menu.]]
    :justify('center')
    :link(window, 'center')


  menu:sort(function(a, b)
    return b.id < a.id
  end)

  function menu:onchoose(item)
    self:unlink()
    dprint(item)
  end

  function window:onmousedown(button, x, y)
    if button == cel.mouse.buttons.right then
      x, y = cel.translate(self, x, y, root)
      menu:showat(x+1, y+1, root)
      menu:disable()
      cel.doafter(100, function() menu:enable() end)
    end
  end
end
