#include <iostream>
#include <string>

#include <triangles/Lib.h>

int main(int argc, char* argv[])
{
    size_t trianglesNumber;
    constexpr size_t pointsNumber = 3;
    std::vector<triangles::Triangle<3>> triangles;
    
    std::cout << "Enter number of 3D triangles" << std::endl;
    std::cin >> trianglesNumber;
    
    std::cout << "Enter all coordinates" << std::endl;
    
    float x;
    float y;
    float z;
    for (size_t i = 0; i < trianglesNumber; ++i)
    {
        std::vector<triangles::Point<3>> points;
        for (size_t j = 0; j < pointsNumber; ++j)
        {
            std::cin >> x;
            std::cin >> y;
            std::cin >> z;
            points.push_back(triangles::Point<3>{ std::array{ x, y, z} });
        }
        triangles.push_back(triangles::Triangle<3> { points[0], points[1], points[2] }); 
    }

    size_t numOfIntersections = 0;
    for (size_t i = 0; i < triangles.size(); ++i)
    {
        for (size_t j = i + 1; j < triangles.size(); ++j)
        {
            numOfIntersections += static_cast<size_t>(haveIntersection(triangles[i], triangles[j]));
        }
    }
    std::cout << "Number of unique intersections = " << numOfIntersections << std::endl;
}
