#include<iostream>
#include<math.h>

using namespace std;
int fibb(int n)
{
    if(n == 0)return 0;
    if(n == 1)return 1;
    return fibb(n-1)+fibb(n-2);
}
int main()
{
    int ans = fibb(5);
    cout<<"Answer: "<<ans<<endl;
    return 0;
}