#include<iostream>

using namespace std;
void print(int n, int& ans)
{
    if(n==0)return;
    ans=ans+n;
    print(n-1,ans);
}
int main()
{
    int ans=0;
    print(4,ans);
    cout<<ans<<endl;
    return 0;
}