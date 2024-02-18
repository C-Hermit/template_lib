#include<iostream>
#include"template_lib.h"
int main(void)
{
    array_queue<int> a(11);
    if (a.empty())
    {
        std::cout<<"empty"<<std::endl;
    }
    std::cout<<a.length()<<std::endl;
    return 0;
}