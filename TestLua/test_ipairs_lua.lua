

-- 实现 pairs ipairs for 三个函数
local function ipairs_next_func(tab, key)
	key = key + 1
	value = tab[key]
	if value then
		return key, value
	end
end
local function ipairs_func(tab)
	return ipairs_next_func, tab, 0
end

local function pairs_next_func(tab, key)
	key = next(tab, key)
	value = tab[key]
	if value then
		return key, value
	end
end
local function pairs_func(tab, key)
	return pairs_next_func, tab, nil
end
local function for_func(iter_func, test_table, user_func)
	local next, var, state = iter_func(test_table)
	while true do
		local k, v = next(var, state)
		if not k then break end	
		state = k
		user_func(k, v)
	end
end

-- 测试一下
local test_table = 
{
	a = 1,
	2,
	x = 'x',
	3,
}

print('ipairs:')
for k, v in ipairs(test_table) do
	print(k,v)
end

print("ipairs_func:")
for_func(ipairs_func, test_table, print)

print('pairs:')
for k, v in pairs(test_table) do
	print(k,v)
end

print("pairs_func:")
for_func(pairs_func, test_table, print)	

--[[
test next function
--]]

print("------------null table----------");
local ta = {

}

print(#ta)
print(next(ta))

print("------------no explit key----------");
local ta = {
--'}' expected (to close '{' at line 71) near '='
--1 = "ma"
       "ma"
}

print(#ta)
print(next(ta))
print(next(ta,nil))
--lua: invalid key to 'next'
--print(next(ta,0))
print(next(ta,1))

print("------------[numb] as key----------");
local ta = {
[1] = "ma"
}

print(#ta)
print(next(ta))
print(next(ta,nil))
--lua: invalid key to 'next'
--print(next(ta,0))
print(next(ta,1))

print("------------rr as key----------");
local ta = {
rr = "ma"
}

print(#ta)
print(ta[rr])
print(ta["rr"])
print(next(ta))
print(next(ta,nil))
print(next(ta,rr))
-- invalid key to 'next'
--print(next(ta,1))

print("------------[rr] as key----------");
local ta = {
-- table index is nil
--[rr] = "ma"
--'}' expected (to close '{' at line 106) near '='
--"rr" = "ma"
}
ta["rr"] = "ma";
print(next(ta,rr))
print(ta[rr])
print(ta["rr"])
print(next(ta,"rr"))
--table index is nil
--ta[rr]="ma";

--[[next (table [, index])
功能：允许程序遍历表中的每一个字段，返回下一索引和该索引的值。
参数：table：要遍历的表
　　　index：要返回的索引的前一索中的号，当index为nil[]时，将返回第一个索引的值，当索引号为最后一个索引或表为空时将返回nil
注：可以用next(t)来检测表是否为空(此函数只能用于以数字索引的表与ipairs相类似)--]]

 --[[关于lua table是否为空的判断
在项目的脚本lua中经常有这样的需求，

1、local a = {}

2、对a进行处理

3、对a是否为空表进行判断

关于对a是否为空表的判断，我发现有些代码如此做：

if a == {} then

这样的结果就是a == {}永远返回false，是一个逻辑错误。因为这里比较的是table a和一个匿名table的内存地址。

也有些代码如此做：

if table.maxn(a) == 0 then

这样做也不保险，除非table的key都是数字，而没有hash部分。

难道真的要遍历table发现有东西就return false跳出才能断定它是否为空吗？这样写至少代码太难看. 

网上小搜了一下，发现原来官方手册里早已经给了答案，那就是靠lua内置的next函数

即如此用：if next(a) == nil then

next其实就是pairs遍历table时用来取下一个内容的函数.

在项目的module中最好封装一下，免得module本地也有next函数

于是封装后判断的lua table是否为空的函数如下：

function table_is_empty(t)

        return _G.next( t ) == nil

end
--]]


--[[
pairs 和 ipairs 区别
--]]

--[[标准库提供了集中迭代器，包括迭代文件每行的(io.lines)，
迭代table元素的(pairs)，迭代数组元素的(ipairs)，迭代字符串中单词的 
(string.gmatch)
LUA手册中对与pairs,ipairs解释如下：

ipairs (t)
Returns three values: an iterator function, the table t, and 0, so that the construction
for i,v in ipairs(t) do body end
will iterate over the pairs (1,t[1]), (2,t[2]), ···, up to the first integer key absent from the table.

pairs (t)
Returns three values: the next function, the table t, and nil, so that the construction
for k,v in pairs(t) do body end
will iterate over all key–value pairs of table t.
See function next for the caveats of modifying the table during its traversal.

这样就可以看出  ipairs以及pairs 的不同。
pairs可以遍历表中所有的key，并且除了迭代器本身以及遍历表本身还可以返回nil;
但是ipairs则不能返回nil,只能返回数字0，如果遇到nil则退出。它只能遍历到表中出现的第一个不是整数的key
--]]

--下面举个例子吧！

local tabFiles = {
[3] = "test2",
[6] = "test3",
[4] = "test1"
}
 
for k, v in ipairs(tabFiles) do
print(k, v)
end
 
 --[[
猜测它的输出结果是什么呢？
 
根据刚才的分析，它在 ipairs(tabFiles) 遍历中，当key=1时候value就是nil，所以直接跳出循环不输出任何值。
 
>lua -e "io.stdout:setvbuf 'no'" "Test.lua"
>Exit code: 0
 
那么，如果是
for k, v in pairs(tabFiles) do
print(k, v)
end
则会输出所有 ：
>lua -e "io.stdout:setvbuf 'no'" "Test.lua" 
3 test2
6 test3
4 test1
>Exit code: 0
现在改变一下表内容，
local tabFiles = {
[1] = "test1",
[6] = "test2",
[4] = "test3"
}
for k, v in ipairs(tabFiles) do
print(k, v)
end
现在的输出结果显而易见就是key=1时的value值test1
 >lua -e "io.stdout:setvbuf 'no'" "Test.lua" 
1 test1
>Exit code: 0 
--[示例1.]--
local tt =
{
    [1] = "test3",
    [4] = "test4",
    [5] = "test5"
}

for i,v in pairs(tt) do        -- 输出 "test4" "test3" "test5"
    print( tt[i] )
end

for i,v in ipairs(tt) do    -- 输出 "test3" k=2时断开
    print( tt[i] )
end





-- [示例2.] --
tbl = {"alpha", "beta", [3] = "uno", ["two"] = "dos"}

for i,v in ipairs(tbl) do    --输出前三个
    print( tbl[i] )
end

for i,v in pairs(tbl) do    --全部输出
    print( tbl[i] )
end
--]]
