#include <iostream>
#include <ctime>

#include "functions.h"

using namespace std;

int main()
{
	char a[] = "albe", b[] = "ball";

	sendSerialData(a);
	Sleep(400);
	sendSerialData(b);

	return 0;
}