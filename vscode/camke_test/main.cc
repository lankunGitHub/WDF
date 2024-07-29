#include<iostream>
#include"addfunction.hpp"
#include"mulfunction.hpp"

int main()
{
    auto c = addfunction(1,2);
    std::cout << c << std::endl;
    c = mulfunction(4,5);
    std::cout << c << std::endl;
}