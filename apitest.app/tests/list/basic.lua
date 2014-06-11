local cel=require 'cel'

return function(root)

  do
    local scroll=cel.scroll.new()

    local list=cel.list.new()
      :link(scroll, 'fill')

    function list:onchange(...)
      print(self, ...)
    end

    for i=1, 20 do
      local btn=cel.textbutton.new('item '..i):link(list, 20)
      --list:setslotface(btn, '#ff7fff')
    end

    function list:onmousedown(button, x, y, intercepted)
      if not intercepted then
        local item, index=self:pick(x, y)
        if item then
          item:takefocus()
          if cel.keyboard:isdown('shift') then
            self:select(item)
          end
          self:setcurrent(item)
        end
      end
    end

    function list:onkeypress(key, intercepted)
      dprint(self, key, intercepted)
      if 'up' == key then
        local current = self:getcurrent()
        dprint('current', current)
        self:setcurrent(list:prev(current))
        scroll:jumptocel(self:getcurrent())
        return true
      elseif 'down' == key then
        local current = self:getcurrent()
        dprint('current', current)
        self:setcurrent(list:next(current))
        scroll:jumptocel(self:getcurrent())
        return true
      end
    end
    
    cel.window {
      title='A listbox',
      w=200, 
      h=400, 
      link='fill',
      scroll,
    }:adddefaultcontrols():link(root)
  end

  cel.window {
    title='A list - testing unlink',
    w=200, 
    h=400, 

    link='fill',

    cel.scroll {
      link='fill', 
      cel.list {
        function(list)
          cel.textbutton.new('This button does nothing')
            :link(list, 'fill', 0, 0, {flex=1, minh=100})

          for i=1, 20 do
            local button=cel.textbutton.new('click to remove '..i)
              :link(list, 'width')
            button.onclick=button.unlink
          end
        end
      },
    },
  }:adddefaultcontrols():link(root)

  do
    local list=cel.list {
      'this',
      'is',
      'a',
      'listbox with text',
      'pretty',
      'basic',
      'stuff',

      onmousedown=function(list, button, x, y, intercepted)
        if not intercepted then
          local item, index=list:pick(x, y)
          list:select(item)
        end
      end,

      onchange=dprint,
    }

    cel.window {
      title='A list - testing selection',
      w=200, 
      h=400, 

      link='fill',

      cel.row {
        { link='width',
          cel.textbutton {
            text='remove',

            onclick=function(button)
              for item in list:selecteditems() do
                dprint(item)
                item:unlink()
              end
            end
          }
        },
        { link='fill', flex=1,
          cel.scroll { link='fill',
            list, 
          },
        },
      },
    }:adddefaultcontrols():link(root, 'right'):relink()
  end
end

