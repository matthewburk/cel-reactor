local cel = require 'cel'

return function(root)

  root:addlinks {
    cel.row {
      function(row)
        row:resize(400, 400)
      end,
      cel.col {
        cel.button {
          w = 100, h = 100,
          cel.label.new'no linker';
        },
        cel.button {
          w = 100, h = 100,
          cel.label.new'no linker';
        },
      },
      cel.col {
        link = 'top';
        cel.button {
          w = 100, h = 100,
          cel.label.new'top';
        },
        cel.button {
          w = 100, h = 100,
          cel.label.new'top';
        },
      },
      cel.col {
        link = 'left';
        cel.button {
          w = 100, h = 100,
          cel.label.new'left';
        },
        cel.button {
          w = 100, h = 100,
          cel.label.new'left';
        },
      },
      cel.col {
        link = 'right';
        cel.button {
          w = 100, h = 100,
          cel.label.new'right';
        },
        cel.button {
          w = 100, h = 100,
          cel.label.new'right';
        },
      },
      cel.col {
        link = 'bottom';
        cel.button {
          w = 100, h = 100,
          cel.label.new'bottom';
        },
        cel.button {
          w = 100, h = 100,
          cel.label.new'bottom';
        },
      },
      cel.window {
        link = 'fill';
        function(w) w:adddefaultcontrols() end;
        cel.col {
          link = 'center';
          cel.button {
            w = 100, h = 100,
            cel.label.new'center';
          },
          cel.button {
            w = 100, h = 100,
            cel.label.new'center';
          },
        },
      },
      cel.col {
        link = 'height';
        cel.button {
          w = 100, h = 100,
          cel.label.new'height';
        },
        cel.button {
          w = 100, h = 100,
          cel.label.new'height';
        },
      },
      cel.col {
        link = 'width';
        cel.button {
          w = 100, h = 100,
          cel.label.new'width';
        },
        cel.button {
          w = 100, h = 100,
          cel.label.new'width';
        },
      },
      cel.col {
        link = {'fill.margin', -5, -5};
        cel.button {
          w = 100, h = 100,
          cel.label.new'fill.margin';
        },
        cel.button {
          w = 100, h = 100,
          cel.label.new'fill.margin';
        },
      },
    }
  }

end

