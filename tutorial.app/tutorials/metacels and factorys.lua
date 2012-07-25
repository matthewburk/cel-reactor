--So far we have only used basic cels. This tutorial will introduce other types
--of cels, that offer more functionality. 
local cel = require 'cel'

return function(root)
  pause()
  --A cel type is defined by a what is called metacel.  A metacel defines the
  --metatable of a cel and creates cels.
  --
  --In Cel metcels are normally hidden behind a factory, when you require 'cel'
  --what you get back is the 'cel' factory.  By convention the factory/module
  --has the same name as the metacel. Lets get another factory.
  local buttonfactory = require 'cel.button'

  --An lets make a button
  local button = buttonfactory.new(100, 100)

  --Since a button is a cel we can link it to another cel.
  button:link(root, 'center')
  pause()

  --As a convenience the cel factory will require sub modules automatically.
  --Here we create a label, cel will require 'cel.label' for us.
  local label = cel.label.new('A label')

  --Make a labeled button, TADA!
  label:link(button, 'center')
  pause()

  --This next trick is for demonstration purposes only, and not how you should
  --actually underline text (the trick only works on fixed width fonts anyways).
  cel.label.new('_______'):link(label)
  pause()

  --cleanup
  button:unlink()
  pause()

  --So putting a label in a button is pretty handy, but scanning the code to see
  --that relationship is not very handy.  For this reason Cel supports a 
  --more declaritive style for creating cels.  Here is how to declare a label.
  local label = cel.label {
    text='Hello',
  }
  pause()

  --The factory cel.label is a functable.  A cel factory can be called as a 
  --function, the factory takes a table as its only parameter, so we can omit
  --the parens.  The cel module is also cel factory, so it can be used the same
  --way to create cels.
  local zed = cel {
    w = 100,
    h = 100,
  }
  pause()

  --The named parameters should be fairly obvious, consult the api documentation
  --for detailed descriptions.  

  --Lets make a labeled button.  Any cels contained in the array part of the
  --table are linked to the cel being constructed.
  local button = cel.button {
    w = 200, h = 200,
    label,
  }

  button:link(root, 'center')
  pause()

  --The obvious problem here is that our label is not centered.  Do over.
  button:unlink()
  pause()

  --To center the label we can specify the linker like this:
  button = cel.button {
    link = 'center',
    w = 200, h = 200,
    label,
  }

  button:link(root)
  pause()

  --This is another variation, with the same result.
  cel.button {
    link = 'center'; w = 200; h = 200;
    cel.label {
      text = 'hello',
    }
  }:link(root, 'right')
  pause()

  --This variation does the same.  When a string is in the array part, a label
  --is created (actually thats what the cel metacel does, most metacels do not
  --override that behavior, but they can).
  cel.button {
    link = 'center'; w = 200; h = 200;
    'hellO',
    '_____',
  }:link(root, 'bottom')

  --This time 2 labels will linked to the button, both using the 'center'
  --linker.
  pause()

  --If you want to control the linker on a per link basis you can do this:
  cel.button {
    link = 'center'; w = 200; h = 200;
    { link = 'left.center'; 'left.center'},
    { link = 'right.center'; 'right.center'},
    { link = 'center.top'; 'center.top'},
    { link = 'center.bottom'; 'center.bottom'},
  }:link(root, 'fill')
  pause()

  --The idea of just putting a label in a button to have a textbutton is nice,
  --but it doesn't always work like you want.
  cel.button {
    w = 100, h = 100,
    'THIS LABEL IS TOO BIG',
  }:link(root, 'center')
  pause()

  --This cannot be resolved with a linker becuase we need to make the button
  --bigger to accomodate the label, and linkers position the link in the host.
  --If you tried to go both ways, you could easily end up in an infinite loop.
  --So you need to measure the label first and then make the button big enough
  --to contain the label.  So a textbutton is a good candidate for a new 
  --metacel that does this for us, so I made one.

  cel.textbutton.new('IS THIS LABEL TOO BIG?'):link(root, 'center')
  pause()

  --Later tutorials will show how to create a new metacel, its more advanced
  --and we still need to cover some basics. Now we will start using labels
  --and buttons and other types of cels in the tutorials.
  pause()
end
