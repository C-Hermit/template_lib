#include<iostream>
#include"template_lib.h"
int main(void)
{
    int *b=new int[3];
    b[1]=0;
    b[2]=0;
    chain_maxpriority_queue<int> a;
    a.initialize(b,10);
    if (a.empty())
    {
        std::cout<<"empty"<<std::endl;
    }
    std::cout << "Number of nodes = ";
    std::cout << a.length() << std::endl;
    a.output();
    return 0;
}