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

        Node* _find(const T& value) const;
        void _rebinding(Node* parent, Node* child);
        
        void _flush(Node* root);
        
        // Rotations
        void _leftRotate(Node* oldRoot);
        void _rightRotate(Node* oldRoot);

        // zig/zigzag/zigzig movements
        void _splay(Node* newRoot);

        Node* _next(Node* current) const;

    public:
        SplayTree() : root(nullptr) { }
        ~SplayTree() { _flush(root); }

        void insert(const T& value);
        bool find(const T& value);
        void remove(const T& value);

        Node* upperBound(const T& value) const;

        Node* getRoot() const { return root; }

        size_t rangeQuery(const T& lower, const T& upper) const;

        // For validation
        std::string print(Node* from = nullptr, std::string& result = std::string(""));
    };


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
    typename SplayTree<T>::Node* SplayTree<T>::_find(const T& value) const
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
    void SplayTree<T>::_leftRotate(Node* oldRoot)
    {
        auto newRoot = oldRoot->right;
        oldRoot->right = newRoot->left;
        if (oldRoot->right != nullptr)
        {
            oldRoot->right->parent = oldRoot;
        }

        _rebinding(oldRoot, newRoot);
        newRoot->left = oldRoot;
        newRoot->left->parent = newRoot;
    }

    template <typename T>
    void SplayTree<T>::_rightRotate(Node* oldRoot)
    {
        auto newRoot = oldRoot->left;
        oldRoot->left = newRoot->right;
        if (oldRoot->left != nullptr)
        {
            oldRoot->left->parent = oldRoot;
        }

        _rebinding(oldRoot, newRoot);
        newRoot->right = oldRoot;
        newRoot->right->parent = newRoot;
    }

    template <typename T>
    void SplayTree<T>::_splay(Node* newRoot)
    {
        while(newRoot != root)
        {   
            // Zig step (if new root is child of the root)
            if (newRoot == root->left)
            {
                _rightRotate(root);
            }
            else if (newRoot == root->right)
            {
                _leftRotate(root);
            }
            else
            {
                // Zig-zig step (from one side)
                if (newRoot == newRoot->parent->left && newRoot->parent == newRoot->parent->parent->left)
                {
                    _rightRotate(newRoot->parent->parent);
                    _rightRotate(newRoot->parent);
                }
                else if (newRoot == newRoot->parent->right && newRoot->parent == newRoot->parent->parent->right)
                {
                    _leftRotate(newRoot->parent->parent);
                    _leftRotate(newRoot->parent);
                }
                // Zig-zag step (from different sides)
                else if (newRoot == newRoot->parent->left && newRoot->parent == newRoot->parent->parent->right)
                {
                    _rightRotate(newRoot->parent);
                    _leftRotate(newRoot->parent);
                }
                else
                {
                    _leftRotate(newRoot->parent);
                    _rightRotate(newRoot->parent);
                }
            }
        }
    }

    template <typename T>
    typename SplayTree<T>::Node* SplayTree<T>::_next(Node* current) const
    {
        Node* next = current;
        if (current->right != nullptr)
        {
            next = current->right;
            while(next->left != nullptr)
            {
                next = next->left;
            }
            return next;
        }
        
        while(next->parent != nullptr && next != next->parent->left)
        {
            next = next->parent;
        }

        return next->parent;
    }

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

        _splay(elemToInsert);
    }

    template <typename T>
    bool SplayTree<T>::find(const T& value)
    {
        auto node = _find(value);
        if (node != nullptr)
        {
            _splay(node);
            return true;
        }
        return false;
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

        _splay(minimum);
    }

    template <typename T>
    typename SplayTree<T>::Node* SplayTree<T>::upperBound(const T& value) const
    {
        Node* upperBound = root;
        Node* parent = nullptr;
        while(upperBound != nullptr)
        {
            parent = upperBound;
            if (upperBound->key == value)
            {
                return upperBound;
            }
            upperBound = upperBound->key < value ? upperBound->right : upperBound->left;
        }
        if (parent->key > value)
        {
            return parent;
        }

        return _next(parent);
    }

    template <typename T>
    size_t SplayTree<T>::rangeQuery(const T& lower, const T& upper) const
    {
        if (lower >= upper)
        {
            throw std::runtime_error("Incorrect range given");
        }
        size_t suitableElems = 0;

        auto begin = upperBound(lower);
        auto end = upperBound(upper);

        if (end == nullptr && begin == nullptr)
        {
            return suitableElems;
        }

        for(auto s = begin; s != end; s = _next(s))
        {
            suitableElems += 1u;
        }
        if (begin && begin->key == lower)
        {
            suitableElems -= 1u;
        }
        return suitableElems;
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