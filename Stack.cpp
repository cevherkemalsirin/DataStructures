#pragma once
#include <iostream>
#include <array>
#include <unordered_map>
#include <algorithm>


template<class T>
struct Node
{
	T value{};
	Node* next{};
	
	~Node()
	{
		if (next)
		{
			delete next;
		}
	}
};

template <class T>
class StackLL
{
	Node<T>* _head;
	uint32_t _size;
public:
	StackLL():_head{nullptr}, _size{0}
	{
		
	}

	inline uint32_t size() const { return _size; }

	bool isEmpty() const
	{
		return _size == 0;
	}

	void push(const T & item)
	{
		Node<T>* temp = new Node<T>{ item, nullptr };
		temp->next = _head;
		_head = temp;
		++_size;
	}

	T pop()
	{
		if (_size == 0 || !_head) return 0;
		else
		{
			Node<T>* temp = _head;
			_head = _head->next;
			T value = temp->value;
			temp->next = nullptr;
			delete temp;
			--_size;
			return value;
		}
	}

	T top() const
	{
		if(_head)
			return _head->value;
		return 0;
	}

	friend std::ostream& operator<<( std::ostream& out, const StackLL<T>& sll)
	{
		for (Node<T>* p = sll._head; p; p = p->next)
		{
			out << p->value << " ";
	    }
		return out;
	}

	~StackLL()
	{
		if(_head)
			delete _head;

	}
};


template <class T>
class Stack
{
private:
	unsigned int _size{};
	unsigned int _capacity{};
	const unsigned int DEFAULT_CAP{ 50 };
	T* _Tarr;

	void Change_Capacity(bool increase = true)
	{
		if (increase)
		{
			_capacity *= 2;
		}
		else
		{
			_capacity /= 2;
		}
		if (_capacity < _size) throw;

		T* temp = new T[_capacity]{};
		
		for (unsigned int i = 0; i < _size; i++)
		{
			temp[i] = _Tarr[i];
		}


		delete[] _Tarr;
		_Tarr = temp;
	}

public:
	Stack() :_size(0)
	{
		_capacity = DEFAULT_CAP;
		_Tarr = new T[_capacity]{};
	}
	Stack(unsigned int cap) :_size{ 0 }, _capacity{ cap }
	{
		_Tarr = new T[_capacity]{};
	}

	void push(T item)
	{
		if (_size == _capacity)
		{
			Change_Capacity();
		}
		_Tarr[_size++] = item;
	}

	T pop()
	{
		if (_size > 0)
		{
			if (_capacity > _size * 4)
			{
				Change_Capacity(false);
			}
			return _Tarr[--_size];
		}
		else
		{
			return T{};
		}
	}

	bool isEmpty() const
	{
		return _size == 0;
	}

	T Top() const
	{
		if (_size > 0)
			return _Tarr[_size - 1];
	}

	unsigned int size() const
	{
		return _size;
	}

	friend std::ostream& operator<<(std::ostream& out, const Stack <T>& s)
	{
		for (int i = 0; i < s.size(); ++i)
		{
			out << s._Tarr[i] << " ";
		}
		out << '\n';
		return out;
	}

	~Stack()
	{
		if (_Tarr)
		{
			delete[] _Tarr;
			_Tarr = nullptr;
		}
	}
};




bool isBalancedParentheses(const std::string& str)
{
	std::unordered_map<char, char> parenthesesMap{ {'(',')'},{'{','}'},{'[',']'} };

	Stack<char> pStack;

	for (const char& c : str)
	{

		if (parenthesesMap.find(c) != parenthesesMap.end())
		{
			pStack.push(c);
		}
		else if (!pStack.isEmpty() && parenthesesMap[pStack.Top()] == c)
		{
			pStack.pop();
		}
		else
		{
			return false;
		}

	}
	return pStack.isEmpty(); // what if only one left parenthesis is present

}


std::pair<unsigned int, unsigned int> GetPrecedence(char op);

