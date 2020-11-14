#include <chrono> 
#include <iostream>
#include <string>
#include <vector>
#include <trees/Tree.h>
#include <trees/Set.h>


int main() 
{ 
	size_t numOfKeys = 0;
    std::cout << "Enter number of keys" << std::endl;
	std::cin >> numOfKeys;
	trees::SplayTree<int> tree;
	trees::StandardSet<int> standardTree;

    std::cout << "Enter all keys" << std::endl;
    int key = 0;
	for(size_t i = 0; i < numOfKeys; ++i) 
    {
		std::cin >> key;
		tree.insert(key);
		standardTree.insert(key);
	}
	
	size_t numOfQueries = 0;
    std::cout << "Enter number of queries" << std::endl;
	std::cin >> numOfQueries;

    // Results
	std::vector<size_t> results(numOfQueries, 0u);
	std::vector<size_t> resultsSet(numOfQueries, 0u);
	
    std::cout << "Enter all queries" << std::endl;
    int lower = 0;
    int upper = 0;
	for(size_t i = 0; i < numOfQueries; ++i) 
    {
		std::cin >> lower;
		std::cin >> upper;
		auto start = std::chrono::high_resolution_clock::now();
		results[i] = tree.rangeQuery(lower, upper);
		std::cout << "Time for SplayTree: " << std::chrono::duration_cast<std::chrono::microseconds>(std::chrono::high_resolution_clock::now() - start).count() << std::endl;
		start = std::chrono::high_resolution_clock::now();
		resultsSet[i] = standardTree.rangeQuery(lower, upper);
		std::cout << "Time for std::set: " << std::chrono::duration_cast<std::chrono::microseconds>(std::chrono::high_resolution_clock::now() - start).count() << std::endl;
	}
	
    std::cout << "Results\n" << std::endl;
	for(size_t i = 0; i < results.size(); ++i) 
    {
		std::cout << results[i] << " " << resultsSet[i] << std::endl;
	}
}