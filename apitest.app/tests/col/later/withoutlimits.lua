local cel = require 'cel'

return function(root)

  root:addlinks {
    cel.col {

      function(col)
        col:resize(400, 400)
      end,

      cel.row {
        cel.button {
          w = 100, h = 100,
          cel.label.new'no linker';
        },
        cel.button {
          w = 100, h = 100,
          cel.label.new'no linker';
        },
      },
      cel.row {
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
      cel.row {
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
      cel.row {
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
      cel.row {
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
        cel.row {
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
      cel.row {
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
      cel.row {
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
      cel.row {
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
    },
  }
end


