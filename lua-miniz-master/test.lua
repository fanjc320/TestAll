local miniz = require "miniz"
--local fs = require "path.fs"
local fs = require "lfs"
--local fs = require "E:/TestProjs/lua-miniz-master/lminiz.c"

local za = miniz.zip_write_file "lua-miniz.zip"
za:add_file "lminiz.c"
za:add_file "miniz.c"
za:add_file "lua.exe"
za:add_file "lua53.dll"
za:add_file "miniz.dll"
za:add_file "zlib.dll"
za:add_file "path.dll"
za:add_file "test.lua"
za:add_file "xlsx.lua"
za:add_file "test_flate.lua"
za:add_file "test_xlsx.lua"
print("----------------")
for file in fs.dir("xlsxwriter") do
print("file "..file);
   za:add_file("xlsxwriter/"..file)
end
print("----------------")
za:finalize()
za:close()

--local za = assert(miniz.zip_read_file "lua-miniz.zip")
local za = miniz.zip_read_file "lua-miniz.zip"
print(za)
print(#za)
for _, file in ipairs(za) do
--for key, file in ipairs(za) do
--for _, file in pairs(za) do
   print(file)
end
print(za:extract "test.lua")
za:close()

