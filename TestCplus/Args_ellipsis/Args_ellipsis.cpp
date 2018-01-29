// Args_ellipsis.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include <iostream>
#include <unordered_map>
using namespace std;

//递归终止函数
void print() {
	cout << "empty" << endl;
}
//展开函数
template <class T, class ...Args>
void print(T head, Args... rest)
{
	cout << "parameter " << head << endl;
	print(rest...);
}

//上例会输出每一个参数，直到为空时输出empty。展开参数包的函数有两个，一个是递归函数，另外一个是递归终止函数，参数包Args...在展开的过程中递归调用自己，每调用一次参数包中的参数就会少一个，直到所有的参数都展开为止，当没有参数时，则调用非模板函数print终止递归过程。
//
//递归调用的过程是这样的 :
//
//print(1, 2, 3, 4); print(2, 3, 4); print(3, 4); print(4); print();
//上面的递归终止函数还可以写成这样：
//
//template <class T>void print(T t) { cout << t << endl; }
//修改递归终止函数后，上例中的调用过程是这样的：
//
//print(1, 2, 3, 4); print(2, 3, 4); print(3, 4); print(4);
//当参数包展开到最后一个参数时递归为止。

template<typename T>T
sum(T t) { return t; }
template<typename T, typename ... Types>T
sum(T first, Types ... rest)
{
	return first + sum<T>(rest...);
}

template <class T>void printarg(T t)
{
	cout << t << endl;
}
template <class ...Args>
void expand(Args... args)
{
	int arr[] = {
		(printarg(args), 0)...
	};
}
//expand函数中的逗号表达式：(printarg(args), 0)，也是按照这个执行顺序，先执行printarg(args)，再得到逗号表达式的结果0。同时还用到了C++11的另外一个特性——初始化列表，通过初始化列表来初始化一个变长数组, { (printarg(args), 0)... }将会展开成((printarg(arg1), 0), (printarg(arg2), 0), (printarg(arg3), 0), etc...)，最终会创建一个元素值都为0的数组int arr[sizeof...(Args)]。由于是逗号表达式，在创建数组的过程中会先执行逗号表达式前面的部分printarg(args)打印出参数，也就是说在构造int数组的过程中就将参数包展开了，这个数组的目的纯粹是为了在数组构造的过程展开参数包。我们可以把上面的例子再进一步改进一下，将函数作为参数，就可以支持lambda表达式了，从而可以少写一个递归终止函数了，具体代码如下：

template<class F, class... Args>
void expand1(const F& f, Args&&...args)
{  //这里用到了完美转发，关于完美转发，读者可以参考笔者在上一期程序员中的文章《通过4行代码看右值引用》  
	initializer_list<int>
	{
		(f(std::forward< Args>(args)), 0)...
	};
}

int main()
{
	print(1, 2, 3, 4);
	sum(1, 2, 3, 4); //10
	expand(1, 2, 3, 4);

	expand1([](int i) {cout << i << endl; }, 10, 20, 30);
	//上面的例子将打印出每个参数，这里如果再使用C++14的新特性泛型lambda表达式的话，可以写更泛化的lambda表达式了：
	expand1([](auto i) {cout << i << endl; }, 11, 12.0, "test");


	getchar();
    return 0;
}

