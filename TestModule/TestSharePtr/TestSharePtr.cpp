// TestSharePtr.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"

#include <memory>
#include <iostream>
#include <assert.h>
#include <vector>
using namespace std;

struct Good : std::enable_shared_from_this<Good> // note: public inheritance
{
	std::shared_ptr<Good> getptr() {
		return shared_from_this();
	}
};

struct Bad
{
	std::shared_ptr<Bad> getptr() {
		return std::shared_ptr<Bad>(this);
	}
	~Bad() { std::cout << "Bad::~Bad() called\n"; }
};

class shared                                    //一个拥有shared_ptr的类    
{
private:
	shared_ptr<int> p;                          //shared_ptr成员变量    
public:
	shared(shared_ptr<int> p_) :p(p_) {}          //构造函数初始化shared_ptr        
	void print()                                //输出shared_ptr的引用计数和指向的值        
	{
		cout << "count:" << p.use_count()
			<< "v =" << *p << endl;
	}
};
void print_func(shared_ptr<int> p)                //使用shared_ptr作为函数参数    
{
	//同样输出shared_ptr的引用计数和指向的值        
	cout << "count:" << p.use_count()
		<< " v=" << *p << endl;
}

int main()
{
	//// Good: the two shared_ptr's share the same object
	//std::shared_ptr<Good> gp1 = std::make_shared<Good>();
	//std::shared_ptr<Good> gp2 = gp1->getptr();
	//std::cout << "gp2.use_count() = " << gp2.use_count() << '\n';

	//// Bad: shared_from_this is called without having std::shared_ptr owning the caller 
	//try {
	//	Good not_so_good;
	//	std::shared_ptr<Good> gp1 = not_so_good.getptr();
	//}
	//catch (std::bad_weak_ptr& e) {
	//	// undefined behavior (until C++17) and std::bad_weak_ptr thrown (since C++17)
	//	std::cout << e.what() << '\n';
	//}

	//// Bad, each shared_ptr thinks it's the only owner of the object
	//std::shared_ptr<Bad> bp1 = std::make_shared<Bad>();
	//std::shared_ptr<Bad> bp2 = bp1->getptr();
	//std::cout << "bp2.use_count() = " << bp2.use_count() << '\n';


	shared_ptr<int> sp(new int(10));                //一个指向整数的shared_ptr    
	assert(sp.unique());                            //现在shared_ptr是指针的唯一持有者     
	shared_ptr<int> sp2 = sp;                       //第二个shared_ptr,拷贝构造函数     
	assert(sp == sp2 && sp.use_count() == 2 && sp2.use_count()==2);       //两个shared_ptr相等,指向同一个对象,引用计数为2  

	*sp2 = 100;                                     //使用解引用操作符修改被指对象    
	assert(*sp == 100);                             //另一个shared_ptr也同时被修改     
	sp.reset();                                     //停止shared_ptr的使用    
	assert(!sp);

	assert(sp.use_count() == 0);


	shared_ptr<int> p(new int(100));
	shared s1(p), s2(p);                        //构造两个自定义类         
	s1.print();
	s2.print();
	*p = 20;                                    //修改shared_ptr所指的值        
	print_func(p);
	s1.print();


	typedef vector<shared_ptr<int> > vs;    //一个持有shared_ptr的标准容器类型        
	vs v(10);                               //声明一个拥有10个元素的容器，元素被初始化为空指针         
	int i = 0;
	for (vs::iterator pos = v.begin(); pos != v.end(); ++pos)
	{
		(*pos) = make_shared<int>(++i);     //使用工厂函数赋值            
		cout << *(*pos) << ", ";            //输出值        
	}
	cout << endl;
	shared_ptr<int> p1 = v[9];
	*p1 = 100;
	cout << *v[9] << endl;

	
	getchar();
	return 0;
}

