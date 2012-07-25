local cel = require 'cel'

return function(root)

  local panel 
  panel = cel.newnamespace {
    new = function(metacel, ...)
      local ret = cel[metacel].new(...)
      return ret 
    end,

    compile = function(metacel, t)
      local ret = cel[metacel](t)

      if t.appname then
        panel.cels[t.appname] = ret
      end

      return ret
    end,

    cels = setmetatable({}, {__mode='kv'})
    
  }

  local function sliderchanged(slider, value)
    local label = panel.cels.listbox:prev(slider)
    label:printf('%d of %d stepby %d', value, slider:getmaxvalue(), slider:getstepvalue())
    dprint(label)
  end

  panel.window {
    w = root.w/2;
    h = root.h/2;
    link = 'fill';
    panel.listbox { 
      appname = 'listbox';

      link = cel.composelinker('width', 'center');
      'ABA', panel.slider { direction='horizontal', min=0, max=100, step=10, onchange=sliderchanged, },
      'ABA', panel.slider { direction='horizontal', min=0, max=100, step=15, onchange=sliderchanged, },
      'ABA', panel.slider { direction='horizontal', min=0, max=100, step=20, onchange=sliderchanged, },
      'ABA', panel.slider { direction='horizontal', min=0, max=100, step=25, onchange=sliderchanged, },
    }
  }:link(root, 'center'):relink()
  
end

