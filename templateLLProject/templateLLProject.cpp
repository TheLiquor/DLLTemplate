#include <iostream>
#include <time.h> 
using namespace std;

template <class T>
class MyNode
{
public:
	MyNode(const T &e = T(), MyNode *n = NULL, MyNode *p = NULL) : element(e), next(n), previous(p) {}
	~MyNode() {}
	T element;
	MyNode *next;
	MyNode *previous;
};

template <class T>
class MyList
{
private:
	MyNode<T> *head;
	MyNode<T> *tail;

public:
	MyList()
		: head(nullptr)
		, tail(nullptr)
	{}
	~MyList()
	{
		clear();
		delete head;
		delete tail;
	}

	bool isEmpty() { 
		return head == nullptr; 
}
	// insert at the beginning
	void insertFirst(const T &e)
	{
		if (isEmpty())
			head = tail = new MyNode<T>(e);
		else
		{
			MyNode<T> *newNode = new MyNode<T>(e, head, nullptr);
			head->previous = newNode; // new node is predecessor of head
			head = newNode;          // new head is new node
		}
	}

	// instert at the end 
	void insertLast(const T &e)
	{
		if (isEmpty())
			head = tail = new MyNode<T>(e);
		else
		{
			MyNode<T> *newNode = new MyNode<T>(e, nullptr, tail);
			tail->next = newNode; // new node is successor of tail
			tail = newNode;      // new tail is new node
		}
	}

	// deletes a specific node
	void deleteNode(T element)
	{
		MyNode<T> * tmp = head;
		while (tmp && tmp->element != element)
		{
			tmp = tmp->next;
		}

		if (tmp)
		{
			if (tmp->previous && tmp->next) // no change to head or tail
			{
				tmp->previous->next = tmp->next;
				tmp->next->previous = tmp->previous;
			}
			else if (tmp->previous) // change to tail
			{
				tmp->previous->next = tmp->next;
				tail = tmp->previous;
			}
			else if (tmp->next) // change to head
			{
				tmp->next->previous = tmp->previous;
				head = tmp->next;
			}

			delete tmp;
		}
	}

	// finds a specific node : EXACT SAME as delete node, but returns bool
	bool findNode(T element)
	{
		MyNode<T> * tmp = head;
		while (tmp && tmp->element != element)
		{
			tmp = tmp->next;
		}

		if (tmp)
		{
			if (tmp->previous && tmp->next) 
			{
				tmp->previous->next = tmp->next;
				tmp->next->previous = tmp->previous;
			}
			else if (tmp->previous) 
			{
				tmp->previous->next = tmp->next;
				tail = tmp->previous;
			}
			else if (tmp->next)
			{
				tmp->next->previous = tmp->previous;
				head = tmp->next;
			}

		}
		return tmp;
	}

	// clears out the list while theres 
	void clear() 
	{
		MyNode<T> *curr = head;
		while (curr != nullptr)
		{
			MyNode<T> *del = curr;
			curr = curr->next;
			delete del;
		}
		head = tail = nullptr;
	}

	// prints out the list
	void show() 
	{
		MyNode<T> *curr = head;
		while (curr != nullptr)
		{
			std::cout << curr->element << "\n";
			curr = curr->next;
		}
	}

	// inserts numbers in order, just like a regular insert however it checks the values and inserts them in the correct order...
	void insertSort(T n)
	{
		MyNode<T> *newNode = new MyNode<T>;
		newNode->element = n;
		newNode->next = NULL;
		newNode->previous = NULL;
		if (head == NULL)
		{
			head = newNode;
		}
		else if (head->element > n)
		{
			MyNode<T>* temp = head;
			head = newNode;
			newNode->next = temp;
			temp->previous = head;
		}
		else {
			MyNode<T> *temp = head;
			MyNode<T> *previous = NULL;
			bool inserted = false;
			while (temp != NULL)
			{
				if (temp->element > n)
				{
					newNode->previous = temp->previous;
					newNode->next = temp;
					temp->previous = newNode;
					if (newNode->previous != NULL)
					{
						newNode->previous->next = newNode;
					}
					inserted = true;
					break;
				}
				previous = temp;
				temp = temp->next;
			}
			if (!inserted)
			{
				newNode->previous = previous;
				previous->next = newNode;
			}

		}
	}

	int* quickSort(int arr[], int left, int right) 
	{
		int i = left, j = right;
		int tmp;
		int pivot = arr[(left + right) / 2];

		while (i <= j) {

			while (arr[i] < pivot)
			{
				i++;
			}

			while (arr[j] > pivot)
			{
				j--;
			}

			if (i <= j) 
			{

				tmp = arr[i];

				arr[i] = arr[j];

				arr[j] = tmp;

				i++;

				j--;

			}

		};


		if (left < j)
		{

			quickSort(arr, left, j);
		}


		if (i < right)
		{
			quickSort(arr, i, right);
		}

		return arr;

	}

	

};


int main()
{
	MyList<int> list; // access list class
	bool result = false; // bool to display output find function
	clock_t t;
	
	
	//list.insertFirst(1); 
	//list.insertFirst(2);
	//list.insertFirst(3); // insert at beginning
	//list.show(); // print
	int test[20] = { 16, 2, 77, 40, 12071, 56, 34, 645, 19, 33, 54, 98, 76, 32, 83, 1, 456, 89, 323, 67 }; // array to merge sort
	t = clock(); // start clock
	int* arr = list.quickSort(test, 0, 19);
	
	
	for (int i = 0; i < 20; i++)
	{
		//list.insertSort(test[i]);
		cout << arr[i] << endl;
	}
	t = clock() - t; // get how much time it took
	printf("It took me %d clicks (%f seconds).\n", t, ((float)t) / CLOCKS_PER_SEC); // print out time
	//list.insertSort(1);
	//list.insertSort(4);
	//list.insertSort(2);
	//system("pause");

	//list.deleteNode(15); //delete specific node
	list.show(); // print
	//system("pause");

	//result = list.findNode(12); //find specific node
	//cout << result << endl; // print out if find found something or not
	//system("pause");

	//list.insertSort();
	list.show();
	system("pause");
	
	return 0;
};