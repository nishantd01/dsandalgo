#include<iostream>
#include<vector>
#include<climits>
#include<map>
#include<list>
#include<utility>

//https://www.youtube.com/watch?v=lAXZGERcDf4&list=PLrmLmBdmIlpu2f2g8ltqaaCZiq6GJvl1j&index=2
using namespace std;

struct Node
{
	int vertex;
	int distance; 
};

class HeapC
{
	private:
	Node *harray;
	int capacity;
	

public:
	HeapC(int c);
	int incrementVal;
	void insertKey(Node val); // Inserts node into heap
	map<int,int> IndexMap; // vertex and its index map
	int left(int index);
	int right(int index);
	int parent(int index);
	Node extractMin();
	void swap(Node &a, Node &b);
	void decreaseKey(int index, Node val);
	void MinHeapify(int index);
};


HeapC::HeapC(int c)
{
	capacity = c;
	incrementVal=-1;
	harray = new Node[capacity];
}

int HeapC::parent(int index)
{
	return (index-1)/2;
}

int HeapC::left(int index)
{
	return (2*index+1);
}

int HeapC::right(int index)
{
	return (2*index+2);
}

void HeapC::swap(Node &a, Node &b)
{
	Node c = a;
	a = b;
	b = c;

	int inTemp = IndexMap[b.vertex];
	IndexMap[b.vertex] = IndexMap[a.vertex];
	IndexMap[a.vertex] =  inTemp;
}


// O(log(n))
void HeapC::insertKey(Node v)
{
	if(incrementVal == capacity - 1)
	{
		cout<<" could not insert more elements "<<endl;
		return;
	}

	incrementVal++;
	harray[incrementVal] = v;
	
	IndexMap[v.vertex] = incrementVal;
	int i =  incrementVal;
	while(i !=0 && harray[parent(i)].distance > harray[i].distance)
	{
		swap(harray[parent(i)],harray[i]);
		i = parent(i);
	}

	
}

//O(log(n))
/*void HeapC::deleteKey(int index)
{
	decreaseKey(index,INT_MIN);
	extractMin();
}*/


//O(log(n))
void HeapC::MinHeapify(int index)
{
	int Left = left(index);
	int Right = right(index);
	int smallerIndex = index;
	if(harray[index].distance > harray[Left].distance && Left<=incrementVal)
	{
		smallerIndex = Left;
	}
	if(harray[smallerIndex].distance > harray[Right].distance && Right<=incrementVal)
	{
		smallerIndex = Right;
	}	
	if(smallerIndex !=index)
	{
		swap(harray[smallerIndex],harray[index]);
		MinHeapify(smallerIndex);
	}
}

Node HeapC::extractMin()
{

if(incrementVal == 0)
{
	incrementVal--;
	return harray[0];	
} 
	Node min = harray[0];
	
	harray[0]=harray[incrementVal];
	IndexMap[harray[incrementVal].vertex]=0;
	incrementVal--;
	
	
	MinHeapify(0);
	return min;
}

void HeapC::decreaseKey(int index,Node newVal)
{

	harray[index] = newVal;
	
	int i = index;
	while(i !=0 && harray[parent(i)].distance > harray[i].distance)
	{
		swap(harray[parent(i)],harray[i]);
		i = parent(i);
	}

}


map<int,int> singleSourceShortestPath(vector< list< pair<int,int> > > adjList)
{

	HeapC mapHeapObj(adjList.size());
	map<int,int> distanceMap;
	map<int,int> pathMap;
	for(int i=0;i<adjList.size();i++)
	{
		Node node;
		node.vertex = i;
		node.distance = INT_MAX;
		distanceMap[i]=INT_MAX;
		mapHeapObj.insertKey(node);
	}

	// start with A , decrease the value from INT_MAX to 0
	Node A;
	A.vertex=0;
	A.distance=0;
	mapHeapObj.decreaseKey(0,A);
	distanceMap[0] = 0;

	while(mapHeapObj.incrementVal>=0)
	{
		//cout<<mapHeapObj.vertexDistance.size()<<endl;
		Node min = mapHeapObj.extractMin();
		list< pair< int,int > >::iterator it = adjList[min.vertex].begin();
		while(it!=adjList[min.vertex].end())
		{
			int minDis = distanceMap[min.vertex] + it->second;
			if(distanceMap[it->first]>minDis)
			{
				distanceMap[it->first] = minDis;
				//mapHeapObj.vertexDistance[it->first] = minDis;
				int tempIndex = mapHeapObj.IndexMap[it->first];
				//cout<<tempIndex<<endl;
				Node tempNode;
				tempNode.vertex = it->first;
				tempNode.distance = minDis;
				mapHeapObj.decreaseKey(tempIndex,tempNode);
			}
			it++;
		}

	}
	return distanceMap;
	
}


int main()
{
	vector< list< pair<int,int> > > adjList(6);

	adjList[0].push_back(make_pair(1,5));
	adjList[0].push_back(make_pair(4,2));
	adjList[0].push_back(make_pair(3,9));
	adjList[1].push_back(make_pair(0,5));
	adjList[1].push_back(make_pair(2,2));
	adjList[2].push_back(make_pair(1,2));
	adjList[2].push_back(make_pair(3,3));
	adjList[3].push_back(make_pair(2,3));
	adjList[3].push_back(make_pair(0,9));
	adjList[3].push_back(make_pair(5,2));
	adjList[4].push_back(make_pair(0,2));
	adjList[4].push_back(make_pair(5,3));
	adjList[5].push_back(make_pair(4,3));
	adjList[5].push_back(make_pair(3,2));

	map<int,int> distanceM = singleSourceShortestPath(adjList);

	//singleSourceShortestPath(adjList);

	map<int,int>::iterator it;
	for(it=distanceM.begin();it!=distanceM.end();it++)
	{
		cout<<" distance of  "<<it->first<<" from A "<<it->second<<endl;
	}

	
	return 0;
}