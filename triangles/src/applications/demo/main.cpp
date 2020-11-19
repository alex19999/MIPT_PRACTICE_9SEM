#include <iostream>
#include <string>

#include <triangles/Lib.h>
#include <set>

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
        // Do not consider degenerative triangles
        if (triangles::Triangle<3> { points[0], points[1], points[2] }.square() != 0.0)
        {
            triangles.push_back(triangles::Triangle<3> { points[0], points[1], points[2] }); 
        }
    }
    std::set<size_t> intersected;
    for (size_t i = 0; i < triangles.size(); ++i)
    {
        for (size_t j = i + 1; j < triangles.size(); ++j)
        {
            if (haveIntersection(triangles[i], triangles[j]))
            {
                intersected.insert(i);
                intersected.insert(j);
            }
        }
    }
    
    // output
    for (auto& num : intersected)
    {
        std::cout << num << std::endl;
    }
}
