#include <iostream>
#include <string>
#include <vector>
#include <memory>
using namespace std;

int main(void)
{
   vector<int> numbers;
   shared_ptr<vector<int>>p1 = make_shared<vector<int>>(numbers);
}