tb = {};
tb[5] = 3;
tb[6]=2;


print(""..tb[5]);

print(""..tb[6]);

local a = tb[7];
local b = tb[1];

if a == nil then
print("a==nil");
end

if not b then
print("b==nil");
end;
--------------------------------------------------------
print("-----------------------------------------");
tbtest = {  
    [1] = 1,  
    [2] = 2,  
    [3] = 3,  
    [4] = 4,  
	["a"] = 6,  
	["b"] = 7, 
} 
 
for key, value in pairs(tbtest) do  
    print("key:",key,"value:",value)
end 
print("-----------------------------------------");
--我认为输出应该是1，2，3，4，实际上的输出是1，2，4，3。我因为这个造成了一个bug，这是后话。
--也就是说for k,v in pairs(tbtest) do 这样的遍历顺序并非是tbtest中table的排列顺序，而是根据tbtest中key的hash值排列的顺序来遍历的

--当然，同时lua也提供了按照key的大小顺序来遍历的，注意，是大小顺序，仍然不是key定义的顺序，这种遍历方式就是for k,v in ipairs(tbtest) do。
--for k,v in ipairs(tbtest) do 这样的循环必须要求tbtest中的key为顺序的，而且必须是从1开始，ipairs只会从1开始按连续的key顺序遍历到key不连续为止。

tbtest = {  
[1] = 1,  
[2] = 2,  
[3] = 3,  
[5] = 5,  
["a"] = 6,  
["b"] = 7, 
} 
 
for k,v in ipairs(tbtest) do  
print("K:",k,"V:",v)  
end 
print("-----------------------------------------");

tbtest = {  
tbaaa = {  
[1] = 1,  
[2] = 2,  
[3] = 3,  
},  
["a"] = 4,  
["b"] = 5,  
} 
for k, v in pairs(tbtest) do  
print("k:",k,"v:" ,v)  
end 
print("-----------------------------------------");
--其实在table中定义一个table，这个table的名字就是key，对应的内容其实是table的地址。
-----------------------------------------------------------------

ta = {1,2,a=nil,b=4,"d",nil,5}
--ta = {[1]=3,[2]=5,nil,nil}--第一个nil将[1]赋值为nil，第二个nil将[2]赋值为nil，所以输出空
--ta = {[2]=3,[3]=5,30,50}--输出1,30;2,50;3,50有[]，值会被覆盖
--ta = {1,2,3,nil,nil}--输出1,2,3,没有[]，值并不会被覆盖
for i,v in pairs(ta) do
	 print("i ",i,"v ",v)
end
print("-----------------------------------------");
 for i,v in ipairs(ta) do
     print("i:",i,"v:",v)
end
print("-----------------------------------------");
a={"Hello","World";a=1,b=2,z=3,x=10,y=20;"Good","Bye"}  
--fjc:ipairs遇到[1]=nil直接跳出
for i, v in ipairs(a) do  
    print(v)  
end 
print("-----------------------------------------");
for i, v in pairs(a) do  
    print(v)  
end 
print("-----------------------------------------");

if false==0 then
print("fasle==0",false);
else
print("false~=0",false);
end

function callf(str)
print("call ok "..str);
end

callf "fjc"

print("-----------------------------------------");


