#include<iostream>
#include<vector>
#include<climits>
#include<map>
#include<list>
#include<utility>

using namespace std;

class HeapC
{
	private:
	int *harray;
	int capacity;
	int incrementVal;

public:
	HeapC(int c);
	void insertKey(int val);
	int left(int index);
	int right(int index);
	int parent(int index);
	int extractMin();
	void decreaseKey(int index, int val);
	void MinHeapify(int index);
	void deleteKey(int index);
	int getMin() {return harray[0];}
};

HeapC::HeapC(int c)
{
	capacity = c;
	incrementVal=-1;
	harray = new int[capacity];
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

void swap(int &a, int &b)
{
	int temp = a;
	a = b;
	b = temp;
}

void HeapC::insertKey(int val)
{
	if(incrementVal == capacity - 1)
	{
		cout<<" could not insert more elements "<<endl;
		return;
	}

incrementVal++;
	harray[incrementVal] = val;
	int i =  incrementVal;
	while(i !=0 && harray[parent(i)] > harray[i])
	{
		swap(harray[parent(i)],harray[i]);
		i = parent(i);
	}

	//incrementVal++;
}

void HeapC::deleteKey(int index)
{
	decreaseKey(index,INT_MIN);
	extractMin();
}

void HeapC::MinHeapify(int index)
{
	int Left = left(index);
	int Right = right(index);
	int smallerIndex = index;
	if(harray[index] > harray[Left] && Left<=incrementVal)
	{
		smallerIndex = Left;
	}
	if(harray[smallerIndex] > harray[Right] && Right<=incrementVal)
	{
		smallerIndex = Right;
	}	
	if(smallerIndex !=index)
	{
		swap(harray[smallerIndex],harray[index]);
		MinHeapify(smallerIndex);
	}
}

int HeapC::extractMin()
{

if(incrementVal == 0)
{
	incrementVal--;
	return harray[0];	
} 
	int min = harray[0];
	//cout<<harray[incrementVal]<<endl;
	harray[0]=harray[incrementVal];
	incrementVal--;
	MinHeapify(0);
	return min;
}

void HeapC::decreaseKey(int index,int newVal)
{

	harray[index] = newVal;
	int i = index;
	while(i !=0 && harray[parent(i)] > harray[i])
	{
		swap(harray[parent(i)],harray[i]);
		i = parent(i);
	}

}


int main()
{
    HeapC h(11);
    h.insertKey(3);
    h.insertKey(2);
    h.deleteKey(1);
    h.insertKey(15);
    h.insertKey(5);
    h.insertKey(4);
    h.insertKey(45);
    cout << h.extractMin() << " ";
   cout << h.getMin() << " ";
   h.decreaseKey(2, 1);
   cout << h.getMin();
    return 0;
}