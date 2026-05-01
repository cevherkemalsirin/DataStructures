#include <iostream>
#include <initializer_list>

template<class T>
class myVector {
private:
	int _size;
	int _capacity;
	T* _array;

	void ExpandCapacity()
	{
		_capacity *= 2;
		T* temp = new T[_capacity];
		for (int i = 0; i < _size; ++i)
		{
			temp[i] = _array[i];
		}
		delete[] _array;
		_array = temp;
		temp = nullptr;
	}

public:
	myVector()
	{
		_size = 0;
		T* _array = nullptr;
	}
	myVector(int size) : _size(size)
	{
		if (size < 0) _size = 1;

		_capacity = _size * 2;
		T* array = new T[_capacity]{};
	}

	myVector(const std::initializer_list<T> list):_size(static_cast<int>(list.size()))
	{
		if (_size <= 0) _size = 1;

		_capacity = _size * 2;
		_array = new T[_capacity]{};
		int i = 0;
		for (const auto& item : list)
		{
			if (i < _size)
			{
				_array[i++] = item;
			}
			
	    }
	}

	void Set(int index, const T& value)
	{
		if (index < 0 || index >= _size) return;

		_array[index] = value;
	}

	T Get(int index)
	{
		if (index < 0 || index >= _size) return;

		return _array[index];
	}

	int Find(const T& value)
	{
		for (int i = 0; i < _size; ++i)
		{
			if (_array[i] == value)
			{
				return i;
			}
		}
	}

	int Find_Tranportation(const T& value)
	{
		int index = Find(value);
		if (index > 0)
		{
			T temp = _array[index];
			_array[index] = _array[index - 1];
			_array[index - 1] = temp;
			--index;
		}
		return index;

	}

	void Insert(int index, const T& value)
	{
		if (index < 0 || index >= _size) return;

		if (_size == _capacity)
		{
			ExpandCapacity();
		}

		for (int i = _size - 1; i >= index; --i)
		{
			_array[i + 1] = _array[i];
		}

		_array[index] = value;
		++_size;
		
	}

	void Push_Back(const T& value)
	{
		if (_size < _capacity)
		{
			_array[_size++] = value;
	    }
		else
		{
			ExpandCapacity();
			_array[_size++] = value;
		}
	}

	void RightRotate()
	{
		T temp = _array[_size - 1];
		for (int i = _size - 2; i >= 0; --i)
		{
			_array[i + 1] = _array[i];
		}
		_array[0] = temp;
	}

	void RightRotate(int times)
	{
		times %= _size;

		for (int i = 0; i < times; ++i)
		{
			RightRotate();
		}
	}

	void LeftRotate()
	{
		T temp = _array[0];
		for (int i = 0; i <= _size - 2; ++i)
		{
			_array[i] = _array[i + 1];
		}
		_array[_size - 1] = temp;

	}

	T Pop(int index)
	{
		T temp = _array[index];
		for (int i = index; i < _size - 1; ++i)
		{
			_array[i] = _array[i + 1];
		}
		--_size;
		return temp;
	}

	void Print()
	{
		for (int i = 0; i < _size; ++i)
		{
			std::cout << _array[i] << " ";
		}
	}

	T GetFront()
	{
		return _array[0];
	}
	
	T GetBack()
	{
		return _array[_size - 1];
	}

	~myVector()
	{
		delete[] _array;
		_array = nullptr;
	}
};



//questions, 5 medium challanges:

//add right rotate 1 2 3 4 - > 4 1 2 3
//add left rotate
//add pop


int main1()
{
	return 0;
	myVector<int> a = { 1,2,3,4,5 };
	a.Print();
	a.RightRotate();
	std::cout << std::endl;
	a.Print();
	a.LeftRotate();
	std::cout << std::endl;
	a.Print();
	a.RightRotate(38);
	std::cout << std::endl;
	a.Print();
	std::cout << std::endl;
	std::cout << a.Pop(2)<<std::endl;
	a.Print();
}