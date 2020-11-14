#ifndef SET_H
#define SET_H

#include <set>

namespace trees
{
    template <typename T>
    class StandardSet
    {
    public:
        void insert(const T& value) { standardTree.insert(value); }
        bool find(const T& value) { return standardTree.find(value) != standardTree.end(); }
        void remove(const T& value) { standardTree.erase(value); }

        typename std::set<T>::const_iterator upperBound(const T& value) const { return standardTree.upper_bound(value); }
        typename std::set<T>::const_iterator lowerBound(const T& value) const { return standardTree.lower_bound(value); }

        typename std::set<T>::const_iterator end() const { return standardTree.cend(); }
        typename std::set<T>::const_iterator begin() const { return standardTree.cbegin(); }

        size_t rangeQuery(const T& lower, const T& upper) const;
    private:
        std::set<T> standardTree;
    };

    template <typename T>
    size_t StandardSet<T>::rangeQuery(const T& lower, const T& upper) const
    {
        auto start = upperBound(lower);
        auto end = lowerBound(upper);
        size_t num = 0;
        for (auto s = start; s != end; ++s)
        {
            num++;
        }
        return num;
    }
}

#endif