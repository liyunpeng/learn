#include <iostream>
#include "b.h"
using namespace std;
int b::f()
{
	this->privatea = 1;
	std::cout << "f \n" ; 
	return 1;
}
b::b()
{
	std::cout << "create b object. " ;
}
