#include <iostream>
#include <string>
#include <vector>
#include <Matrix.h>

int main() 
{
    std::cout << "Enter size of matrix" << std::endl;
    size_t size;
    std::cin >> size;

    std::cout << "Enter all elements of matrix" << std::endl;
    std::vector<float> filler(size * size);
    float value;
    for (size_t i = 0; i < size * size; ++i)
    {
        std::cin >> value;
        filler[i] = value;
    }

    matrix::Matrix<float> m{ size, size, filler.begin(), filler.end() };
    std::cout << "Determinant = " << m.calcDeterminant() << std::endl;
    
    return 0;
}