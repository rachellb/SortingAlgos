#include<iostream>
#include<cstdlib> // used for random number generation
#include<math.h> // used for ceil and floor functions in adaptive sort
#include<ctime> // used for measuring time

using namespace std;

class sortElements {
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