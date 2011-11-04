local cel = require 'cel'

require 'cel.textbutton'

return function(_ENV)
  setfenv(1, _ENV)

  local face = cel.getface('textbutton')

  face.textcolor = cel.color.encodef(.8, .8, .8)
  face.fillcolor = cel.color.encodef(.2, .2, .2)
  face.linecolor = cel.color.encodef(.4, .4, .4)
  face.linewidth = 1

  face.layout = {
    wrap = 'line',
    justification = 'center',
    padding = {
      fitx = 'bbox',
      l = function(w, h, font) return font.ascent * .5 end, --TODO need font em
      t = function(w, h, font) return h*.35 end,
    },
  }

  function face.draw(f, t)
    if f.fillcolor then
      cairo.cel_set_source_rgba(cr, f.fillcolor)
      cairo.cel_roundrect(cr, 0, 0, t.w, t.h, f.radius)
      cairo.fill(cr)
    end

    if f.textcolor and t.text then
      cairo.cel_set_source_rgba(cr, f.textcolor)
      for i, line in ipairs(t.lines) do
        if string.sub(t.text, line.j, line.j) ~= '\n' then
        --uncomment this optimization later
        --if t.y + line.y < t.clip.b  and t.y + line.y + line.h > t.clip.t then
          cairo.cel_show_text(cr, t.font, line.penx, line.peny, t.text, line.i, line.j)
        --end
        elseif line.i < line.j then
          cairo.cel_show_text(cr, t.font, line.penx, line.peny, t.text, line.i, line.j-1)
        end
      end
    end

    if f.linewidth and f.linecolor then
      cairo.set_line_width(cr, f.linewidth)
      cairo.cel_set_source_rgba(cr, f.linecolor)
      cairo.cel_roundrect(cr, 0, 0, t.w, t.h, f.radius)
      cairo.stroke(cr)
    end

    return drawlinks(t)
  end

  do
    face['%pressed'] = face:new {
      fillcolor = cel.color.tint(.5, face.fillcolor),
      linecolor = cel.color.encodef(0, 1, 1),
    }

    face['%mousefocusin'] = face:new {
      fillcolor = cel.color.tint(.5, face.fillcolor),
      linecolor = cel.color.encodef(0, 1, 1),
    }
    
    do
      local face = face['%mousefocusin']

      face['%pressed'] = face:new {
        textcolor = cel.color.encodef(.2, .2, .2),
        fillcolor = cel.color.encodef(0, .8, .8),
        linecolor = cel.color.encodef(0, 1, 1),
        linewidth = 2,
      }
    end
  end

  function face.select(face, t)
    if t.mousefocusin then
      face = face['%mousefocusin'] or face
      if t.pressed then
        face = face['%pressed'] or face
      end
    elseif t.pressed then
      face = face['%pressed'] or face
    end
    return face
  end
end


