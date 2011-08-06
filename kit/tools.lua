local kit = require 'kit'

--properties
--host
--linker
--x, y, w, h
--name

do
  local panels = {}

  panels.linkers = kit.panel {
    { link = {'edges', 5, 5};
      kit.selector {
        'width', 'height', 'edges',
        onselect = function(_, item)
          proto.link.linker = item:gettext()
        end
      }
      kit.selector {
        'width', 'height', 'edges',
        onselect = function(_, item)
          proto.link.linker = item:gettext()
        end
      }
    },
  }
  function showprop(name)

  end
end

function propselect(name)
  local button = kit.textbutton.new(name)
  button.onclick = function(button)
    showprop(name)
  end
  return button
end

local propetypanel = kit.panel {
  { name = 'property select';
    kit.listbox {
      kit.textbutton.new('name'),
      kit.textbutton.new('host'),
      kit.textbutton.new('linker'),
      kit.textbutton.new('rect'),
    }
  }
}

kit.
function pro

function kit.maketextbutton()
  local code = [[
    { link = {${linker}, {$xval}, {$yval}};
      kit.textbutton {
        __name = ${name},
        face = ${face},
      },
    },
  ]]

end

function kit.makerow()
  local code = [[
    { link = {${linker}, {$xval}, {$yval}};
      kit.row {
        __name = ${name},
        face = ${face},
      },
    },
  ]]

end
