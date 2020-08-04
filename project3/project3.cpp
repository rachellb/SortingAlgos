#include<iostream>
#include<cstdlib> // used for random number generation
#include<math.h> // used for ceil and floor functions in adaptive sort
#include<ctime> // used for measuring time

using namespace std;

class sortElements {

	friend ostream& operator<< (ostream& s, sortElements& ele);

protected:
	int numElements; //Number of elements of the array
	int* elements; //dynamic array with the elements of type int
public:
	sortElements(); // default constructor
	sortElements(int n); // non-default constructor
	~sortElements(); // destructor
	void generateRandom(int seed, int lower, int upper); // will generate
	void displayElements(int* arr); // display the given set
	int* getElementsArray(); // return the entire array of elements
	int getnumElements(); // return the number of elements
	// Necessary methods for each of the sorting algorithm
	// - Bubble and Quick sort methods
	// - Extra credit – Shell and Adaptive sort methods
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

ostream& operator << (ostream& s, sortElements& ele) { //This line taken from pg 146 of book

	for (int i = 0; i < ele.numElements; i++)
	{
		if (i > 0)
		{
			s << ' '; //Prints a space between all elements, but not before first
		}
		s << ele.elements[i]; //Prints the given element
	}
	s << endl; //Ends with an endline

	return s;
}

int main() {

	sortElements* a = new sortElements(5);
	a->generateRandom(1, 0, 20);

	cout << *a;

	return 0;
}