#include<iostream>
#include"template_lib.h"
int main(void)
{
    
    array_binarytree<int> a;
    if (a.empty())
    {
        std::cout<<"empty"<<std::endl;
    }
    a.pre_order_output();
    std::cout << "Number of nodes = ";
    std::cout << a.length() << std::endl;
    return 0;
}