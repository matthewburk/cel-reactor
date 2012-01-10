--Cel does not have rendering capabilities, it is the applications job
--perform all rendering.  Cel provides a description of itself
--to be used for rendering.  When a cel is created it is assigned a face, the
--face controls how a cel looks.  This tutorial will show how to select 
--and create faces.  

local cel = require 'cel'

return function(root)
  pause()
  
  print('hello world')
  pause()
  --The first thing to understand is that a cel always has a face, A cel is 
  --assigned a face when it is created.
  --
  --To get a face use cel.getface('metacel')
  --Here we get the face for the cel metacel.  Just as all cels inherit from
  --the 'cel' metacel, all faces inherit from the 'cel' face.
  local face = cel.getface('cel')
  print(face)
  print('hello world')
  --Here we get the face for the label metacel.  All labels will use this face
  --or a face that inherits from it.
  --local labelface = cel.getface('label')
  --print(labelface)

  --face and labelface are special faces becuase they are bound to the metacel.
  --When a new metacel is created a face is created 
  --(if it does not alreay exist) for that metacel, with the same name as the
  --metacel.  These become the default face for a cel created from the metacel,
  --and so are referred to as metafaces.

  --A cel face is shared by Cel and the renderer.  A face can be used to control
  --a cel's layout, the font it uses, and presentation related behavior such as
  --animation and hit testing.
  --These entries in the face are reserved for use by Cel:
  --  font - this should be a font returned from cel.loadfont()
  --  touch - a function to do hit testing
  --  layout - a table defining various layout parameters, varies by metacel.
  --  flows - a table with named flow functions, names are defined by metacel.

  --For this tutorial demo a simple renderer was created that will fill in the
  --cel using the color in face.fillcolor, and stroke the cel rectangle using
  --the color in face.linecolor.  If no color is specified then the fill/stroke
  --is not done.  These properties are not a part of Cel, they are loaded into
  --the face by the renderer, and have no meaning to Cel.  One could use images
  --or shaders to render a cel, and the face is a context for the renderer to
  --store any information it needs.
  
  --Lets take a look at the face.
  for k, v in pairs(face) do
    io.write('face['..tostring(k)..']', tostring(v), '\n') io.flush()
    --print('face['..tostring(k)..']', tostring(v))
  end
  pause()

  --[==[
  --Notice the face.draw function.  The tutorial renderer looks for a draw
  --function on a face and calls it, we will supply our own draw function later.
  --
  --Next we will create a new face.  A new face
  --can be created from an existing face and will inherit its properties.
  local customface = face:new()

  --Lets take a look again.
  print('-----customface-----')
  for k, v in pairs(customface) do
    print('customface['..tostring(k)..']', v)
  end
  pause()

  --customface only has an __index entry which points to the face that created
  --it. (A face is its own metatable).  

  --Since our face inherted from the 'cel' metaface it can be used for any cels.
  --We can create a new cel with this face and by passing the face in the new 
  --function.
  local zed = cel.new(100, 200)
  local zoe = cel.new(100, 200, customface)

  print('zed.face', zed.face) 
  print('zoe.face', zoe.face) 
  pause()

  --Becuase no face was passed to zed, it will use the metaface corresponding to
  --its metacel. Passing in the metaface produces the same result.  
  zed = cel.new(100, 200, cel.getface('cel'))
  print('zed.face', zed.face)
  pause()


  --Since we havent changed anything on customface zed and zoe will look the
  --same.
  local row = cel.row {
    zed, zoe,
  }:link(root, 'center')
  pause()

  --Actually you can't see them becuase the draw function we are using looks
  --for fillcolor and linecolor on the face, if they are not present(false) then
  --nothing is drawn for the face.  Our renderer is looking for a 4 byte string
  --for any color, cel.color.encodef() creates a color as a 4 byte string.   
  --Here we give our customface some colors so we can see it.
  customface.fillcolor = cel.color.encodef(1, 0, 0)
  customface.linecolor = cel.color.encodef(1, 1, 1)
  pause()

  --zed is still invisible.  We can color him up too, but that will affect all
  --faces.  THIS WILL BE UGLY.
  face.fillcolor = cel.color.encodef(0, 0, 1)
  face.linecolor = cel.color.encodef(1, 1, 1)
  pause()

  --Change it back
  face.fillcolor = false
  face.linecolor = false
  pause()

  --We cannot change the a cel's face once it is set. This is not supported
  --becuase it would make creating new metacels much more difficult.  For the
  --same reason any changes made to a cel's face are not tracked by Cel. Also
  --each face would have to keep a reference to all the cels using that face.
  --It is way too much overhead for what is basically a gimmick.  It is overall
  --more efficient and simpler to just create a new cel.  Changing the linecolor
  --and fillcolor works becuase they are used by the renderer, which looks at
  --the values every time the cel is drawn.  
  
  --Just keep in mind that this tutorial is to help you understand faces.
  --Changing the entries in a face is not something you would normally do after
  --it has been intialized.  Later in this tutorial I will show the right way to
  --use faces.  For now we will continue down this path of crazy :)
  
  --Lets get zed out of there and make a new zed we can see.
  zed:unlink()
  
  --Make a new face that inherits from customface
  local customface2 = customface:new()
  zed = cel.new(100, 200, customface2):link(row)
  pause()

  --Change zed's color
  customface2.fillcolor = cel.color.encodef(0, 0, 1)
  pause()

  --Ok now we will finally draw our new face differently by redefining the
  --draw function.  face is the face of the cel being drawn, t is the
  --description of the cel being drawn.  (The description actually has the face
  --at t.face, if you want to know why we don't use that look at how
  --face.select is used in the tutorial renderer, in short face and t.face 
  --won't always match)
  function customface.draw(face, t)
    --draw a circle
    local radius = math.min(t.w, t.h)/2
    local cx = t.w/2
    local cy = t.h/2

    if face.fillcolor then
      love.graphics.setColor(string.byte(face.fillcolor, 1, 4))
      love.graphics.circle('fill', cx, cy, radius, radius*2)
    end
    if face.linecolor then
      love.graphics.setColor(string.byte(face.linecolor, 1, 4))
      love.graphics.circle('line', cx, cy, radius, radius*2)
    end
  end
  pause()

  --We are switching modes here, you should understand at this point what a
  --face is, and how a cel is assigned a face.  When creating your own renderer
  --you are free to choose what to put in the face and how to render a cel.
  --Now on to intended/right way to use faces, we won't change the face after
  --it is initialized anymore.

  --The purpose of a face is to aid in decoupling rendering from gui logic. It
  --is useful to have a highly cohesive renderer, and it makes sense to 
  --define all the faces for you application in the renderer.  To enable this
  --a face can be registered with Cel by name.

  --face:new can be called with a table which will be the face, in which case
  --new just takes care of making inheritance works.
  cel.getface('label'):new {      
    --The draw function for a label sets the color to textcolor before drawing
    --the text.
    textcolor = cel.color.encodef(0, 1, 1), 
  }:register('@cyan')
  --The register function allows us to lookup the face by its registered 
  --name.  My convention is to use @ as the first char for face names.  The
  --name can be any lua type however.
  pause()

  --We can get a registerd face by passing the name it was registered under
  --as the second parameter to cel.getface().
  print('label@cyan', cel.getface('label', '@cyan'))

  --Each metaface has its own registry, so '@cyan' is not the 'cel' metaface
  --registry.
  print('cel@cyan', cel.getface('cel', '@cyan'))
  pause()

  --Now you can use the registerd name instead of the face when creting a cel.
  zed = cel.label.new('zed', '@cyan'):link(row)
  pause()

  --If the name does not exist, thats ok, the metaface will be used.
  zoe = cel.textbutton.new('zoe', '@cyan'):link(row)
  pause()

  --This technique allows you to use semantic names, like '@closebutton' or
  --'@damagetext', and then create different faces for them or let them
  --default to the metaface.
  -- 
  --Also note that a face can be registered under multiple names if you wish.
  pause()

  --Often you want to have labels with different fonts or different colored
  --text, this means the labels will have different faces.
  --Lets create another face that uses a different font.
  cel.getface('label', '@cyan'):new {
    font = cel.loadfont('serif', 32)
  }:register('@fancy')

  --since we inherit from '@cyan' the textcolor is still cyan
  zoe = cel.label.new('fancy zoe', '@fancy'):link(row)
  pause()

  --One more thing about metafaces.  If no name is given you ALWAYS get a face,
  --which is the metaface for the the metacel with the corresponding name.
  face = cel.getface('thisceltypedoesnotexist')

  --This face inherits from the default 'cel' face, but it can never be used
  --until a metacel called 'thisceltypedoesnotexist' is created.
  print('thisceltypedoesnotexist', face)

  --This means that a face can be created for a metacel that does not yet 
  --exist.  Creating a new metacel is fairly easy as well, and will be covered
  --in another tutorial.
  pause()
  --]==]
end
