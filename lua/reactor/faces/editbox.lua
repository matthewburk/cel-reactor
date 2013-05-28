local cel = require 'cel'

cel.getface('cel'):new {
  color = app.colors.themecomplement
}:register('@caret')

local face = cel.getface('editbox')
face.color = cel.color.setalpha(app.colors.white, .2)

do
  local face = cel.getface('editbox.text')
  face.textcolor = app.colors.themetextcolor
  face.selectedtextcolor = app.colors.themecolor
  face.color = false 
  face.bordercolor = false
  face.borderwidth = false 

  face.layout = {
    padding = {
      l=function(w, h, font) return math.floor(font.emadvance/2) end,
      t=function(w, h, font) return font.emheight/2 end,
    },
  }

  function face.cairodraw(_ENV, cr, f, t)
    if f.color then
      cr:set_source_color(_ENV.color)
      cr:rectangle(0, 0, t.w, t.h)
      cr:fill()
    end

    if f.textcolor and t.text then
      cr:set_source_color(_ENV.textcolor)
      
      --TODO lineheight is not exact, this may skip things that should be rendered
      local lineheight = t.font.lineheight
      local ymin = t.clip.t - _ENV.Y - lineheight
      local ymax = t.clip.b - _ENV.Y + lineheight

      for i, line in ipairs(t.lines) do
        if line.peny > ymin then
          if line.peny > ymax then
            break
          else
            cr:drawstring(t.font, line.penx, line.peny, line.text)
          end
        end
      end

      if t.selectionx then
        cr:save()
        cr:rectangle(t.selectionx, t.selectiony, t.selectionw, t.selectionh)
        cr:clip()
        cr:paint()
        cr:set_source_color(f.selectedtextcolor)

        for i, line in ipairs(t.lines) do
          if line.peny > ymin then
            if line.peny > ymax then
              break
            else
              cr:drawstring(t.font, line.penx, line.peny, line.text)
            end
          end
        end

        cr:restore()
      end
    end

    if f.borderwidth and f.bordercolor then
      cr:set_line_width(f.borderwidth)
      cr:set_source_color(_ENV.bordercolor)
      cr:rectangle(0, 0, t.w, t.h)
      cr:stroke()
    end

    return _ENV.drawlinks(cr, t)
  end
end




