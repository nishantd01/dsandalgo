#include<iostream>
using namespace std;


int main()
{
	int arr[]={2,5,3,6};
	int s = sizeof(arr)/sizeof(arr[0]);
	int k = 10;
	int T[s][k+1];

	for(int i=0;i<s;i++)T[i][0]=1;
	for(int j=1;j<=k;j++)
	{
		if(j % arr[0] == 0) T[0][j] = 1;
		else T[0][j]=0;
	}

	for(int i=1;i<s;i++)
	{
		for(int j=1;j<=k;j++)
		{
			if(arr[i]>j) T[i][j]=T[i-1][j];
			if(arr[i]<=j)
			{
				
				//else
				 T[i][j] = T[i-1][j] + T[i][j-arr[i]];
				 //if(j%arr[i] == 0) T[i][j] = T[i][j] +1;
			}
		}
	}

	cout<<" answer is "<<T[s-1][k]<<endl;
	return 0;


}