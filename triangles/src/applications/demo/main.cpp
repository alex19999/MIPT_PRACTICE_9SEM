#include <iostream>
#include <string>

int main(int argc, char* argv[])
{
    size_t trianglesNumber;
    constexpr size_t pointsNumber = 3;
    
    std::cout << "Enter number of 3D triangles" << std::endl;
    std::cin >> trianglesNumber;
    
    std::cout << "Enter all coordinates" << std::endl;
    //std::array<triangles::Point, pointsNumber> triangle;
    //std::vector<triangles::Triangle> triangles;
    //triangles.resize(trianglesNumber);
    for (size_t i = 0; i < trianglesNumber; ++i)
    {
        for (size_t j = 0; j < pointsNumber; ++j)
        {
            //std::cin >> triangle[j].x;
            //std::cin >> triangle[j].y;
            //std::cin >> triangle[j].z;
        }
        //triangles[i] = triangles::Triangle(triangle[0], triangle[1], triangle[2]); 
    }
}