local ffi = require 'ffi'
local socket = require 'socket'
local u = socket.udp()

ffi.cdef[[
  int WSAGetLastError(void);
]]

local lib = ffi.load("ws2_32")



print(u:setsockname('*', 8899))
print(lib.WSAGetLastError())
print(u:setoption('ip-add-membership', {multiaddr='239.255.1.1', interface='*'}))

print(lib.WSAGetLastError())

--print(u:setoption('ip-add-membership', {multiaddr='127.0.0.1', interface='127.0.0.1'}))
--print(u:getsockname())
while true do
  print(u:receivefrom())
end
