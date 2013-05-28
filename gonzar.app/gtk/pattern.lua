local cel = require 'cel'

local face = cel.getface('cel'):new()


function face.cairodraw(_ENV, cr, f, t)
  cr:rectangle(0, 0, t.w, t.h)
  cr:save()
  cr:set_source(f.pattern)
  cr:fill()
  cr:restore()

  return _ENV.drawlinks(cr, t)
end

function face:resize(w, h)
  local surface = cairo.surface.create(w, h)
  local cr = cairo.create(surface)
  
  cr:rectangle(0, 0, w, h)
  cr:scale(w/self.w, h/self.h)
  cr:set_source(self.pattern)
  cr:fill()

  surface:flush()

  self.pattern = cairo.pattern.create_for_surface(surface)
  self.pattern:set_extend('repeat')
  self.w = w
  self.h = h

  cr:destroy()
  surface:destroy()

  return self
end

return function(source)
  local surface = cairo.surface.create_from_png(source)
  local cr = cairo.create(surface)
  
  local pattern = cairo.pattern.create_for_surface(surface)
  pattern:set_extend('repeat')
  local w, h = surface:get_size()

  cr:destroy()
  surface:destroy()

  return face:new {
    pattern=pattern, w=w, h=h,
  }
end
