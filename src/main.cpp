#include <iostream>
#include <stdlib.h>
#include <time.h>
#include "tests.h"

using namespace std;

int main(int argc, char *argv[])
{
	srand(time(NULL));

	Tests tests;
	tests.runAllTests();

	return 0;
}
