//https://www.youtube.com/watch?v=oP2-8ysT3QQ
#include<iostream>
#include<climits>
#include<map>
#include<list>
#include<vector>
using namespace std;



class Heap
{

public:
	//Heap(int s);
	int Incindex;
	pair<int,int> *heapArray;
	map<int,int> IndexMap;
	int sizeOfHeap;
	void insertKey(pair<int,int> Vertex);
	void decreaseKey(int vKey, int value);
	void minHeapify(int index);
	void swap(pair<int,int> &v1, pair<int,int> &v2);
	int left(int i)
	{
		return (2*i+1);
	};
	int right(int i)
	{
		return (2*i+2);
	};

	int parent(int i)
	{
		return (i-1)/2;
	};
	pair<int,int> extractMin();
};

void Heap::swap(pair<int,int> &v1, pair<int,int> &v2)
{
	int indexV1 = IndexMap[v1.first];
	IndexMap[v1.first] = IndexMap[v2.first];
	IndexMap[v2.first] = indexV1;

	pair<int,int> temp = v1;
	v1 = v2;
	v2 = v1;
}


void Heap::insertKey(pair<int,int> Vertex)
{
	if(Incindex == sizeOfHeap -1)
	{
		cout<<" could not insert more elements sorry  :P"<<endl;
		return;
	}

	Incindex++;
	heapArray[Incindex] = Vertex;
	IndexMap[Vertex.first] = Incindex;

	while(Incindex !=0 && heapArray[parent(Incindex)].second > heapArray[Incindex].second)
	{
		swap(heapArray[Incindex],heapArray[parent(Incindex)]);
		Incindex = parent(Incindex);
	}
}

void Heap::decreaseKey(int vKey,int value)
{
	int index = IndexMap[vKey];
	pair<int,int> newval;
	newval =make_pair(vKey,value);
	heapArray[index] = newval;
	while(index !=0 && heapArray[parent(index)].second >heapArray[index].second)
	{
		swap(heapArray[index],heapArray[parent(index)]);
		index = parent(index);
	}
}

pair<int,int> Heap::extractMin()
{
	if(Incindex<0)
	{
		cout<<" nothing more left toted"<<endl;
	}
	else
	{
	pair<int,int> min = heapArray[0];
	heapArray[0] = heapArray[Incindex];
	IndexMap.erase(heapArray[IndexMap].first);
	Incindex--;
	minHeapify(0);

	return min;
}
}

void Heap::minHeapify(int index)
{
	int leftIndex = left(index);
	int rightIndex = right(index);
	int smaller = index;
	if(heapArray[smaller].second>heapArray[leftIndex].second && leftIndex <= Incindex)
	{
		smaller = leftIndex;
	}
	if(heapArray[smaller].second>heapArray[rightIndex].second && rightIndex <=Incindex)
	{
		smaller = rightIndex;
	}

	if(smaller !=index)
	{
		swap(heapArray[smaller],heapArray[index]);
		minHeapify(smaller);
	}
}



class Graph:public Heap
{

public:
	Graph(int size);
	map<int,int> DistanceFromSourceMap;
	vector< pair<int,int> > prims(vector<list <pair<int,int> > > adjList);
};

Graph::Graph(int s)
{
	heapArray = new pair<int,int>[s];
	sizeOfHeap = s;
	Incindex=-1;
	for(int i=0;i<s;i++)
	{
		pair<int,int> p;
		p = make_pair(i,INT_MAX);
		DistanceFromSourceMap[i]=INT_MAX;
		insertKey(p);
	}
	
}

vector< pair<int,int> > Graph::prims(vector<list <pair<int,int> > > adjList)
{
	map<int,pair<int,int> > vertexToEdgeMap;
	int startVertex = 0;
	decreaseKey(startVertex,0);	
	DistanceFromSourceMap[startVertex]=0;
	while(IndexMap.size()>0)
	{
		pair<int,int> vd = extractMin();
		list< pair<int,int> >::iterator it = adjList[vd.first].begin();
		while(it !=adjList[vd.first].end())
		{
			pair<int,int> neighbours = *it;
			if(IndexMap.count(neighbours.first) !=0)
			{
				int sum = neighbours.second;
				if(sum < DistanceFromSourceMap[neighbours.first])
				{
					DistanceFromSourceMap[neighbours.first] = sum;
					decreaseKey(neighbours.first,sum);
					pair<int,int> edge;
					edge.first = vd.first;
					edge.second = neighbours.first;
					vertexToEdgeMap[neighbours.first]=edge;
				}
			}

			it++;
		}
	}
}



int main()
{

	Graph g(6);
	vector< list< pair<int,int> > > adjList(6);
	prims(adjList);



	return 0;
}