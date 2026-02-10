#include <iostream>

using namespace std;
void print(int n)
{
    if(n==-1)return;
    cout<<"Nagarajan"<<endl;
    print(n-1);
}
int main() {
    // Write C++ code here
    std::cout << "Try programiz.pro";
    print(4);
    return 0;
}