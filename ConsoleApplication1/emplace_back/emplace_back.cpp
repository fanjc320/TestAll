// emplace_back.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include <iostream>
#include <vector>
#include<string>
using namespace std;
class CText {
private:
	string str;
public:
	CText(string s):str(s) {
	}
	void show()const {
		cout << str << endl;
	}

};

struct President
{
	std::string name;
	std::string country;
	int year;

	President(std::string p_name, std::string p_country, int p_year)
		: name(std::move(p_name)), country(std::move(p_country)), year(p_year)
	{
		std::cout << "I am being constructed.\n";
	}
	President(const President& other)
		: name(std::move(other.name)), country(std::move(other.country)), year(other.year)
	{
		std::cout << "I am being copy constructed.\n";
	}
	President(President&& other)
		: name(std::move(other.name)), country(std::move(other.country)), year(other.year)
	{
		std::cout << "I am being moved.\n";
	}
	President& operator=(const President& other) = default;
};


int main()
{
	vector<CText> vi;
	//This new element is constructed in place using args as the arguments for its constructor.
	//A similar member function exists, push_back, which either copies or moves an existing object into the container.
	vi.emplace_back("hey");
	vi.front().show();
	//vi.push_back("girl");//错误
	vi.push_back(CText("girl"));
	vi.back().show();

	std::vector<President> elections;
	std::cout << "emplace_back:\n";
	elections.emplace_back("Nelson Mandela", "South Africa", 1994); //没有类的创建  

	std::vector<President> reElections;
	std::cout << "\npush_back:\n";
	reElections.push_back(President("Franklin Delano Roosevelt", "the USA", 1936));

	std::cout << "\nContents:\n";
	for (President const& president : elections) {
		std::cout << president.name << " was elected president of "
			<< president.country << " in " << president.year << ".\n";
	}
	for (President const& president : reElections) {
		std::cout << president.name << " was re-elected president of "
			<< president.country << " in " << president.year << ".\n";
	}


	getchar();
	return 0;
}

