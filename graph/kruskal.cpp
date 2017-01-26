//https://www.youtube.com/results?search_query=kruskal%27s+algorithm+tushar+roy
#include<iostream>
#include<algorithm>
#include<vector>
using namespace std;

class DisjointSet
{
protected:
	int *parent;
	int *rank;
	int V;
public:
	void Union(int a,int b);
	int findset(int v);
};

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

class Kruskal:public DisjointSet
{
public:
	Kruskal(int size)
	{
		V = size;
		parent = new int[size];
		rank = new int[size];
	
	// makeset here
	   for(int i=0;i<size;i++)
	   {
		parent[i] = i;
		rank[i] = 0;
       }
	};
	
	vector< pair<int, int> > KrukskalMST(vector<pair< pair<int,int>, int> > Edge,int noOfEdges,int &weightOfTree);

};

vector< pair<int, int> > Kruskal::KrukskalMST(vector<pair< pair<int,int>, int> > Edge,int E, int &weightOfTree)
{
	vector< pair<int,int> > result;
	weightOfTree=0;
	//vector<pair < pair<int,int> ,int>::iterator it = Edge.begin();
	//O(E)
	for(int it=0;it<E;it++)
	{
		pair< pair<int,int>, int> pi = Edge[it];
		pair<int,int> pairOfVertices = pi.first;

		//cout<<pairOfVertices.first<<"  "<<pairOfVertices.second<<endl;

		int repOfFirst = findset(pairOfVertices.first);
		int repOfSecond = findset(pairOfVertices.second);
		//cout<<repOfFirst<<"  "<<repOfSecond<<endl;

		if(repOfFirst != repOfSecond)
		{
			weightOfTree+=pi.second;
			result.push_back(pairOfVertices);
			Union(pairOfVertices.first,pairOfVertices.second);
		}
	}
	return result;

}

bool compareFunc(const pair< pair<int,int>, int> &a, const pair< pair<int,int>, int> &b)
{
	return a.second < b.second;
}

int main()
{
Kruskal dsObj(6);
vector<pair< pair<int,int>, int> > Edge(9);

Edge[0]=make_pair(make_pair(0,1),3);
Edge[1]=make_pair(make_pair(0,3),1);
Edge[2]=make_pair(make_pair(1,2),1);
Edge[3]=make_pair(make_pair(1,3),3);
Edge[4]=make_pair(make_pair(2,3),1);
Edge[5]=make_pair(make_pair(2,4),5);
Edge[6]=make_pair(make_pair(2,5),4);
Edge[7]=make_pair(make_pair(3,4),6);
Edge[8]=make_pair(make_pair(4,5),2);


//O(Elog(E)) sort
sort(Edge.begin(),Edge.end(),compareFunc);
int wt;

vector< pair<int,int> > result = dsObj.KrukskalMST(Edge,9,wt);

//cout<<result.size();

vector< pair<int,int> >::iterator it = result.begin();

cout<<"Min Spanning tree and their Vertices are as follows"<<endl;

while(it != result.end())
{
	cout<<"  "<<(*it).first<<"  "<<(*it).second<<endl;
	it++;
}

cout<<" weight of the tree  is"<<wt<<endl;

	//return 0;
	
}


// Time complexity - O(ElogE + E)
// Space complexity - O(E)