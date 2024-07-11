#include"template_lib.h"
int main(void)
{
    int a[11]={0,1,2,3,4,5,6,7,8,9,10};
    maxloser_competitivetree b(a,10);
    b.replay(1,1);
    b.output();
    return 0;
}