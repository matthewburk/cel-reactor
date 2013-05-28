--window={title='apitest', w=400, h=400}
local ffi = require 'ffi'
local cel = require 'cel'
local socket = require 'socket'

ffi.cdef[[
int _getpid( void );
]]

local udp = socket.udp()
local multicastip = '239.255.1.1'
local multicastport = 9000
local localip = '127.0.0.1'
local hostname = 'localhost'

local chathistory = cel.listbox.new()

do
  hostname = socket.dns.gethostname()
  localip = socket.dns.toip(hostname)
  dprint('hostname', hostname)
  dprint('ip', localip)
  dprint(ffi.C._getpid())
end

dprint(udp:setsockname(localip, multicastport))
udp:setoption('ip-add-membership', {multiaddr=multicastip, interface='*'})
udp:settimeout(1/1000)
dprint('sockname', udp:getsockname())

local chatinput = cel.editbox.new('hi')

function chatinput:onkeypress(key)
  dprint('chaintinput:onkeypress', key)
  if key == 'enter' then
    cel.text.new(self:gettext())
      :link(chathistory, 'fill.rightmargin', 100)   
      :wrap('width')
  
    chathistory:scrollto(0, math.huge)

    udp:sendto(self:gettext(), multicastip, multicastport)

    self:settext(nil)
    return true
  end
end

app.window.root:addlinks {
  link = 'fill';
  cel.col {
    {link='fill', flex=1, 
      chathistory,
    },
    {link='width', chatinput},
  }
}

chatinput:takefocus()

function app.update(millis)
  while true do
    local msg, ip, port = udp:receivefrom()

    if msg and ip ~= localip then

    elseif msg then
      dprint(msg, ip, port)
    else
      break
    end
  end

  return 100
end
