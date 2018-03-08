
-----------------------------------------------------------------
function print_r ( t )  
    local print_r_cache={}
    local function sub_print_r(t,indent)
        if (print_r_cache[tostring(t)]) then
            print(indent.."*"..tostring(t))
        else
            print_r_cache[tostring(t)]=true
            if (type(t)=="table") then
                for pos,val in pairs(t) do
                    if (type(val)=="table") then
                        print(indent.."["..pos.."] => "..tostring(t).." {")
                        sub_print_r(val,indent..string.rep(" ",string.len(pos)+8))
                        print(indent..string.rep(" ",string.len(pos)+6).."}")
                    elseif (type(val)=="string") then
                        print(indent.."["..pos..'] => "'..val..'"')
                    else
                        print(indent.."["..pos.."] => "..tostring(val))
                    end
                end
            else
                print(indent..tostring(t))
            end
        end
    end
    if (type(t)=="table") then
        print(tostring(t).." {")
        sub_print_r(t,"  ")
        print("}")
    else
        sub_print_r(t,"  ")
    end
    print()
end

----------------------------------------------------------------
key = ""
function PrintTable(table , level)
  level = level or 1
  local indent = ""
  for i = 1, level do
    indent = indent.."  "
  end

  if key ~= "" then
    print(indent..key.." ".."=".." ".."{")
  else
    print(indent .. "{")
  end

  key = ""
  for k,v in pairs(table) do
     if type(v) == "table" then
        key = k
        PrintTable(v, level + 1)
     else
        local content = string.format("%s%s = %s", indent .. "  ",tostring(k), tostring(v))
      print(content)  
      end
  end
  print(indent .. "}")

end
----------------------------------------------------------------





-- 实现 pairs ipairs for 三个函数
 function ipairs_next_func(tab, key)
	key = key + 1
	value = tab[key]
	if value then
		return key, value
	end
end
 function ipairs_func(tab)
	return ipairs_next_func, tab, 0
end

 function pairs_next_func(tab, key)
	key = next(tab, key)
	value = tab[key]
	if value then
		return key, value
	end
end
 function pairs_func(tab, key)
	return pairs_next_func, tab, nil
end
 function for_func(iter_func, test_table, user_func)
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

----------testSplit-----------;
print("\n----------testSplit-----------");
function lua_string_split(str, split_char)
	local sub_str_tab = {};
	for mu_id in string.gmatch(str, "(%d+)"..split_char .."*") do
	print("mu_id:"..mu_id);
		table.insert(sub_str_tab, mu_id)
	end
	return sub_str_tab;
end

function testSplit()
	local str0 = "2|5";
	local params = lua_string_split("3|5",'|');
	--local params = lua_string_split(str0,'|');
	local str = "";
	print_r(params);
	if params then
		for k,v in ipairs(params) do
			print("\n ######## :"..v);
			if v=="1" then str=str.."周一、" end
			if v=="2" then str=str.."周二、" end
			if v=="3" then str=str.."周三、" end
			if v=="4" then str=str.."周四、" end
			if v=="5" then str=str.."周五、" end
			if v=="6" then str=str.."周六、" end
			if v=="7" then str=str.."周七、" end
		end
	print("\n str :"..str);
	else
		print("\n params is nill \n");
	end
	
	return str;
end

testSplit();