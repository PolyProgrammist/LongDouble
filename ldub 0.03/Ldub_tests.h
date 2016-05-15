#include <iostream>
#include <cstdio>
#include <ctime>
#include "ldub.h"
using namespace std;
#define STARTRAND time(NULL)
#define TESTS 1000
#define OP /
#define REAL 0.0000001
double suprand(void)
{
	return ((double)rand() + rand()) / rand() / 100 * rand();
}
void testing_D()
{
	srand(STARTRAND);
	ldub l1, l2, lres;
	double d1, d2, dres;
	freopen("testResult.txt", "w", stdout);
	vector <ldub> wrong[2];
	for (int i = 0; i < TESTS; i++)
	{
		d1 = suprand();		d2 = suprand();
		l1 = d1;			l2 = d2;
		dres = d1 OP d2;     lres = l1 OP l2;
		printf("\td1 = %.10lf\t\td2 = %.10lf\t\t\tdres = %.14lf\t\t\tlres = ", d1, d2, dres); cout << lres;
		if (abs(lres - dres) > REAL)
		{
			wrong[0].push_back(dres);
			wrong[1].push_back(lres);
			printf("\t\tWRONG!WRONG!WRONG!\n");
		}
		else
			printf("\t\tok\n");
	}
	printf("wrong:\n");
	for (int i = 0; i < wrong[0].size(); i++)
		cout << " d = " << wrong[0][i] << "\tl = " << wrong[1][i] << endl;
	fclose(stdout);
}