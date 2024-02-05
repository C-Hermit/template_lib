#include<iostream>
#include"template_lib.h"
int main(void)
{
    chain_dictionary<int,int> a(10);
    std::pair<int,int> b;
    b.first=1;
    b.second=1;
    a.insert((std::pair<const int,int>)b);
    if (a.empty())
    {
        std::cout<<"empty"<<std::endl;
    }
    std::cout<<a.length()<<std::endl;
    std::cout<<a<<std::endl;
    std::cout<<a.find(1)<<std::endl;
    return 0;
}