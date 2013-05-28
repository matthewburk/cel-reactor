local _print = print
function print(...)
  _print(...) io.flush()
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
  jit.opt.start(3)
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

return function(tluapath)
  if type(tluapath) == 'table' then
    do
      local path = ''
      for i=#tluapath, 1, -1 do
        local v = tluapath[i]
        path = v .. '/?.lua;' .. v .. '/?/init.lua;' .. path
      end
      package.path = path .. package.path
    end
    do
      local path = ''
      for i=#tluapath, 1, -1 do
        local v = tluapath[i]
        path = v .. '/?_L.dll;' .. v .. '/?.dll;' .. path
      end
      package.cpath = path .. package.cpath
    end
  elseif type(tluapath) == 'string' then
    do
      local path = ''
      local v = tluapath
      path = v .. '/?.lua;' .. v .. '/?/init.lua;' .. path
      package.path = path .. package.path
    end
    do
      local path = ''
      local v = tluapath
      path = v .. '/?_L.dll;' .. v .. '/?.dll;' .. path
      package.cpath = path .. package.cpath
    end
  end

  dprint('package.path', (string.gsub('\n  '..package.path, ';', '\n  ')))
  dprint('package.cpath', (string.gsub('\n  '..package.cpath, ';', '\n  ')), '\n')
end
