#include"template_lib.h"
int main(void)
{
    std::pair<const int,int> b(10,10);
    indexed_binary_search_tree<int,int> a;
    a.insert(b);
    a.ascend();
    std::cout<<'a';
    return 0;
}