#include <iostream>
#include <cstdio>
#include "Ldub_tests.h"
using namespace std;
int main()
{
	ldub a, b;
	for (int i = 0; i < 100; i++)
	{
		cin >> a >> b;
		cout << a/b << endl;
	}
}