//  ((a+b)*c)-d^e^f
//ab+c*def^^-
std::string InfixToPostfix(const std::string& infix)
{
	Stack<char> opStack;
	std::string postfix;
	for (const char& c : infix)
	{
		if (c == ' ') continue;
		if (std::isalnum(c))
		{
			postfix += c;
		}
		else if (GetPrecedence(c).first >= 0)
		{
			if (opStack.isEmpty())
			{
				opStack.push(c);
		    }
			else
			{
				if (GetPrecedence(c).first < GetPrecedence(opStack.Top()).second)
				{
					while (!opStack.isEmpty() && GetPrecedence(c).first < GetPrecedence(opStack.Top()).second)
					{
						postfix += opStack.pop();
					}
					if (!opStack.isEmpty() && GetPrecedence(c).first == GetPrecedence(opStack.Top()).second)
					{
						opStack.pop();
					}
					else
					{
						opStack.push(c);
					}
				}
				else if (GetPrecedence(c).first == GetPrecedence(opStack.Top()).second)
				{
					opStack.pop(); //this is only if (  ) happens.
				}
				else
				{
					opStack.push(c);
				}

			}
		}
	}

	while (!opStack.isEmpty())
	{
		postfix += opStack.pop();
	}

	return postfix;
}

std::pair<unsigned int, unsigned int> GetPrecedence(char op)
{
	if (op == '+' || op == '-')
		return { 1, 2 };
	else if (op == '*' || op == '/')
		return { 3, 4 };
	else if (op == '^')
		return { 6, 5 };
	else if (op == '(')
		return { 7, 0 };
	else if (op == ')')
		return { 0, -1 };
	else
		return { -1,-1 }; // invalid operator
}


bool IsOperator(char c)
{
	return c == '+' || c == '-' || c == '*' || c == '/' || c == '^';
}

int EvaluatePostfix(const std::string& postfix)
{
	//"35*62/+4-";
	Stack<int> s{};
	for (const char& c : postfix)
	{
		if (std::isdigit(c))
		{
			s.push(c - '0');
		}
		else if (IsOperator(c))
		{
			if (s.size() >= 2)
			{
				int b = s.pop();
				int a = s.pop();
				s.push([a, b, c]() ->int {
					
					switch (c)
					{
					case '+':
						return a + b;
						break;
					case '-':
						return a - b;
						break;
					case '*':
						return a * b;
						break;
					case '/': 
						if( b != 0) return a / b;
						else throw std::runtime_error("Division By Zero");
						break;
					case '^':
						return pow(a,b);
						break;
					default:
						throw std::invalid_argument("Invalid Operator");
						break;
					}
					}());
			}
		}

	}
	if (s.size() == 1) return s.Top();
	else
		return -1;
	
}



std::string RemoveAllAdj(const std::string& str)
{
	Stack <char> s{};
	std::string newText{};
	for (const auto& c : str)
	{
		if (s.isEmpty())
		{
			s.push(c);
		}
		else
		{
			if (s.Top() == c)
			{
				s.pop();
			}
			else
			{
				s.push(c);
			}
		}
	}
	while (!s.isEmpty())
	{
		newText += s.pop();
	}
	std::reverse(newText.begin(), newText.end());
	return newText;
}


int main_stack()
{
	return 0;
	Stack<int> s{};
	s.push(10);
	s.push(20);
	s.push(30);
	s.pop();
	std::cout << s.pop() << " is popped " << std::endl;
	std::cout << s << std::endl;
	StackLL<int> sll{};
	sll.push(100);
	sll.push(110);
	sll.push(120);
	std::cout << sll << std::endl;
	//std::cout << sll.pop() << std::endl;
	//std::cout << sll << std::endl;
	//sll.pop();
	//sll.pop();
	std::cout << sll.size() << " here is the size" << std::endl;

	std::cout << "------------------------ \n \n ";
	/*std::string text{};

	for (;;)
	{

		std::cin >> text;

		if (isBalancedParentheses(text))
		{
			std::cout << "Balanced \n";
		}
		else
		{
			std::cout << "Not Balanced \n";
		}

	}
	*/

	std::string text = "((a + b) * c) - d ^ e ^ f";
	std::string text2 = "3 * 5 + 6 / 2 - 4";
	std::cout << InfixToPostfix(text)<<"\n";
	std::cout << InfixToPostfix(text2)<< "\n";
	std::cout << "------------------------ \n \n ";

	std::string postfixT = "35*62/+4-";
	std::cout << EvaluatePostfix(postfixT)<<"\n";

	std::cout << "------------------------ \n \n ";

	while (true)
	{
		std::cout << "Please enter a text to remove adjcesent: " << std::endl;
		std::string text;
		std::cin >> text;
		std::cout << RemoveAllAdj(text) << "\n";
	}

}

