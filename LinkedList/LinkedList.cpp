#include <print>
#include <set>


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


	void DeleteNext(Node<T>* currentNode)
	{
		if (!currentNode || !currentNode->next) return;
		Node<T>* tempDelete = currentNode->next;
		if (!currentNode->next->next && tail)
		{
			//we remove tail
			delete tail;
			tail = currentNode;
			tail->next = nullptr;
			--length;
			return;
		}
		currentNode->next = currentNode->next->next;
		delete tempDelete;
		--length;
	}
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

	void SwapPairs()
	{
		for (Node<T>* current = head; current; current = current->next)
		{
			if (!current->next)
			{
				return;
			}
			std::swap(current->data, current->next->data);
			current = current->next;
		}
	}
	//1 2 3 4 5 6 
	void Reverse()
	{
		/* it just changes data we want to swap adresses
		for (int i = 0; i < length / 2; ++i)
		{
			Node<T>* nodeFront = Get_nth(i + 1);
			Node<T>* nodeBack = Get_nth_Back(i + 1);
			std::swap(nodeFront->data, nodeBack->data);
		}*/

		for (int i = 1; i < length; ++i)
		{
			Node<T>* nodeBack = Get_nth_Back(i);
			Node<T>* nodeBackPrev = Get_nth_Back(i + 1);
			nodeBack->next = nodeBackPrev;
			nodeBackPrev->next = nullptr;
		}
		std::swap(head, tail);
	}

	void DeleteEvenPositions()
	{
		int i = 1;
		int realIndex = 1;
		for (Node<T>* current = head; current;++realIndex,++i)
		{
			if (realIndex % 2 == 0)
			{
				current = current->next;
				Delete_nth(i);
				--i;
				continue;
			}
			current = current->next;
		}
	}

	void InsertSorted(T data)
	{
		if (!head || data < head->data)
		{
			InsertFront(data);
			return;
		}
		Node<T>* prevCurrent = head;
		for (Node<T>* current = head->next; current; current = current->next)
		{

			if (data < current->data)
			{
				Node<T>* newNode = new Node<T>(data);
				prevCurrent->next = newNode;
				newNode->next = current;
				++length;
				return;
			}

			prevCurrent = current;
		}
		InsertEnd(data);
	}

	void SwapHeadTail()
	{
		if (length < 2) return;

		Node<T>* prevTail = Get_nth(length - 1);
		prevTail->next = head;
		tail->next = head->next;
		head->next = nullptr;
		std::swap(head, tail);
	}

	//rotate to left k times
	void LeftRotate(int k)
	{
		// 1 2 3 4 5 
		if (k < 1 || length < 2) return;
		//if k circles,meaning k bigger than length
		k = k % length;
		Node<T>* cutNode = Get_nth(k);
		tail->next = head;
		head = cutNode->next;
		tail = cutNode;
		tail->next = nullptr;
	}

	void DeleteDuplicates()
	{
		if (!head) { return; }

		std::set<T> nodeSet;
		nodeSet.insert(head->data);
		for (Node<T>* current = head->next, *prev = head; current;)
		{
			if (!nodeSet.contains(current->data))
			{
				nodeSet.insert(current->data);
				current = current->next;
				prev = prev->next;
			}
			else
			{
				current = current->next;
				DeleteNext(prev);
			}
		}
	}

	//moves back all the nodes with specific keys
	void MoveBack(T key)
	{
		int i = 0;
		
		for (Node<T>* current = head , *prev = nullptr; (i < length) && current; ++i)
		{
			if (key == current->data)
			{
				if (current == head)
				{
					current = head->next;
					tail->next = head;
					head = head->next;
					tail->next->next = nullptr;
					tail = tail->next;
				}
				else
				{
					prev->next = current->next;
					tail->next = current;
					current->next = nullptr;
					tail = current;
					current = prev->next;
				}
			}
			else
			{
				prev = current;
				current = current->next;
			}
		}
	}

	int FindMax(Node<T>* node)
	{
		if (!node) return INT_MIN;

		int max = std::max(node->data,FindMax(node->next));
		return max;
	}

	void RemoveLastOccurence(T key)
	{
		Node<T>* prevLastOccurence = nullptr;
		for (Node<T>* current = head,*prev = nullptr; current; prev = current, current = current->next)
		{
			if (current->data == key)
			{
				prevLastOccurence = prev;
			}
		}
		if (prevLastOccurence)
		{
			DeleteNext(prevLastOccurence);
		}
	}

	//arrange odd and even positions by taking odd positions to the begining
	void ArrangeOddEven()
	{
		if (length < 3) { return; }

		int i = 2;
		for (Node<T>* prev = head, *current = head->next; current; ++i)
		{
			if (i % 2 == 1)
			{
				prev->next = current->next;
				current->next = head->next;
				head->next = current;
				current = prev->next;
			}
			else
			{
				prev = current;
				current = current->next;
			}
		}
	}
	//it will modify the original linked list such that linkedlist 2 items will be added alternativly
	void InsertAlternate(const LinkedList & linkedList2)
	{
		if (linkedList2.length == 0) return;
		int minIndex = std::min(length, linkedList2.length);
		int maxIndex = std::max(length, linkedList2.length);
		int realIndex = linkedList2.length > minIndex ? maxIndex : minIndex;

		Node<T>* current = head;
		Node<T>* secondCurrent = linkedList2.GetHead();
		Node<T>* newNode = nullptr;
		for (int i = 0; i < realIndex; secondCurrent = secondCurrent->next,++i)
		{
			newNode = new Node<T>(secondCurrent->data);
			if (i < minIndex)
			{
				newNode->next = current->next;
				current->next = newNode;
				//update pos
				current = newNode->next;
			}
			else
			{
				this->InsertEnd(newNode->data);
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
	list.InsertEnd(8);
	list.InsertEnd(15);
	list.InsertFront(11);
	list.InsertEnd(8);
	list.InsertEnd(8);
	list.Print();

	LinkedList<int> sortedList;
	sortedList.InsertSorted(10);
	sortedList.InsertSorted(2);
	sortedList.InsertSorted(30);
	sortedList.InsertSorted(4);
	sortedList.InsertSorted(1);
	sortedList.Print();

	list.InsertAlternate(sortedList);
	list.Print();








	/*
	//list.MoveBack(8);
	list.Print();
	std::println("max is: {}", list.FindMax(list.GetHead()));
	list.ArrangeOddEven();
	list.Print();
	*/


	/*
	* 	list.RemoveLastOccurence(25);
	list.Print();
	std::println("{}", list.Get_nth(3)->data);
	std::println("{}", list.Get_nth_Back(1)->data);
	std::println("{}", list.Get_nth_Back(3)->data);
	list.DeleteEvenPositions();
	list.Print();
	*/






	/*
	* 	sortedList.LeftRotate(1);
	sortedList.Print();
	sortedList.SwapHeadTail();
	sortedList.Print();
	
	list.Reverse();
	list.Print();
	list.DeleteFront();
	list.Print();
	list.SwapPairs();
	list.Print();
	list.DeleteEnd();
	list.Print();
	list.Delete_nth(3);
	list.Print();
	list.DeleteKey(25);
	list.Print();
	*/
}