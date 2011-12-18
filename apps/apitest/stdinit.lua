return function(luapath)
  for i, v in ipairs(luapath) do
    package.path = v .. '/?.lua;' .. v .. '/?/init.lua;' .. package.path
  end

  if not dprint then
    local print = print
    function dprint(...) print(...) io.flush() end
  end

  if not dprintf then
    local dprint = dprint
    function dprintf(format, ...) dprint(string.format(format, ...)) end
  end

  if jit then
    dprint('jit', jit.status())
    jit.opt.start('maxside=10', 'hotloop=5', 'loopunroll=32', 'maxsnap=500', 'tryside=5')
  else
    dprint('no jit :(')
  end

  do --string interpolation via % operator 
    local function dostring(w, t)
      local s = 'setfenv(1, ...); return ' .. w
      local f = assert(loadstring(s))
      local ok, r = pcall(f, t)
      if ok then
        return r;
      end
    end

    local function psub(p, t)
      local w = p:sub(3, -2)
      return t[w] or dostring(w, t) or p
    end

    getmetatable('').__mod = function(s, t)
      return (s:gsub('($%b{})', function(p) return tostring(psub(p, t)) end))
    end
  end
end
