#include <iostream>
#include <vector>
#include <string>
#include <thread>


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
bool checkVectors(const std::vector<short>& vect1, const std::vector<short>& vect2) {
	bool same = true;
	for (size_t i = 0; i < vect1.size(); i++) {
		if (vect1.at(i) != vect2.at(i)) {
			same = false;
			//std::cout << vect1.at(i) << "\t!=\t" << vect2.at(i) << '\n';
		}
		if (!same) std::cout << "\t\tFALSE\n";
		else std::cout << "\t\tSAME\n";
		return same;
	}
}
void myMerging(std::vector<short>& vect, size_t start, size_t finish) {
	std::vector<short>buffer;
	size_t left_index = start, right_index = start + ((finish - start) / 2);
	for (int i = 0; i < finish; i++) {
		if (i < ((finish - start) / 2)) buffer.push_back(vect.at(i));
		if (!buffer.empty()) {
			if (vect.at(right_index) <= buffer.at(0)) {
				vect.at(i) = vect.at(right_index);
				if (right_index < vect.size() - 1) right_index++;
				else vect.at(right_index) = buffer.back();
			}
			else {
				vect.at(i) = buffer.front();
				buffer.erase(buffer.begin());
			}
		}
	}
}
std::vector<short>& quickSortMultiThreads(std::vector<short>& vect) {
	const size_t threads_count = 2;
	size_t middle = vect.size() / 2;

	std::vector<std::thread> threads;
	threads.reserve(threads_count);

	threads.emplace_back(myQuickSort, std::ref(vect), size_t{ 0 }, middle);
	threads.emplace_back(myQuickSort, std::ref(vect), middle, vect.size());

	for (std::thread& thread : threads) {
		thread.join();
	}

	myMerging(vect, 0, vect.size());
	return vect;
}


int main() {
	srand(static_cast<int>(time(0)));
	std::vector<short> vect(50'000);
	myInit(vect);
	std::vector<short> vect1 = vect, vect2 = vect, vect3 = vect;
	
	timeTest(bubbleSort, vect1, "\nBubble sort");
	timeTest(quickSort, vect2, "\nQuick sort");
	std::cout << "BubbleSort and QuickSort: "; checkVectors(vect1, vect2);
	timeTest(quickSortMultiThreads, vect3, "\nQuick sort multi threads: "); 
	std::cout << "QuickSort and QuickSortMultiThreads: "; checkVectors(vect2, vect3);
}
