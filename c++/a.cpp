#include <iostream>
#include "b.h" 
#include "c.h"
namespace namespacea
{
	int a = 10;
}

namespace namespaceb
{
	int a = 11;
}

int main()
{
	std::cout << "in namespacea : a = " << namespacea::a << "\n";
	std::cout << "in namespaceb : a = " << namespaceb::a << "\n" ;
	b *p = new b();
	p->f();

	c *pC = new c();
	pC->f();

	return 1;
}
