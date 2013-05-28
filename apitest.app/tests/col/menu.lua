return function(root)
  local cel = require 'cel'

  local menu = cel.menu {
    cel.text.new [[this is a rather large item]],
    'is',
    'a',
    'menu',
    { submenu = 'submenu';
      'a',
      'b',
      { submenu = cel.textbutton.new('submenu2');
        '1',
        '2',
        '3';
      };
      'c',
    },

    { submenu = 'submenu';
      'a',
      'b',
      { submenu = cel.textbutton.new('submenu2');
        '1',
        '2',
        '3';
      };
      'c',
    },
  }

  local window = cel.window.new(200, 200):link(root, 'fill'):relink()

  cel.string.link('hello ima string', window, 'center')


  cel.row {
    cel.textbutton {
      text = 'A menu',
      onclick = function(txtbtn, button, x, y)
        x, y = cel.translate(txtbtn, 0, txtbtn.b, root)
        txtbtn.menu:showat(x, y, root)
      end,
      function(txtbtn)
        txtbtn.menu = cel.menu {
          'A', 'a', 'AA', 'AaA',
          onchoose = function(menu, item)
            menu:hide()
            dprint(item)
          end,
        }
      end,
    },
    cel.textbutton {
      text = 'B menu',
      onclick = function(txtbtn, button, x, y)
        x, y = cel.translate(txtbtn, 0, txtbtn.b, root)
        txtbtn.menu:showat(x, y, root)
      end,
      function(txtbtn)
        txtbtn.menu = cel.menu {
          'B', 'b', 'BB', 'BbB',
          onchoose = function(menu, item)
            --menu:hide()
            dprint(item)
          end,
          { submenu='C',
            'C', 'c', 'CC',
          },
          { submenu='Its an editbox',
            cel.editbox.new('edit me', 10):setlimits(200),
            cel.editbox.new('edit me', 10):setlimits(200),
            cel.editbox.new('edit me', 10):setlimits(200),
            cel.editbox.new('edit me', 10):setlimits(200),
            cel.editbox.new('edit me', 10):setlimits(200),
            cel.slider.new(),
          },
        }
      end,
    },
  }:link(window, 'top')

  function menu:onchoose(item)
    self:unlink()
    dprint(item)
  end

  function window:onmousedown(button, x, y, incept)
    if button == cel.mouse.buttons.right then
      x, y = cel.translate(self, x, y, root)
      menu:showat(x+1, y+1, root)
      menu:disable()
      cel.doafter(100, function() menu:enable() end)
    end
  end
end
