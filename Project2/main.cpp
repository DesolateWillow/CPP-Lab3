#include <iostream>
#include <vector>
#include <string>


void myInit(std::vector<short>& vector) {
	for (size_t i = 0; i < vector.size(); i++)
		vector.at(i) = rand() % 101;
}
void printVector(const std::vector<short>& vector) {
	for (short i : vector) std::cout << i << ' ';
	std::cout << '\n';
}
std::vector<short>& bubbleSort(std::vector<short>& vector) {
	for (size_t i = 0; i < vector.size(); i++)
		for (size_t j = 0; j < vector.size() - 1; j++)
			if (vector.at(j) > vector.at(j + 1))
				std::swap(vector.at(j), vector.at(j + 1));
	return vector;
}
void timeTest(std::vector<short>& (*func)(std::vector<short>& vector), std::vector<short>& vector, std::string message) {
	time_t start = clock();
	func(vector);
	time_t finish = clock();
	std::cout << message << ": " << static_cast<double>(finish - start) / 1000.0 << " seconds.\n";
}
size_t separateFunction(std::vector<short>& vector, size_t start, size_t finish) {
	size_t i = start, j = start - 1;
	for (; i < finish; i++) {
		if (vector.at(i) <= vector.at(finish - 1)) {
			j++;
			std::swap(vector.at(i), vector.at(j));
		}
	}
	return j;
}
std::vector<short>& myQuickSort(std::vector<short>& vector, size_t start, size_t finish) {
	if (start < finish)
	{
		size_t pivot = separateFunction(vector, start, finish);
		myQuickSort(vector, start, pivot);
		myQuickSort(vector, pivot + 1, finish);
		return vector;
	}
}
std::vector<short>& quickSort(std::vector<short>& vector) {
	myQuickSort(vector, 0, vector.size());
	return vector;
}


int main() {
	srand(static_cast<int>(time(0)));
	std::vector<short> vect(10);
	myInit(vect);
	std::vector<short> vect1 = vect, vect2 = vect;

	printVector(vect); std::cout << '\n';
	timeTest(bubbleSort, vect1, "Bubble sort"); printVector(vect1);
	timeTest(quickSort, vect2, "Quick sort"); printVector(vect2);
}
