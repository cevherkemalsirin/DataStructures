#include <iostream>
#include <print>
#include <algorithm>


int Fibonacci(int n)
{
	if (n <= 0) return 0;
	if (n == 1) return 1;

	return Fibonacci(n - 1) + Fibonacci(n - 2);
}

int FibonacciNR(int n)
{
	int firstNum{ 0 };
	int secondNum{ 1 };
	int result{1};
	for (int i = 1; i < n; ++i)
	{
		result = firstNum + secondNum;
		firstNum = secondNum;
		secondNum = result;
	}
	return result;
}

int Power(int n, int p)
{
	if (p == 0) return 1;

	return n * Power(n, p - 1);
}

int PowerNR(int n, int p)
{
	int result{ 1 };
	for (int i = 0; i < p; ++i)
	{
		result *= n;
	}
	return result;
}

void PrintUntilN(int n)
{
	if (n <= 0) return;

	PrintUntilN(n - 1);
	std::print("{} ", n);
}

int CountDigits(int n)
{
	if (n == 0) return 0;

	return 1 + CountDigits(n / 10);

}

int SumDigits(int n)
{
	if (n == 0) return 0;

	int digit = n % 10;
	return digit + SumDigits(n / 10);
}

int CountZeroes(int n)
{
	if (n == 0) return 0;

	if ((n % 10) == 0) return 1 + CountZeroes(n / 10);
	else
		return 0 + CountZeroes(n / 10);
}

float GeometricSum(int n)
{
	if (n <= 0) return 1;
	return 1.0f / std::pow(2, n) + GeometricSum(n - 1);
}


bool IsSorted(int* arr, int n)
{
	if (n == 0 || n == 1) return true;

	return arr[n-1] > arr[n - 2] && IsSorted(arr, n - 1);
	
}


int SumArray(int* arr, int n)
{
	if (n == 0) return 0;

	return arr[n - 1] + SumArray(arr, n - 1);
}


bool HasElement(int* arr, int n ,int key)
{
	if (n == 0) return false;

	return  key == arr[0] || HasElement(arr + 1, n - 1, key);
}

int FindFirstIndex(int* arr, int n, int key, int i = 0)
{
	if (i == n) return -1;

	if (arr[i] == key) return i;

	FindFirstIndex(arr, n, key, i + 1);
}

int FindLastIndex(int* arr, int n, int key)
{
	if (n == 0) return -1;

	if (arr[n - 1] == key) return n - 1;
	else
	{
		FindLastIndex(arr, n - 1, key);
	}

}

void PrintAllIndex(int* arr, int n, int key)
{
	if (n == 0) return;

	if (arr[n - 1] == key)std::print("{} ", n - 1);

	PrintAllIndex(arr, n - 1, key);

}

int CountOccurences(int* arr, int n, int key)
{
	if (n == 0) return 0;

	if (arr[n - 1] == key) return 1 + CountOccurences(arr, n - 1, key);

	CountOccurences(arr, n - 1, key);
}

bool isPalindrome(int* arr, int n, int i = 0)
{
	if (i >= n-1) return true;

	if (arr[i] != arr[n - 1]) return false;
	else
	{
		isPalindrome(arr, n - 1, i + 1);
	}
}

void PrintChar(char* arr,bool reverse = true,int i = 0)
{
	if (arr[i] == '\0')
	{
		std::println();
		return;
	}

	if(reverse)std::print("{} ", arr[i]);
	PrintChar(arr,reverse,i + 1);
	if(!reverse)std::print("{} ", arr[i]);
}


void ChangeChar(char* arr, char oldChar, char newChar)
{
	if (arr[0] == '0') return;

	if (arr[0] == oldChar)
	{
		arr[0] = newChar;
	}
	ChangeChar(arr + 1, oldChar, newChar);
}

void RemoveConsecDup(char* arr)
{
	if (arr[0] == '\0') return;

	if (arr[0] == arr[1])
	{
		for (int i = 0; arr[i] != '\0'; ++i)
		{
			arr[i] = arr[i + 1];
	    }
		RemoveConsecDup(arr);
	}
	else
	{
		RemoveConsecDup(arr + 1);
	}

}

void PrintAllSubseq(char* arr)
{
	if (arr[0] == '\0') return;

	//std::print("{} " PrintAllSubseq());
}

int main99()
{
	return 0;
	int n; std::cin >> n;
	//std::println("Fibonacci number {} : {}", n, FibonacciNR(n));
	//int p; std::cin >> p;
	//std::println("Power number {} : {}", n, Power(n,p));
	//PrintUntilN(n);
	//std::print("total number of digits for {} is : {}",n,CountDigits(n));
	//std::print("sum of digits for {} is : {}", n, SumDigits(n));
	//std::print("sum of 0 digits for {} is : {}", n, CountZeroes(n));
	//std::print("geo sum for {} is : {}", n, GeometricSum(n));
	int arr[] = {1,3,2,3,4,6,3,2,3,1};
	//std::print("this array is {}", IsSorted(arr, 7) ? "Sorted!" : "Not Sorted!");
	//std::print("Sum of array is {}", SumArray(arr, 7));
	//std::println("this array {} key {}", HasElement(arr, 7, 5) ? " has " : "has not ", 5);
	//std::println("this array {} key {}", HasElement(arr, 7, 31) ? " has " : "has not ", 31);
	//std::println("First index of key {} is {}", 3, FindLastIndex(arr,8,31));
	//PrintAllIndex(arr, 8, 0);
	//std::println("Occurence of key {} is {} times", 3, CountOccurences(arr,11,3));
	//std::println("this array is {}", isPalindrome(arr, 10) ? "palindrome." : "not palindrome.");
	char carr[] = "aabbbcdda";
	//PrintChar(carr);
	//PrintChar(carr, false);
	//ChangeChar(carr,'e', 'a');
	//std::println("{}",carr);
	RemoveConsecDup(carr);
	std::println("{} ",carr);

}