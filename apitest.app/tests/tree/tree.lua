return function(root)


  local cel = require 'cel'

  local indent = 16

  local treeface = cel.getface('tree'):new {
    layout = {
      root = {
       -- link = 'width',
      },
      list = {
        link = {'left', indent},
      }
    }
  }

  local newtree do
    function newtree(text)
      local tree
      local treeroot = cel.row{
        link='center',
        cel.button {
          w=indent, h=indent,
          onclick=function()
            dprint('clicked', tree, tree.id)
            tree:togglestate()
          end
        },
        { flex=1, minw=true, link='width',
          cel.text {
            text=text,
            justify='left',
          }
        }
      }

      tree=cel.tree.new(treeroot)
      return tree
    end
  end

  local function buildstrings(filepath, dsiplayname)
    local t = {displayname or filepath}

    for file in lfs.dir(filepath) do
      if file ~= "." and file ~= ".." then
        local filepath = filepath .. '\\' .. file
        if 'directory' == lfs.attributes(filepath, 'mode') then
          t[#t+1] = buildstrings(filepath, file)
        else
          t[#t+1]=file
        end
      end
    end

    return t
  end
  local startstrings = os.clock()
  local strings = buildstrings(lfs.currentdir())
  dprint('strings', os.clock() - startstrings)


  local function buildtree(t)
    local tree = newtree(t[1])

    tree:flux(function()
      for i = 2, #t do
        local ti = t[i]
        if 'table' == type(ti) then
          buildtree(ti):link(tree)
        else
          cel.label.new(ti):link(tree)
        end
      end
    end)

    tree:setface {
      color = cel.color.rgb8(math.random(255), math.random(255), math.random(255)),
    }

    return tree
  end

  local starttree = os.clock()
  --local tree = buildtree(lfs.currentdir())
  local tree = buildtree(strings)

  cel.window { w=300, h=300, title='tree',
    link='fill',
    cel.scroll { link='fill', tree },
  }:link(root, 'center'):relink()
    :adddefaultcontrols()

  dprint('buildtree', os.clock() - starttree)
  dprint(cel.new().id)
end
