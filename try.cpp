#include<iostream>
#include"template_lib.h"
int main(void)
{
    
    chain_binarytree<int> a,x,y,z;
    y.make_tree(1,a,a);
    z.make_tree(2,a,a);
    x.make_tree(3,y,z);
    y.make_tree(4,x,a);
    if (a.empty())
    {
        std::cout<<"empty"<<std::endl;
    }
    y.pre_order_output();
    std::cout << "Number of nodes = ";
    std::cout << y.length() << std::endl;
    std::cout << "height = ";
    std::cout << y.height() << std::endl;
    return 0;
}