#include<iostream>
#include<math.h>

using namespace std;
bool checkParlindrome(string str,int i,int j)
{
    if(i >= j)return true;
    if(str[i]!=str[j])return false;
    return checkParlindrome(str,i+1,j-1);
}
int main()
{
    string str = "racecar";
    bool ans = checkParlindrome(str,0,str.size()-1);
    cout<<"Answer: "<<ans<<endl;
    return 0;
}