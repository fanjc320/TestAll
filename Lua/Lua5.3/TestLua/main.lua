--called for c++
--require "../test"
--require "../../../TestLua/test_ipairs_lua"
--require "E:\\TestProjs\\test_ipairs_lua.lua"
--dofile ("E:/TestProjs/TestLua/test_ipairs_lua.lua")--用require找不到，为什么


dofile ("E:/TestProjs/TestLua/common.lua")

--这部分内容是不能在c++里使用的，会执行不下去
--[[
require("lfs")
path=lfs.currentdir()
print(path);
--]]
--脚本函数实现打印一个table
function printTable(t, n)
    if "table" ~= type(t) then
        return 0;
    end
    n = n or 0;
    local str_space = "";
    for i = 1, n do
        str_space = str_space.."  ";
    end
    print(str_space.."{");
    for k, v in pairs(t) do
        local str_k_v = str_space.."  ["..tostring(k).."] = ";
        if "table" == type(v) then
            print(str_k_v);
            printTable(v, n + 1);
        else
            str_k_v = str_k_v..tostring(v);
            print(str_k_v);
        end
    end
    print(str_space.."}");
end

global_c_read_val = "test val"
print(global_c_write_val)
global_c_read_array = {5,6.78,"array string"}

print("tst lua--------------------");

--只有在c++中调用，才会执行for
if global_c_write_table then
for k,v in pairs(global_c_write_table) do 
     print("k = ",k," v = ",v)
end
end

if global_c_write_array then
     for i = 1, #global_c_write_array do
         print("v = ", global_c_write_array[i])
     end
 end
 

 if global_c_Matrix then
 print("####global_c_write_Matrix\n");
     for i = 1, #global_c_Matrix do
         print("M v = ", global_c_Matrix[i])
     end
 end
 
 
  if global_c_matrix then
   print("####global_c_matrix\n");
     for i = 1, #global_c_matrix do
         print("m v = ", global_c_matrix[i])
     end
 end
 
 
 print(" ------------\n");
 if global_c_Matrix then
 print("global_c_Matrix------------\n");
 for_func(pairs_func, global_c_Matrix, print)
for_func(ipairs_func, global_c_Matrix, print) 
end
 print(" npc------------\n");
--print_r(global_c_Matrix);
--print_r(g_npcPos);
--PrintTable(g_npcPos);
--print_r(g_npcPos1);
--PrintTable(g_npcPos1);

