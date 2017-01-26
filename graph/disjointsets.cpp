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
	if(a<b)
	{
		rank[a]= rank[a]+1;
		rank[b]=0;
		parent[b] = a;
	}
	else
	{
		rank[b]= rank[b]+1;
		rank[a] = 0;
		parent[a] = b;
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

	int res = dsObj.findset(1);
	cout<<" res  "<<res<<endl;



}