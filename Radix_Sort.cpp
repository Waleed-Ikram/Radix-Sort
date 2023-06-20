#include <iostream>
#include <string.h>
using namespace std;

template <class T>
class Queue
{
private :

	int MaxSize = 0; // max Queue size
	int front, rear;
	T* arr;  // Array of the queue
	int size;

public : 

	Queue()  // Default constructor
	{
		MaxSize = 10;
		arr = new T[MaxSize];
		size = 0;
		rear = -1; // points to the last element
		front = 0; // points to first element

	}
	
	Queue(int size_input)
	{
		if (size_input <= 0) 
			MaxSize = 10; 
		else MaxSize = size_input;
		
		arr = new T[MaxSize];
		size = 0;
		rear = -1; // points to the last element
		front = 0; // points to first element
	}

	bool isFull()
	{
		return (MaxSize == size);
	}
	
	bool isEmpty()
	{
		return (size == 0);
	}
	
	
	void Enqueue(T data)
	{
		if (!isFull()) 
		{
			rear++;
			arr[rear] = data;
			size++;
		}
	}

	void Dequeue(T& data)
	{
		if (!isEmpty())
		{
			data = arr[front];
			front++;
			size--;
		}
	}

	void print()
	{
		if (isEmpty())
			return;
		
		for (int i = front; i <= rear; i++)
		{
			cout << arr[i] << " ";
		}
	}

	void reset()
	{
		rear = -1;
		size = 0;
		front = 0;
	}

};


void RadixSort(Queue<int>& q, int n, int k)  // radix sort for integers
{
	Queue<int> bucket[10];   // Used for numbers 0-9
	int key = 0;
	int mod = 0;
	int dequeued = 0;
	int div = 1;

	for (; k > 0; k--)
	{
		for (int i = 0; i < n; i++)
		{
			q.Dequeue(key);
			mod = key / div;
			mod = mod % 10;   // extracts the digit wanted
			bucket[mod].Enqueue(key);
		}

		q.reset();   // to bring the front and rear back to place

		for (int m = 0; m < 10; m++)
		{
			while (!bucket[m].isEmpty())   // joins the numbers once again in the initial queue
			{
				bucket[m].Dequeue(dequeued);
				q.Enqueue(dequeued);
			}
		}

		for (int i = 0; i < 10; i++)
		{
			bucket[i].reset();
		}
		
		div = (div * 10);
	}
}


void RadixSort_String(Queue<string> &queue, int n, int k)
{
	Queue<string> bucket[256];  // for all ASCII values
	string str;
	string dequeued;
	char letter;

	for (; k > 0; k--)
	{
		for (int i = 0; i < n; i++)
		{
			queue.Dequeue(str);
			letter = str[k - 1];  // takes the char required 
			bucket[letter].Enqueue(str);  // gives the index by ASCII value
		}

		queue.reset();

		for (int m = 0; m < 256; m++)  // Enqueue in the initial queue once agin
		{
			while (!bucket[m].isEmpty())
			{
				bucket[m].Dequeue(dequeued);
				queue.Enqueue(dequeued);
			}
		}

		for (int i = 0; i < 256; i++)
		{
			bucket[i].reset();
		}
	}


}

int main()
{

	cout << "What is the length of the array to be sorted ?\n";
	int arr_size = 0;
	cin >> arr_size;

	cout << "What are the maximum digits in a number ?\n";
	int k = 0;
	cin >> k;
	
	Queue<int> q(arr_size);

	q.Enqueue(82);
	q.Enqueue(901);
	q.Enqueue(100);
	q.Enqueue(12);
	q.Enqueue(150);
	q.Enqueue(4076);
	q.Enqueue(55);
	q.Enqueue(17);

	cout << "Array before SORT : \n";
	q.print();


	cout << "\n\nAfter Radix Sort is called.\n";
	RadixSort(q, arr_size, k);
	q.print();
	cout << "\n\n";

	cout << "\n\nHow many strings are in the Queue ? \n";
	cin >> arr_size;
	cout << "What are the maximum letters in a string ? \n";
	cin >> k;

	Queue<string> str(arr_size);
	string input;

	cout << "\nEnter your strings one by one. Make sure they are of same length.\n";
	for (int i = 0; i < arr_size; i++)
	{
		cin >> input;
		str.Enqueue(input);
	}


	str.print();

	RadixSort_String(str, arr_size, k);

	cout << "\n\nAfter Radix Sort is called.\n";
	str.print();
	cout << "\n\n";
}