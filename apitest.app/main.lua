local cel = require 'cel'

--make root cel a fixed size, it will scale, by default it is size to app.window size
--app.window.root:setlimits(nil, nil, 1200, 1200)

local sandbox = cel.mutexpanel.new(100, 100)

local subject = nil

local function loadtest(path)
    if subject then
      sandbox:clear(subject)
      subject = nil
    end

    if not subject then
      subject =  cel.new()
      subject:link(sandbox, 'fill')
      sandbox:select(subject)

      local sub = assert(dofile(path))
      local begtime = app.getelapsedtime()
      sub(subject)
      dprint(name, ' TIME = ', (app.getelapsedtime() - begtime)/1000)
    else
      sandbox:select(subject)
    end
end

do
  local lfs = require 'lfs'

  local function loadtests(path)
    local list = cel.col.new()

    for file in lfs.dir(path) do
      if file ~= "." and file ~= ".." then
        if string.match(file, '(%a-%.lua)$') then
          local button = cel.textbutton.new(file):link(list, 'width', 10, 0)
          
          function button:onclick()
            loadtest(path..'/'..file)
          end         
        end
      end
    end

    return list
  end

  function loadheaders(path, accordion)
    for file in lfs.dir(path) do
      if file ~= "." and file ~= ".." then

        local attr = lfs.attributes (path..'/'..file)      
        if attr.mode == "directory" then
          local header = cel.textbutton.new(file)
          local list = loadtests(path..'/'..file)
          accordion:add(header, list)

          function header:onclick()
            accordion:toggleselect(self)
          end
        end
      end
    end

    return accordion
  end
end

local list = loadheaders(app.path..'/tests', cel.accordion.new())

app.window.root:addlinks {
  link = 'fill';
  cel.row {
    { list, link = 'fill' },
    { sandbox, link = 'fill', flex=1, },
  },
}



