local cel = require 'cel'

return function(root)

  local function buildtree(multitree, filepath)
    for file in lfs.dir(filepath) do
      if file ~= "." and file ~= ".." then
        local filepath = filepath .. '\\' .. file

        if 'directory' == lfs.attributes(filepath, 'mode') then
          local tree = multitree:newtree{ file=file, attribute='directory' }
          buildtree(tree, filepath)
        else
          multitree:newrecord{ file=file, attribute='file' }
        end
      end
    end

    return multitree--:maximize()
  end

  local multitree = cel.multitree.new { 'file', 'attribute' }
  buildtree(multitree, lfs.currentdir())

  cel.window { w=300, h=300, title='tree',
    link='fill',
    cel.scroll { link='fill', multitree },
  }:link(root, 'center'):relink()
    :adddefaultcontrols()
end
