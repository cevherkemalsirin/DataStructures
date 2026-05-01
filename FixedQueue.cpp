#pragma once
#include <iostream>
#include <print>

//circular array implementation of queue
template <class T, unsigned int CAP>
class CircularQueue
{
	int _frontIndex{ 0 };
	int _endIndex{ -1 };
	unsigned int _size{ 0 };
	T _Tarr[CAP]{};

public:
	CircularQueue() = default;
	CircularQueue(T val, unsigned int times)
	{
		if (times >= CAP)
		{
			times = CAP;
		}

		for (size_t i = 0; i < times; ++i)
		{
			_Tarr[i] = val;
		}
		_size = times;
		_frontIndex = 0;
		_endIndex = times ? times - 1 : -1;

	}

	void push(T val)
	{
		if (_size >= CAP)
		{
			std::println("Error ({}) size is larger than the ({}) capacity", _size, CAP);
			return;
		}

		_endIndex = (_endIndex + 1) % CAP;
		_size++;
		_Tarr[_endIndex] = val;
	}

	T pop()
	{
		if (_size > 0)
		{
			T value = _Tarr[_frontIndex];
			_frontIndex = (_frontIndex + 1) % CAP;
			if (_size == 1)
			{
				_endIndex = -1;
				_frontIndex = 0;
			}
			--_size;
			return value;
		}
		else
		{
			std::println("Error ({}) size which means empty, front index is {} ", _size, _frontIndex);
			return {};
		}
	}

	friend std::ostream& operator<<(std::ostream& out, const CircularQueue& q)
	{
		if (q._size == 0) {
			out << "[empty]";
			return out;
		}
		for (unsigned int i = 0, idx = q._frontIndex; i < q._size; ++i, idx = (idx + 1) % CAP) {
			out << q._Tarr[idx];
			if (i != q._size - 1)
				out << " ";
		}
		return out;
	}

	unsigned int Size()const
	{
		return _size;
	}

	bool IsEmpty() const
	{
		return _size == 0;
	}

	T Front() const
	{
		if (_size > 0)
		{
			return _Tarr[_frontIndex];
		}
		return {};
	}


};

//do later
/*
template <class T, unsigned int CAP>
class DynamicQueue
{
	int _frontIndex{ 0 };
	int _endIndex{ -1 };
	unsigned int _size{ 0 };
	T* _Tarr;

public:
	DynamicQueue() = default;
	DynamicQueue(T val, unsigned int times)
	{
		if (times >= CAP)
		{
			times = CAP;
		}

		for (size_t i = 0; i < times; ++i)
		{
			_Tarr[i] = val;
		}
		_size = times;
		_frontIndex = 0;
		_endIndex = times ? times - 1 : -1;

	}

	void push(T val)
	{
		if (_size >= CAP)
		{
			std::println("Error ({}) size is larger than the ({}) capacity", _size, CAP);
			return;
		}

		_endIndex = (_endIndex + 1) % CAP;
		_size++;
		_Tarr[_endIndex] = val;
	}

	T pop()
	{
		if (_size > 0)
		{
			T value = _Tarr[_frontIndex];
			_frontIndex = (_frontIndex + 1) % CAP;
			if (_size == 1)
			{
				_endIndex = -1;
				_frontIndex = 0;
			}
			--_size;
			return value;
		}
		else
		{
			std::println("Error ({}) size which means empty, front index is {} ", _size, _frontIndex);
			return {};
		}
	}

	friend std::ostream& operator<<(std::ostream& out, const DynamicQueue& q)
	{
		if (q._size == 0) {
			out << "[empty]";
			return out;
		}
		for (unsigned int i = 0, idx = q._frontIndex; i < q._size; ++i, idx = (idx + 1) % CAP) {
			out << q._Tarr[idx];
			if (i != q._size - 1)
				out << " ";
		}
		return out;
	}

	unsigned int Size()const
	{
		return _size;
	}

	bool IsEmpty() const
	{
		return _size == 0;
	}

	T Front() const
	{
		if (_size > 0)
		{
			return _Tarr[_frontIndex];
		}
		return {};
	}


};

*/

