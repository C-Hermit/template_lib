#include<iostream>
#include"template_lib.h"
int main(void)
{
    int a[10]={1,2,3,4,5,6,7,8,9,10};
    maxwinner_competitivetree b(a,10);
    b.output();
    return 0;
}