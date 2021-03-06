#include<iostream>
#include<vector>
using namespace std;;

class DisjointSet
{


int *parent;
int *rank;

public:
	DisjointSet(int size); /// it does make set internally
	void Union(int a,int b);
	int findset(int v);
	

};

DisjointSet::DisjointSet(int size)
{
	parent = new int[size];
	rank = new int[size];
	
	// makeset here
	for(int i=0;i<size;i++)
	{
		parent[i] = i;
		rank[i] = 0;
	}

}

void DisjointSet::Union(int a,int b)
{

	int repA = findset(a);
	int repB = findset(b);

	if(repA == repB) return;
	if(rank[repA] >= rank[repB])
	{
		rank[repA] = rank[repA]+1;
		parent[repB] = repA;
		rank[repB]=0;
	}
	else
	{
		rank[repB] = rank[repB]+1;
		parent[repA] = repB;
		rank[repA]=0;
	}
}

int DisjointSet::findset(int v)
{

	if(parent[v] == v) return v;
	else
	{
		parent[v] = findset(parent[v]);
		return parent[v];
	}
}



int main()
{
	DisjointSet dsObj(6);
	dsObj.Union(0,1);
	dsObj.Union(1,2);
	dsObj.Union(3,4);
	dsObj.Union(5,6);
	dsObj.Union(4,5);
	dsObj.Union(2,5); 

	int res = dsObj.findset(6);
	cout<<" representative   "<<res<<endl;



}