template<class T>
class LLqueue {

	struct Node {
		T _val{};
		Node* _next{};
		Node(T val, Node* next = nullptr):_val(val), _next(next) {}

		~Node()
		{
			if (_next)
			{
				delete _next;
			}
	    }
	};

	Node* _head{};
	Node* _tail{};
	unsigned int _size{};
public:
	LLqueue() = default;
	LLqueue(T headVal) : _size(1)
	{
		Node* newHead = new Node{ headVal, nullptr };
		_head = newHead;
		_tail = newHead;
	}


	void push(T val)
	{
		Node* newNode = new Node{ val, nullptr };
		if (_tail)
		{
			_tail->_next = newNode;
			_tail = newNode;

		}
		else
		{
			_head = _tail = newNode;
		}
		++_size;

	}


	T pop()
	{
		if (_head)
		{
			T value = _head->_val;
			Node* temp = _head;
			_head = _head->_next;
			temp->_next = nullptr;
			delete temp;
			_size--;
			if (_size == 0) _tail = nullptr;
			return value;
	    }
		else
		{
			std::println("The queue is empty!");
			return {};
		}
	}


	bool isEmpty() const { return _size == 0; }


	unsigned int size() const { return _size; }


	T front() const
	{
		if (_head) return _head->_val;
		
		std::println("Empty Queue ! no front ");
		return {};
	}


	friend std::ostream& operator<<( std::ostream& out, const LLqueue& llq)
	{
		LLqueue::Node* curr = llq._head;
		while(curr)
		{
			out << curr->_val << " ";
			curr = curr->_next;
	   }
		out << std::endl;
		return out;
	}


	~LLqueue()
	{
		if (_head) delete _head;
		_head = nullptr;
	}


};




int mainQueue()
{
	return 0;
	LLqueue<int> llq;
	int choice;
	while (true) {
		std::cout << "Enter 1 to push, 2 to pop, 3 to exit: ";
		std::cin >> choice;
		if (choice == 1) {
			int val;
			std::cout << "Enter value to push: ";
			std::cin >> val;
			llq.push(val);
			std::cout << "Queue: " << llq << std::endl;
		}
		else if (choice == 2) {
			if (!llq.isEmpty()) {
				int popped = llq.pop();
				std::cout << "Popped: " << popped << std::endl;
			}
			else {
				std::cout << "Queue is empty, cannot pop." << std::endl;
			}
		}
		else if (choice == 3) {
			break;
		}
		else if (choice == 4)
		{
			std::cout << "Queue size is : " << llq.size() << std::endl;
		}
		else if (choice == 5)
		{
			std::cout << "Queue front is : " << llq.front() << std::endl;
		}
		else if (choice == 6)
		{
			std::cout << "Queue: " << llq << std::endl;
		}
		else {
			std::cout << "Invalid choice. Try again." << std::endl;
			break;
		}
	}

	/*
	CircularQueue<int, 5> q;
	int choice;
	while (true) {
		std::cout << "Enter 1 to push, 2 to pop, 3 to exit: ";
		std::cin >> choice;
		if (choice == 1) {
			int val;
			std::cout << "Enter value to push: ";
			std::cin >> val;
			q.push(val);
			std::cout << "Queue: " << q << std::endl;
		}
		else if (choice == 2) {
			if (!q.IsEmpty()) {
				int popped = q.pop();
				std::cout << "Popped: " << popped << std::endl;
			}
			else {
				q.pop();
				std::cout << "Queue is empty, cannot pop." << std::endl;
			}
			std::cout << "Queue: " << q << std::endl;
		}
		else if (choice == 3) {
			break;
		}
		else {
			std::cout << "Invalid choice. Try again." << std::endl;
		}
	}
	*/
}