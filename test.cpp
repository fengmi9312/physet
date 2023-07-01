#include<iostream>
#include"physet.h"
using namespace std;

int main()
{
	physet<long double>* test = new physet<long double>;
	test->add(1232.23);
	test->add(12.23);
	test->add(123);
	physet<long double>::const_iterator it = test->begin();
	cout << ((*it)) << endl;
	cout << ((*++it)) << endl;
	cout << ((*++it)) << endl;
	return 0;
}
