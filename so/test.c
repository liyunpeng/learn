#include "stdio.h"

void say();
void so_sub_2();
main(){
say();
so_sub_2();
char *p;
p = malloc(10);
*p = 'c';
*p++;
//printf("%c", *p++);
}
