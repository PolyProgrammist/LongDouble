#include <iostream>
#include <cstdio>
#include "bint.h"
#include <time.h>
using namespace std;
#define STARTRAND time(NULL)
#define TESTS 100
#define OP %
void testing()
{
	srand(STARTRAND);
	bint l1, l2, lres;
	int d1, d2, dres;
	freopen("testResult.txt", "w", stdout);
	vector <bint> wrong[2];
	for (int i = 0; i < TESTS; i++)
	{
		d1 = rand();		d2 = rand();
		l1 = d1;			l2 = d2;		
		dres = d1 OP d2;     lres = l1 OP l2;
		printf("\td1 = %d\t\td2 = %d\t\t\tdres = %d\t\t\tlres = ", d1, d2, dres); cout << lres;
		if (!(lres == dres))
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