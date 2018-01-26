//#include "createdll.h"
#include "mydll.h"
#include <iostream>

using namespace std;

int main()
{
	Cmydll mydll;

	cout <<" nmydll "<< nmydll <<" fnmydll "<< fnmydll() << " dlladd " << mydll.dllAdd(1,2) << endl;

	int i;
	cin >> i;

	return 0;
}