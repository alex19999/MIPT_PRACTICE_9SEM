#ifndef TREE_H
#define TREE_H

#include <string>

namespace trees
{   
    template <typename T>
    class SplayNode
    {
        T key;

        SplayNode<T>* parent;
        SplayNode<T>* left;
        SplayNode<T>* right;

    public:
        SplayNode(T value);

        T getKey() const { return key; }

        void insert(T value);

        std::pair<bool, SplayNode<T>*> find(T value);

        // For validation
        std::string print(std::string& result = std::string(""));
    };

    template <typename T>
    SplayNode<T>::SplayNode(T value)
        : key(value)
        , parent(nullptr)
        , left(nullptr)
        , right(nullptr)
    {        
    }

    template <typename T>
    void SplayNode<T>::insert(T value)
    {        
        if (key == value)
        {
            return;
        }

        if (value > key)
        {
            if (right == nullptr)
            {
                right = new SplayNode<T>(value);
                return;
            }
            right->insert(value);
            return;
        }

        if (value < key)
        {
            if (left == nullptr)
            {
                left = new SplayNode<T>(value);
                return;
            }
            left->insert(value);
            return;
        }
    }

    template <typename T>
    std::pair<bool, SplayNode<T>*> SplayNode<T>::find(T value)
    {
        if (value > key)
        {
            if (right == nullptr)
            {
                return std::make_pair(false, nullptr);
            }
            return right->find(value);
        }

        if (value < key)
        {
            if (left == nullptr)
            {
                return std::make_pair(false, nullptr);
            }
            return left->find(value);
        }

        return std::make_pair(true, this);
    }

    template <typename T>
    std::string SplayNode<T>::print(std::string& result)
    {        
        if (left != nullptr)
        {
            left->print(result);
        }
        
        result = result + " " + std::to_string(key);

        if (right != nullptr)
        {
            right->print(result);
        }
        
        return result;
    }
}

#endif