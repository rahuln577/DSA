#include<iostream>
#include<math.h>

using namespace std;
void reverseArr(int *arr,int i,int j)
{
    if(i >= j)return;
    swap(arr[i],arr[j]);
    reverseArr(arr,i+1,j-1);
}
int main()
{
    int ans[]={1,2,3,4,5,6};
    reverseArr(ans,0,5);
    for(auto i:ans)
    {
        cout<<i<<" ";
    }
    return 0;
}