#include<iostream>
using namespace std;


int main()
{
	int arr[]={10, 22, 9, 33, 21, 50, 41, 60} ;

	int s = sizeof(arr)/sizeof(arr[0]);
	int LIS[11]={1};

	for(int i=1;i<s;i++)
	{
		for(int j=0;j<i;j++)
		{
			if(arr[j]<arr[i]) LIS[i]=max(LIS[j]+1,LIS[i]);
		}
	}

int max =0;
for(int i=0;i<s;i++)
{
	max = LIS[i]>max?LIS[i]:max;
}
	

	cout<<" answer is "<<max<<endl;
	return 0;


}