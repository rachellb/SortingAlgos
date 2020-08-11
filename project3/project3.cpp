#include<iostream>
#include<cstdlib> // used for random number generation
#include<math.h> // used for ceil and floor functions in adaptive sort
#include<ctime> // used for measuring time

using namespace std;

void swap(int* x, int* y); //For swapping elements of array
int partition(int* ele, int low, int high); //For partitionaing array in quick sort
bool isSorted(int* se, int n); //For adaptive sort
int* merge(int* a, int an, int* b, int bn); //Also for adaptive sort

class sortElements {

protected:
	int numElements; //Number of elements of the array
	int* elements; //dynamic array with the elements of type int

public:
	sortElements(); // default constructor
	sortElements(int n); // non-default constructor
	~sortElements(); // destructor
	void generateRandom(int seed, int lower, int upper); // will generate
	void displayElements(); // display the given set
	int* getElementsArray(); // return the entire array of elements
	int getnumElements(); // return the number of elements
	void bubbleSort();
	void quickSort(int low, int high);
	void shellSort(); 
	int* adaptiveSort(int* li, int n);
};

sortElements::sortElements() {
	numElements = 0;
	elements = new int[1];
}

sortElements::sortElements(int n) {
	numElements = n;
	elements = new int[n];
}

sortElements::~sortElements() {
	if (elements != NULL) delete[] elements;
	elements = NULL;
	numElements = 0;
}

void sortElements::generateRandom(int seed, int lower, int upper) {
	srand(seed); //Sets the seed for the random number generator
	
	for (int i = 0; i < numElements; i++) {
		elements[i] = (rand() % upper) + lower; //Generate random number between upper and lower and fill array
	}
}


void sortElements::displayElements() {
	for (int i = 0; i < numElements; i++) {
		if (i > 0)
		{
			cout << ' '; //Prints a space between all elements, but not before first
		}
		cout << elements[i]; //Prints the given element
	}
	cout << endl;
}

int* sortElements::getElementsArray() {
	return elements;
}

int sortElements::getnumElements() {
	return numElements;
}

void sortElements::bubbleSort()
{
	int i, j;
	for (i = 0; i < numElements -1; i++)

		// Last i elements are already in place  
		for (j = 0; j < numElements - i - 1; j++)
			if (elements[j] > elements[j + 1])
				swap(&elements[j], &elements[j + 1]);
}

void sortElements::quickSort(int low, int high) //I could put the list, but since it's a method of sortElements I don't think I need to
{
	if (low < high)
	{
		int p = partition(elements, low, high); //Partition the array

		// Separately sort elements before  
		// partition and after partition  
		quickSort(low, p - 1);
		quickSort(p + 1, high);
	}
}


void sortElements::shellSort() {
	
	for (int inc = 0; inc < numElements; inc++) {
		int dist;
		int j;
		dist = elements[inc];
		for (int i = dist; i < numElements; i++) {
			int item = elements[i];
			j = i - dist;
			while ((j >= 0) && (elements[j] > item)) {
				elements[j + dist] = elements[j];
				j = j - dist;
			}
			elements[j + dist] = item;
		}

	}
}


int* sortElements::adaptiveSort(int* li, int n) { //Now returns the list
	
	if (n < 2) return li; //If only one, it's already sorted

	//Split step
	
	int esize = int(ceil(double(n) / 2.0));
	int osize = int(floor(double(n) / 2.0));

	int* evens = new int(esize);
	int* odds = new int(osize);

	int lim = n / 2;
	for (int i = 0, i2 = 0; i < lim; i++, i2++) {
		evens[i] = li[i2]; //This needs a star here, why isn't there one?
		i2++; //?
		odds[i] = li[i2];
	}
	if (n % 2 > 0) {
		evens[esize - 1] = li[n - 1];
	}

	//Recursive step
	if (!isSorted(evens, esize)) evens = adaptiveSort(evens, esize); //Originally 1 14 9 
	if (!isSorted(odds, osize)) odds = adaptiveSort(odds, osize); // Originally 7 0
	li = merge(evens, esize, odds, osize);
	
	return li;
	//delete evens;
	//delete odds;
}


int main() {

	sortElements* a = new sortElements(5);
	a->generateRandom(1, 0, 20);	
	
	(*a).displayElements();

	int* mySort = (*a).adaptiveSort((*a).getElementsArray(), (*a).getnumElements());
	

	for (int i = 0; i < (*a).getnumElements(); i++) {
		if (i > 0)
		{
			cout << ' '; //Prints a space between all elements, but not before first
		}
		cout << mySort[i]; //Prints the given element
	}
	cout << endl;

	return 0;
}

void swap(int* x, int* y)
{
	int temp = *x;
	*x = *y;
	*y = temp;
}

int partition(int* ele, int low, int high)
{
	int pivot = ele[high]; // pivot  
	int i = (low - 1); // Index of smaller element  

	for (int j = low; j <= high - 1; j++)
	{
		// If current element is smaller than the pivot  
		if (ele[j] < pivot)
		{
			i++; // increment index of smaller element  
			swap(&ele[i], &ele[j]);
		}
	}
	swap(&ele[i + 1], &ele[high]);
	return (i + 1);
}


bool isSorted(int* li, int n) {
	if (n < 2) return true;
	int prev = li[0];
	for (int i = 1; i < n; i++) {
		
		if (prev <= li[i]) {
			prev = li[i];
		}
		
		else {
			return false;
		}
	}
	return true;
}

int* merge(int* a, int an, int* b, int bn) {
	
	int* c = new int[an + bn];

	int i = 0, j = 0, k = 0;
	
	while ((i < an) && (j < bn)) {
		if (a[i] <= b[j]) {
			c[k++] = a[i++];
		}
		else { 
			c[k++] = b[j++];
		}
	}
	while (i < an) {
		c[k++] = a[i++];
	}
	while (j < bn) {
		c[k++] = b[j++];
	}

	return c; //c is a pointer, merge returns a pointer to this location, so should be the sorted array
}