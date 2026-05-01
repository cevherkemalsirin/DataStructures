#include <iostream>
#include <print>
#include <array>

const int size = 10;

void SelectionSort(std::array<int,size>& arr)
{
	for (size_t i = 0; i <= arr.size() - 2; ++i)
	{
		int min{ INT_MAX };
		int minIndex{};
		for (size_t j = i + 1; j < arr.size(); ++j)
		{
			if (arr[j] < min)
			{
				min = arr[j];
				minIndex = j;
			}
		}
		if (min < arr[i])
		{	
			std::swap(arr[i], arr[minIndex]);
	    }
	}


}

void BubbleSort(std::array<int, size>& arr)
{
	for (size_t i = 0; i < arr.size()-1; ++i)
	{
		bool noSwap = true; // if no need to swap then it is already sorted
		for (size_t j = 0; j < arr.size() - 1; ++j)
		{
			if (arr[j] > arr[j + 1])
			{
				std::swap(arr[j], arr[j + 1]);
				noSwap = false;
			}

		}
		if (noSwap) break;
	} 

}

bool IsSorted(const std::array<int, size>& arr)
{
	for (size_t i = 0; i < arr.size() - 1; ++i)
	{
		if (arr[i] > arr[i + 1])
		{
			return false;
		}
	}
	return true;
}

//binary search, list needs to be sorted 

int BinarySearch(int key, const std::array<int, size>& arr)  // 0 1 2 3 4 5 6
{
	if (!IsSorted(arr)) return -1;

	int endPoint = arr.size() - 1;
	int startPoint = 0;
	while (startPoint <= endPoint)
	{
		int midPoint = (endPoint + startPoint) / 2;
		
		if (arr[midPoint] == key) return midPoint;

		arr[midPoint] < key ? startPoint = midPoint + 1 : endPoint = midPoint - 1;

	}

	return -1;

}













int Sortingmain()
{
	return 0;
	std::array<int, size> arr{ 32,12,11,120,3,1,43,25,86,19 };
	//SelectionSort(arr);
	BubbleSort(arr);
	for (const auto& a : arr)
	{
		std::print("{} ", a);
	}

	std::println("key is: {}", BinarySearch(120, arr));
	std::println("key is: {}", BinarySearch(32, arr));
	std::println("key is: {}", BinarySearch(86, arr));
	std::println("key is: {}", BinarySearch(122, arr));
	std::println("key is: {}", BinarySearch(1, arr));
	std::println("key is: {}", BinarySearch(22, arr));
}