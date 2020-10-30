#ifndef TREE_H
#define TREE_H

#include <string>

namespace trees
{   
    template <typename T>
    class SplayTree
    {
        struct Node
        {

            T key;

            Node* parent;
            Node* left;
            Node* right;

            Node(const T& value = T())
                : key(value)
                , parent(nullptr)
                , left(nullptr)
                , right(nullptr)
            {
            }

        }* root;

        Node* _find(const T& value);
        void _rebinding(Node* parent, Node* child);
        
        void _flush(Node* root);

    public:
        SplayTree() : root(nullptr) { }
        ~SplayTree() { _flush(root); }

        void insert(const T& value);
        bool find(const T& value);
        void remove(const T& value);

        Node* getRoot() const { return root; }

        // For validation
        std::string print(Node* from = nullptr, std::string& result = std::string(""));
    };

    template <typename T>
    void SplayTree<T>::insert(const T& value)
    {
        if (root == nullptr)
        {
            root = new Node(value);
            return;
        }

        if (root->key == value)
        {
            return;
        }

        Node* placeToInsert = root;
        Node* parentOfNewElem = nullptr;

        while(placeToInsert != nullptr)
        {
            parentOfNewElem = placeToInsert;

            if (placeToInsert->key < value)
            {
                placeToInsert = placeToInsert->right;
                continue;
            }
            
            if (placeToInsert->key > value)
            {
                placeToInsert = placeToInsert->left;
                continue;
            }

            return;
        }
        
        auto elemToInsert = new Node(value);
        elemToInsert->parent = parentOfNewElem;
        if (parentOfNewElem->key < value)
        {
            parentOfNewElem->right = elemToInsert;
        }
        if (parentOfNewElem->key > value)
        {
            parentOfNewElem->left = elemToInsert;
        }
    }

    template <typename T>
    void SplayTree<T>::_flush(Node* root)
    {
        if (root == nullptr)
        {
            return;
        }

        _flush(root->left);
        _flush(root->right);
        delete root;
    }

    template <typename T>
    typename SplayTree<T>::Node* SplayTree<T>::_find(const T& value)
    {
        auto startPoint = root;
        while(startPoint != nullptr)
        {
            if (startPoint->key == value)
            {
                return startPoint;
            }
            if (startPoint->key < value)
            {
                startPoint = startPoint->right;
                continue;
            }
            if (startPoint->key > value)
            {
                startPoint = startPoint->left;
                continue;
            }
        }
        return nullptr;
    }

    template <typename T>
    bool SplayTree<T>::find(const T& value)
    {
        return _find(value) != nullptr;
    }
    
    template <typename T>
    void SplayTree<T>::_rebinding(Node* parent, Node* child)
    {
        if (parent->parent == nullptr)
        {
            root = child;
        }
        else if (parent == parent->parent->left)
        {
            parent->parent->left = child;
        }
        else if (parent == parent->parent->right)
        {
            parent->parent->right = child;
        }

        if (child != nullptr)
        {
            child->parent = parent->parent;
        }
    }

    template <typename T>
    void SplayTree<T>::remove(const T& value)
    {
        auto elementToRemove = _find(value);

        if (elementToRemove == nullptr)
        {
            return;
        }

        if (elementToRemove->left == nullptr)
        {
            _rebinding(elementToRemove, elementToRemove->right);
            return;
        }
        
        if (elementToRemove->right == nullptr)
        {
            _rebinding(elementToRemove, elementToRemove->left);
            return;
        }

        // Find minimum element in right subtree
        auto minimum = elementToRemove->right;
        while(minimum->left != nullptr)
        {
            minimum = minimum->left;
        }

        // Exchange minimum with its right subtree if needed
        if (minimum->parent != elementToRemove)
        {
            _rebinding(minimum, minimum->right);
            minimum->right = elementToRemove->right;
            elementToRemove->right->parent = minimum;
        }

        // Exchange minimum and element to remove
        _rebinding(elementToRemove, minimum);
        minimum->left = elementToRemove->left;
        minimum->left->parent = minimum;
    }
    
    template <typename T>
    std::string SplayTree<T>::print(Node* from, std::string& result)
    {
        if (from == nullptr)
        {
            return result;
        }
        if (from->left != nullptr)
        {
            print(from->left, result);
        }

        result = result + " " + std::to_string(from->key);

        if (from->right != nullptr)
        {
            print(from->right, result);
        }
        
        return result;
    }
    
}

#endif