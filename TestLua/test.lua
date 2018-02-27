local miniz = require "miniz"
--local fs = require "path.fs"
local fs = require "lfs"
--local fs = require "E:/TestProjs/lua-miniz-master/lminiz.c"


local za = assert(miniz.zip_read_file "lua-miniz.zip")
--local za = miniz.zip_read_file "lua-miniz.zip"
print(za)
print(#za)
for _, file in ipairs(za) do
--for key, file in ipairs(za) do
--for _, file in pairs(za) do
   print(file)
end
print(za:extract "test.lua")
za:close()

