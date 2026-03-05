#include <stdio.h>

namespace FizzGen
{
	_declspec(dllexport) void Print();
}

int main()
{
	FizzGen::Print();
	printf("print test!\n");


	return 0;
}