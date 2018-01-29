// Tuple.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include <tuple>
#include <type_traits>
#include <utility>
#include <iostream>
//tuple是一个固定大小的不同类型值的集合，是泛化的std::pair。和c#中的tuple类似，
//但是比c#中的tuple强大得多。我们也可以把他当做一个通用的结构体来用，不需要创建结构体又获取结构体的特征，
//在某些情况下可以取代结构体使程序更简洁，直观。

//基本用法
//构造一个tuple
//tuple<const char*, int>tp = make_tuple(sendPack, nSendSize); //构造一个tuple
//这个tuple等价于一个结构体
//struct A
//{
//	char* p;
//	int len;
//};
//用tuple<const char*, int>tp就可以不用创建这个结构体了，而作用是一样的，是不是更简洁直观了。


int main()
{
	std::tuple<int, std::string, float> t1(10, "Test",
		3.14);
	int n = 7;
	auto t2 = std::tuple_cat(t1, std::make_pair("Foo",
		"bar"), t1, std::tie(n));
	n = 10;
	print(t2);

	//还有一种方法也可以创建元组，用std::tie，它会创建一个元组的左值引用。

	auto tp = return std::tie(1, "aa", 2);
	//tp的类型实际是：
	std::tuple<int&, string&, int&>
		//再看看如何获取它的值：
		const char* data = tp.get<0>(); //获取第一个值
	int len = tp.get<1>(); //获取第二个值
						   //还有一种方法也可以获取元组的值，通过std::tie解包tuple
	int x, y;
	string a;
	std::tie(x, a, y) = tp;
	//通过tie解包后，tp中三个值会自动赋值给三个变量。
	//解包时，我们如果只想解某个位置的值时，可以用std::ignore占位符来表示不解某个位置的值。比如我们只想解第三个值时：
	std::tie(std::ignore, std::ignore, y) = tp; //只解第三个值了
												//还有一个创建右值的引用元组方法：forward_as_tuple。
	std::map<int, std::string> m;
	m.emplace(std::forward_as_tuple(10, std::string(20, 'a')));
	//它实际上创建了一个类似于std::tuple<int&&, std::string&&>类型的tuple。
	//我们还可以通过tuple_cat连接多个tupe
}

//输出结果：
//(10, Test, 3.14, Foo, bar, 10, Test, 3.14, 10)

//到这里tuple的用法介绍完了，是不是很简单，也很容易使用，相信你使用它之后就离不开它了。
//我前面说过tuple是简约而不简单。它有很多高级的用法。
//它和模板元关系密切, 要介绍它的高级用法的时候，读者需要一定的模板元基础，
//如果你只是把它当一个泛型的pair去使用时，这部分可以不看，如果你想用它高级用法的时候就往下看。让我们要慢慢揭开tuple神秘的面纱。
//tuple的高级用法
//获取tuple中某个位置元素的类型
//通过std::tuple_element获取元素类型。

template<typename Tuple>
void Fun(Tuple& tp)
{
	std::tuple_element<0, Tuple>::type first = std::get<0>
		(mytuple);
	std::tuple_element<1, Tuple>::type second = std::get<1>
		(mytuple);
}

//获取tuple中元素的个数：
tuple t;

int size = std::tuple_size<decltype(t)) > ::value;

//遍历tuple中的每个元素
//因为tuple的参数是变长的，也没有for_each函数，如果我们想遍历tuple中的每个元素，需要自己写代码实现。比如我要打印tuple中的每个元素。

template<class Tuple, std::size_t N>
struct TuplePrinter {
	static void print(const Tuple& t)
	{
		TuplePrinter<Tuple, N - 1>::print(t);
		std::cout << ", " << std::get<N - 1>(t);
	}
};

template<class Tuple>
struct TuplePrinter<Tuple, 1> {
	static void print(const Tuple& t)
	{
		std::cout << std::get<0>(t);
	}
};

template<class... Args>
void PrintTuple(const std::tuple<Args...>& t)
{
	std::cout << "(";
	TuplePrinter<decltype(t), sizeof...(Args)>::print(t);
	std::cout << ")\n";
}

//根据tuple元素值获取其对应的索引位置
namespace detail
{
	template<int I, typename T, typename... Args>
	struct find_index
	{
		static int call(std::tuple<Args...> const& t, T&& val)
		{
			return (std::get<I - 1>(t) == val) ? I - 1 :
				find_index<I - 1, T, Args...>::call(t, std::forward<T>(val));
		}
	};

	template<typename T, typename... Args>
	struct find_index<0, T, Args...>
	{
		static int call(std::tuple<Args...> const& t, T&& val)
		{
			return (std::get<0>(t) == val) ? 0 : -1;
		}
	};
}

template<typename T, typename... Args>
int find_index(std::tuple<Args...> const& t, T&& val)
{
	return detail::find_index<0, sizeof...(Args)-1, T, Args...>::
		call(t, std::forward<T>(val));
}

int main()
{
	std::tuple<int, int, int, int> a(2, 3, 1, 4);
	std::cout << find_index(a, 1) << std::endl; // Prints 2
	std::cout << find_index(a, 2) << std::endl; // Prints 0
	std::cout << find_index(a, 5) << std::endl; // Prints -1 (not found)
}

//展开tuple，并将tuple元素作为函数的参数。这样就可以根据需要对tuple元素进行处理了



template<size_t N>
struct Apply {
	template<typename F, typename T, typename... A>
	static inline auto apply(F && f, T && t, A &&... a)
		-> decltype(Apply<N - 1>::apply(
			::std::forward<F>(f), ::std::forward<T>(t),
			::std::get<N - 1>(::std::forward<T>(t)),
			::std::forward<A>(a)...
		))
	{
		return Apply<N - 1>::apply(::std::forward<F>(f),
			::std::forward<T>(t),
			::std::get<N - 1>(::std::forward<T>(t)),
			::std::forward<A>(a)...
		);
	}
};

template<>
struct Apply<0> {
	template<typename F, typename T, typename... A>
	static inline auto apply(F && f, T &&, A &&... a)
		-> decltype(::std::forward<F>(f)
		(::std::forward<A>(a)...))
	{
		return ::std::forward<F>(f)(::std::forward<A>
			(a)...);
	}
};

template<typename F, typename T>
inline auto apply(F && f, T && t)
-> decltype(Apply< ::std::tuple_size<
	typename ::std::decay<T>::type
>::value>::apply(::std::forward<F>(f),
	::std::forward<T>(t)))
{
	return Apply< ::std::tuple_size<
		typename ::std::decay<T>::type
	>::value>::apply(::std::forward<F>(f),
		::std::forward<T>(t));
}

void one(int i, double d)
{
	std::cout << "function one(" << i << ", " << d <<
		");\n";
}
int two(int i)
{
	std::cout << "function two(" << i << ");\n";
	return i;
}

//测试代码
int main()
{
	std::tuple<int, double> tup(23, 4.5);
	apply(one, tup);

	int d = apply(two, std::make_tuple(2));

	return 0;
}

//看到这里，想必大家对tuple有了一个全面的认识了吧，怎么样，它是简约而不简单吧。
//对模板元不熟悉的童鞋可以不看tuple高级用法部分，不要为看不懂而捉急，没事的，高级部分一般用不到，知道基本用法就够用了。
//tuple和vector比较：
//vector只能容纳同一种类型的数据，tuple可以容纳任意类型的数据；
//vector和variant比较：
//二者都可以容纳不同类型的数据，但是variant的类型个数是固定的，而tuple的类型个数不是固定的，是变长的，更为强大。
