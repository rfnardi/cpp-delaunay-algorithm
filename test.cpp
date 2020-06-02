#include <iostream>
#include <algorithm>
using namespace std;

int main()
{
	int arr[ 5 ] = { 6, 3, 5, 2, 8 };
	int elem = 2;
	int* itr = find(arr, arr + 5, elem);

	if (itr != end(arr)) {
		cout << "Element " << elem << " is present at index "
			<< distance(arr, itr) << " in the given array";
	}
	else {
		cout << "Element is not present in the given array";
	}

	return 0;
}