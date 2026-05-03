#include <print>


template <class T>
struct Node {
	T data;
	Node<T>* next = nullptr;
	Node(T data):data(data)
	{
	}
	~Node()
	{
	
		
	}

};

template <class T>
class LinkedList
{
private:
	Node<T>* head;
	Node<T>* tail;
	int length;
public:

	LinkedList():head(nullptr),tail(nullptr),length(0){}


	inline int Length() const { return length; }
	inline Node<T>* GetHead() const{ return head; }

	void Print()
	{
		Node<T>* tempHead = head;
		while (tempHead != nullptr)
		{
			std::print(" {} ", tempHead->data);
			tempHead = tempHead->next;
		}
		std::println();
	}

	Node<T>* Find(int data)
	{
		Node<T>* tempHead = head;
		while (tempHead != nullptr)
		{
			if (data == tempHead->data)
			{
				return tempHead;
			}
			tempHead = tempHead->next;
		}

		return nullptr;
	}


	void InsertEnd(T data)
	{

		Node<T>* newNode = new Node<T>(data);
		++length;
		if (head == nullptr)
		{
			head = tail = newNode;
			return;
		}
		tail->next = newNode;
		tail = newNode;
		
	}

	Node<T>* Get_nth(int n)
	{
		if (n > length || n < 1) return nullptr;
		int i = 1;
		for ( Node<T>* node = head; node; node = node->next)
		{
			if (i == n)
			{
				return node;
			}
			++i;
		}
		return nullptr;
	}

	void InsertFront(int data)
	{
		Node<T>* newNode = new Node<T>(data);
		if (head == nullptr)
		{
			head = tail = newNode;
			++length;
			return;
		}
		newNode->next = head;
		head = newNode;
		++length;
	}

	Node<T>* Get_nth_Back(int n)
	{
		int index = length - (n - 1);//get real index from start based on index from back
		return Get_nth(index);
	}

	bool IsEqual(const LinkedList& otherList)
	{
		if (otherList.Length() != Length()) { return false; }

		Node<T>* currentNode = head;
		Node<T>* otherCurrent = otherList.GetHead();
		for (;currentNode && otherCurrent; currentNode = currentNode->next, otherCurrent = otherCurrent->next)
		{
			if (currentNode->data != otherCurrent->data)
			{
				return false;
			}
		}
		return true;

	}

	void DeleteFront()
	{
		Delete_nth(1);
	}

	void DeleteEnd()
	{
		Delete_nth(length);
	}

	void Delete_nth(int n)
	{
		if (length == 0 || n > length || n < 1) return;

		if (n == 1)
		{
			if (length == 1)
			{
				delete head;
				head = tail = nullptr;
				--length;
				return;
			}
			Node<T>* tempNode = head;
			head = head->next;
			delete tempNode;
		}
		else if (n == length)
		{
			Node<T>* prevTail = Get_nth_Back(2);
			delete tail;
			tail = prevTail;
			tail->next = nullptr;
		}
		else
		{
			Node<T>* prevNode = Get_nth(n - 1);
			Node<T>* toDeleteNode = prevNode->next;
			prevNode->next = toDeleteNode->next;
			delete toDeleteNode;
		}
		--length;
	}

	void DeleteKey(T data)
	{
		int i = 1;
		for (Node<T>* current = head; current; current = current->next,++i)
		{
			if (data == current->data)
			{
				Delete_nth(i);
				break;
			}
		}
	}

	

	~LinkedList()
	{
		while (head)
		{
			Node<T>* temp = head;
			head = head->next;
			delete temp;
		}

		tail = nullptr;
		length = 0;
	}
};




int main()
{
	LinkedList<int> list;
	list.InsertEnd(6);
	list.InsertEnd(25);
	list.InsertEnd(10);
	list.InsertEnd(8);
	list.InsertEnd(3);
	list.InsertEnd(25);
	list.InsertEnd(15);
	list.InsertFront(11);
	list.Print();
	std::println("{}", list.Get_nth(3)->data);
	std::println("{}", list.Get_nth_Back(1)->data);
	std::println("{}", list.Get_nth_Back(3)->data);
	list.DeleteFront();
	list.Print();
	list.DeleteEnd();
	list.Print();
	list.Delete_nth(3);
	list.Print();
	list.DeleteKey(25);
	list.Print();
}