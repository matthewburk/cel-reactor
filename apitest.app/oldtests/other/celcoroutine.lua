local cel = require 'cel'

return function(root)

  --[[
  local celx = {}

  cel.fork = function(acel, f)
    local run = coroutine.wrap(f)
    acel[_fork] = run
    return run(acel, coroutine.yield)
  end

  cel.resumefork = function(acel, ...)
    --find fork, look to hosts until one is found, root has the catchall, which raises an error
    local fork = foundfork

    return fork(acel, ...)
  end
  --]]

  local btn = cel.textbutton {
    text = 'coshow',
  }:link(root, 'center'):relink()

  local choice = cel.col {
    face = cel.colorface(cel.color.rgb(0, 0, .3)),
    link = 'width',
    'Make a selection',
    cel.textbutton {
      text = 'real',
      onclick = function(textbtn)
        cel.resumefork(textbtn, textbtn)
      end
    },
    cel.textbutton.new('B'),
    cel.textbutton.new('C'),
    cel.textbutton.new('D'),
  }

  function btn:onclick()
    local action = cel.fork(choice,
    function(choice, yield)
      choice:link(root, 'center')
      local ret = yield('waiting for selection')

      dprint('have selection', ret)
      choice:unlink()
    end)

    dprint('action', action)
  end
end

