#include<iostream>
#include"template_lib.h"
int main(void)
{
    int *b=new int[10];
    b[1]=0;
    chain_maxpriority_queue<int> a;
    if (a.empty())
    {
        std::cout<<"empty"<<std::endl;
    }
    std::cout << "Number of nodes = ";
    std::cout << a.length() << std::endl;
    return 0;
}