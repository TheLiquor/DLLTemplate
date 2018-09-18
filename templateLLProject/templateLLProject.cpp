#include <iostream>
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

};

int main()
{
	MyList<int> list; // access list class
	bool result = false; // bool to display output find function
	
	list.insertLast(10); // insert at end
	list.insertLast(12); // insert at end
	list.insertFirst(15); // insert at beginning
	list.show(); // print
	system("pause");

	list.deleteNode(15); //delete specific node
	list.show(); // print
	system("pause");

	result = list.findNode(12); //find specific node
	cout << result << endl; // print out if find found something or not
	system("pause");
	
	return 0;
}