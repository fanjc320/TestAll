--called for c++

global_c_read_val = "test val"
print(global_c_write_val)
global_c_read_array = {5,6.78,"array string"}

print("tst lua");

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

