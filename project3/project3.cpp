#include<iostream>
#include<cstdlib> // used for random number generation
#include<math.h> // used for ceil and floor functions in adaptive sort
#include<ctime> // used for measuring time

using namespace std;

void swap(int* x, int* y); //For swapping elements of array
int partition(int* ele, int low, int high); //For partitionaing array in quick sort

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
	void quickSort(sortElements& se, int low, int high);
	void shellSort(); 
	// - Extra credit � Shell and Adaptive sort methods
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

void sortElements::quickSort(sortElements& se, int low, int high)
{
	if (low < high)
	{
		int p = partition(elements, low, high); //Partition the array

		// Separately sort elements before  
		// partition and after partition  
		quickSort(se, low, p - 1);
		quickSort(se, p + 1, high);
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


int main() {

	sortElements* a = new sortElements(5);
	a->generateRandom(1, 0, 20);

	(*a).displayElements();

	(*a).shellSort();

	(*a).displayElements();

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