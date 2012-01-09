#include <iostream>
#include "b.h"
#include "c.h"
int c::f()
{
	b *p = new b();
	p->privatea = 1;
	std::cout << "access its friend class private member : " <<  p->privatea << "\n";
	return 1;
}
c::c()
{
	std::cout << "create c object. \n " ;
}
