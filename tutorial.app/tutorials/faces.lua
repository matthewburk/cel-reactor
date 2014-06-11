--Cel does not have rendering capabilities, it is the applications job
--perform all rendering.  Cel provides a description of itself
--to be used for rendering.  When a cel is created it is assigned a face, the
--face controls how a cel looks.  This tutorial will show how to select 
--and create faces.  

local cel = require 'cel'

return function(root)
  pause()
  --A cel is assigned a face when it is created.
  
  --To get a face use cel.getface('<metacel>') where <metacel> is the metacel
  --the face will render.
  do
    --Here we get the face for the cel metacel.
    --Note that just as all cels inherit from the 'cel' metacel, all faces
    --inherit from the 'cel' face, and any properties in the cel face are 
    --present in all faces.
    local face = cel.getface('cel')
    print(face, 'all faces inherit from this face')
  end
  pause()
  do
    --Here we get the face for the label metacel.  All labels will use this face
    --or a face that inherits from it.
    local face = cel.getface('label')
    print(face, 'label')
  end
  pause()

  --When a new metacel is created a face is created 
  --(if it does not alreay exist) for that metacel, with the same name as the
  --metacel.  These become the default face for a cel created from the metacel,
  --and so are referred to as metafaces.

  --A face is shared by cel and the renderer.  A face can be used to control
  --a cel's layout, the font it uses, and presentation related behavior such as
  --animation and hit testing.
  --These entries in the face are reserved for use by Cel:
  --  font - this should be a font returned from cel.loadfont()
  --  touch - a function to do hit testing
  --  layout - a table defining various layout parameters, varies by metacel.
  --  flows - a table with named flow functions, names are defined by metacel.

  --For this tutorial demo a simple renderer was created that will fill in the
  --cel using the color in face.color, and stroke the cel rectangle using
  --the color in face.bordercolor.  
  --These properties are not a part of cel, they are loaded into
  --the face by the renderer, and have no meaning to cel.  One could use images
  --or shaders to render a cel, and the face is a context for the renderer to
  --store any information it needs.
  pause()
 
  --Lets take a look at the face.
  do
    for k, v in pairs(cel.getface('cel')) do
      print('face['..tostring(k)..']', v)
    end
  end
  --Notice the face.cairodraw function. The tutorial renderer looks for a draw
  --function on a face and calls it, we will supply our own draw function later.
  pause()

  --Next we will create a new face. 
  --A new face can be created from an existing face and will inherit its
  --properties.
  do
    local face = cel.getface('cel'):new()

    for k, v in pairs(face) do
      print('newface['..tostring(k)..']', v)
    end
    --This face only has an __index entry which points to the face that created
    --it. (A face is its own metatable).  
    pause()

    --Since our face inherted directly from the 'cel' metaface, it can be used
    --for any cel.
    --We can create a new cel with this face and by passing the face in the 
    --new function.
    local zed = cel.new(100, 200)
    local zoe = cel.new(100, 200, face)

    --A cels' face can be accessed through its face property.
    print('zed.face', zed.face) 
    print('zoe.face', zoe.face) 
    pause()

    --Becuase no face was passed to zed, it will use the metaface corresponding to
    --its metacel. Passing in the metaface produces the same result.  
    zed = cel.new(100, 200, cel.getface('cel'))
    print('zed.face', zed.face)
    pause()

    --Zed and zoe will look the same, since we havent changed anything on the new face. 
    --Change the new face so that it fills in red.
    face.color = cel.color.rgb(1, 0, 0)
    for k, v in pairs(face) do
      print('newface['..tostring(k)..']', v)
    end
    pause()

    --When zed and zoe are linked to root, zed is not visible, becuase the cel metaface doesn't 
    --draw anything by default.
    local row = cel.row {
      zed, zoe,
    }:link(root, 'center')
    pause()

    --Make zed visible by giving it a face that draws something.
    zed:setface(zoe.face)
    pause()
  end

  --The purpose of a face is to aid in decoupling rendering from gui logic. It
  --is useful to have a highly cohesive renderer, and it makes sense to 
  --define all the faces for you application in the renderer.  To enable this
  --a face can be registered with Cel by name.

  --face:new can be called with a table which will be the face, in which case
  --new just takes care of making inheritance works.
  cel.getface('label'):new {      
    --The draw function for a label sets the color to textcolor before drawing
    --the text.
    textcolor = cel.color.rgb(0, 1, 1), 
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
end
