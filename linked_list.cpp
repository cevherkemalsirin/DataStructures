#include <iostream>

using namespace std;

class Node {
public:
	int value{};
	Node* next{};
};

class List {
	Node* head{};
	Node* tail{};
	int length{};
public:

	inline int Getlength() const { return this->length; }

	void Print()
	{
		for (Node* t = head; t; t = t->next)
		{
			cout << t->value << " ";
		}
	}

	void Insert_Front(int value)
	{
		Node* newnode = new Node{ value, nullptr };
		if (head)
		{
			newnode->next = head;
			head = newnode;
		}
		else
		{
			tail = head = newnode;
		}

		length++;
	}

	void Insert(int index, int value)
	{
		//1 based index is given 0 in the begining 1 after first element
		if (index < 0 || index > length) return;
		if (index == 0) Insert_Front(value);
		else
		{
			Node* p = head;
			for (int i = 1; i < index; ++i)
			{
				p = p->next;
			}
			Node* newNode = new Node{ value,nullptr };
			newNode->next = p->next;
			p->next = newNode;
			++length;
		}
	}

	void Insert_End(int value)
	{
		Node* newNode = new Node{ value, nullptr };

		if (head)
		{
			tail->next = newNode;
			tail = newNode;
		}
		else
		{
			head = tail = newNode;
		}

		++length;
	}

	void  Delete_Front()
	{
		if (head)
		{
			Node* temp = head;
			head = head->next;
			length--;
		}
	}

	void Delete_End()
	{
		if (head == tail)
		{
			delete head;
			head = tail = nullptr;
			return;
		}
		for (Node* t = head; t; t = t->next)
		{
			if (t->next == tail)
			{
				delete tail;
				t->next = nullptr;
				tail = t->next;
				return;
		    }
	    }
	}

	void Delete(int val)
	{
		if (val == head->value) Delete_Front();
		else
		{
			Node* followTemp = head;
			for (Node* p = head->next; p; p = p->next)
			{
				if (p->value == val)
				{
					followTemp->next = p->next;
					delete p;
					p = nullptr;
					break;
			    }
				followTemp = p;
			}
		}
		

	}

	Node* Get_nth(int n)
	{
		if (length < n || n < 0)
		{
			return nullptr;
		}
		Node* traverse = head;
		for (int i = 1; i < n; ++i)
		{
			traverse = traverse->next;
		}
		return traverse;
	}

	Node* Get_nth_Back(int n)
	{
		if (n < 1 || n > length) return nullptr;

		int cnt = 0;
		for (Node* cur = head; cur; cur = cur->next)
		{
			if (cnt + n == length)
			{
				return cur;
			}
			cnt++;
		}

	}

	int Search(int value) //0 based
	{
		int index = 0;
		for (Node* h = head; h; h = h->next)
		{
			if (h->value == value)
			{
				return index;
		    }
			index++;
	    }

		return -1;
	}

	int Improved_Search(int value)
	{
		int index = 0;
		Node* Prev = nullptr;
		for (Node* h = head; h; h = h->next)
		{
			if (h->value == value)
			{
				if (Prev)
				{
					swap(Prev->value, h->value);
					index--;
				}
				return index;
			}
			Prev = h;
			index++;
		}

		return -1;
	}

	bool Is_Same(const List& otherlist)
	{
		if (length != otherlist.length) return false;

		for (Node* cur = head, *othercur = otherlist.head; cur && othercur; cur = cur->next, othercur = othercur->next)
		{
			if (cur->value != othercur->value)
			{
				return false;
		    }
		}

		return true;
	}

	~List()
	{
		Node* temp = nullptr;
		while (head)
		{
			temp = head->next;
			delete head;
			head = temp;
		}
		head = tail = nullptr;
	}
};


int main01()
{
	return 0;
	List l{};
	l.Insert_Front(243);
	l.Insert_End(10);
	l.Insert_End(5);
	l.Insert_End(3);
	l.Print();
	cout << "\n";
	l.Delete(10);
	l.Print();
	cout << "\n";
	l.Insert(0,101);
	l.Insert(3,25);
	l.Print();

	/*
	cout << endl << l.Get_nth(3)->value;
	cout << endl << l.Search(l.Get_nth(2)->value);
	l.Insert_Front(24);
	cout << endl;
	l.Print();
	l.Delete_Front();
	cout << endl;
	l.Print();
	cout << endl << l.Get_nth_Back(2)->value;
	*/
}