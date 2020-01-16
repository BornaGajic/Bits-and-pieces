#ifndef AVL_H
#define AVL_H

#include <iostream>
#include <algorithm>
#include <utility>

#include "Node.hpp"

using namespace std;

class AVL
{
    public:
    Node* root{};

    AVL(){}
    ~AVL()
    {
        _deleteTree(root);

        delete root;
    }

    void insert (int value)
    {
        Node* newNode = new Node{value};
        
        if (root == nullptr)
            root = newNode, _incrementHeight(newNode);
        else
        {
            Node* iter = root;
            while (true)
            {
                if (newNode->value <= iter->value)
                {
                    if (iter->leftChild == nullptr)
                    {
                        newNode->parent = iter;
                        iter->leftChild = newNode;
                        
                        _incrementHeight(newNode);
                        _balanceOut(newNode);
                        
                        break;
                    }
                    else iter = iter->leftChild;
                }
                else 
                {
                    if (iter->rightChild == nullptr)
                    {
                        newNode->parent = iter;
                        iter->rightChild = newNode;

                        _incrementHeight(newNode);                      
                        _balanceOut(newNode);

                        break;
                    } 
                    else iter = iter->rightChild;
                }
            }
        } 
    }

    Node* sucessor (int value)
    {
        Node* iter = root;
        
        while (iter != nullptr)
        {
            if (value > iter->value)
                iter = iter->rightChild;
            else if (value < iter->value)
                iter = iter->leftChild;
            else
            {                  
                if (iter->rightChild != nullptr)
                {
                    if (iter->rightChild->leftChild == nullptr)
                        return iter->rightChild;
                    else
                        return iter->rightChild->leftChild;
                }
                else
                {
                    if (iter->parent != nullptr)
                    {
                        if (iter->parent->value > iter->value)
                            return iter->parent;
                        else
                        {
                            if (iter->parent->parent != nullptr)
                            {
                                Node* temp = iter;
                                iter = iter->parent;
                                while(iter != nullptr)
                                {
                                    if (iter->value > temp->value)
                                        return iter;
                                    else
                                        iter = iter->parent;
                                }

                                return nullptr;
                            }
                            else
                                return nullptr;
                        }
                    }
                    else
                        return nullptr;
                }
            }    
        }
    }

    Node* predecessor (int value)
    {
        Node* iter = root;
        
        while (iter != nullptr)
        {
            if (value > iter->value)
                iter = iter->rightChild;
            else if (value < iter->value)
                iter = iter->leftChild;
            else
            {
                if (iter->leftChild != nullptr)
                    return iter->leftChild;
                else
                {
                    if (iter->parent != nullptr)
                        return iter->parent;
                    else
                        return nullptr;
                }
            }
        } 
    }

    void erase (int value)
    {
        Node* iter = root;
        Node* nodeToDelete = nullptr;

        while (iter != nullptr)
        { 
            if (iter->value < value)
                iter = iter->rightChild;
            else if (iter->value > value)
                iter = iter->leftChild;
            else
            {
                nodeToDelete = iter;
                
                if (nodeToDelete->leftChild == nullptr && nodeToDelete->rightChild == nullptr)
                {
                    _decrementHeight(nodeToDelete);

                    if (nodeToDelete->parent != nullptr)
                    {
                        if (nodeToDelete->parent->leftChild == nodeToDelete)
                            nodeToDelete->parent->leftChild = nullptr;
                        else if (nodeToDelete->parent->rightChild == nodeToDelete)
                            nodeToDelete->parent->rightChild = nullptr;
                        
                        _balanceOut(nodeToDelete->parent);
                    }
                    else
                    {
                        root = nullptr;
                        delete root;
                    }
                        
                    _deleteNode(nodeToDelete);
                }
                else
                {
                    Node* sucNode = sucessor(value);

                    if (sucNode == nullptr)
                    {
                        if (nodeToDelete->parent == nullptr)
                        {
                            if (nodeToDelete->leftChild != nullptr)
                            {
                                swap(nodeToDelete->value, nodeToDelete->leftChild->value);
                                nodeToDelete->height = 0;
                                
                                Node* temp = nodeToDelete->leftChild;
                                nodeToDelete->leftChild = nullptr;
                                _deleteNode(temp);

                                break;
                            }   
                            else
                                _deleteNode(nodeToDelete);
                        }
                        else
                        {
                            if (nodeToDelete->leftChild != nullptr)
                                nodeToDelete->parent->rightChild = nodeToDelete->leftChild;
                            
                            nodeToDelete->parent->rightChild = nullptr;
                        }
                    }

                    if (sucNode->leftChild == nodeToDelete)
                    {
                        nodeToDelete->leftChild->parent = nodeToDelete->parent;
                        nodeToDelete->parent->leftChild = nodeToDelete->leftChild;
                        
                        nodeToDelete->leftChild->height = nodeToDelete->height;

                        _decrementHeight(nodeToDelete->leftChild);

                        delete nodeToDelete;
                        nodeToDelete = nullptr;

                        break;
                    }
                    
                    swap(nodeToDelete->value, sucNode->value);
                    nodeToDelete = sucNode;

                    if (nodeToDelete->leftChild == nullptr && nodeToDelete->rightChild == nullptr)
                    {
                        if (nodeToDelete->parent->leftChild == nodeToDelete)
                            nodeToDelete->parent->leftChild = nullptr;
                        else
                            nodeToDelete->parent->rightChild = nullptr;

                        _decrementHeight(nodeToDelete);
                        _balanceOut(nodeToDelete);
                        _deleteNode(nodeToDelete);
                    }
                    else
                    {
                        if (nodeToDelete->parent->leftChild == nodeToDelete)
                            nodeToDelete->parent->leftChild = nodeToDelete->rightChild;
                        else
                            nodeToDelete->parent->rightChild = nodeToDelete->rightChild;

                        nodeToDelete->rightChild->parent = nodeToDelete->parent;
                        
                        _decrementHeight(nodeToDelete->parent);
                        _balanceOut(nodeToDelete->rightChild);
                        delete nodeToDelete;
                        nodeToDelete = nullptr;
                    }
                }
            }
        }
    }

    void inorderPrint (Node* iter)
    {
        if (iter == nullptr) return;
        else 
        {
            cout << " iter val " << iter->value << " " << endl;

            if (iter->leftChild != nullptr)
                cout << " left: " << iter->leftChild->value << endl;
            else
                cout << " left: " << 0 << endl;

            if (iter->rightChild != nullptr)
                cout << " right: " << iter->rightChild->value << endl;
            else
                cout << " right: " << 0 << endl;
            
            cout << " height: " << iter->height << endl;

            cout << endl;
        }

        inorderPrint(iter->leftChild);
        inorderPrint(iter->rightChild);
    }

    int balance (Node* node) 
    {
        if (node->leftChild != nullptr)
        {
            if (node->rightChild != nullptr)
                return node->leftChild->height - node->rightChild->height;

            return node->leftChild->height + 1;
        }
        else
        {
            if (node->rightChild != nullptr)
                return node->rightChild->height + 1;
        }

        return 0;
    }

    private:
    void _incrementHeight (Node* iter)
    {
        iter->height = iter->height == -1 ? 0 : iter->height;

        while (true)
        {
            if (iter->parent == nullptr)
                return;

            if (iter->height <= iter->parent->height)
            {
                if (iter->height == iter->parent->height)
                {
                    iter->parent->height++; 
                }
                else
                {
                    if (iter->parent->leftChild != nullptr && iter->parent->rightChild != nullptr)
                    {
                        iter->parent->height =
                        max(iter->parent->leftChild->height, iter->parent->rightChild->height) + 1;
                    }
                    else
                    {
                        if (iter->parent->rightChild != nullptr && iter->parent->leftChild == nullptr)
                            iter->parent->height = iter->parent->rightChild->height + 1;
                        else
                            iter->parent->height = iter->parent->leftChild->height + 1;
                    }
                }
            }
            else 
                iter->parent->height = iter->height + 1;

            iter = iter->parent;
        }
    }

    void _decrementHeight (Node* iter)
    {
        while (true)
        {
            if (iter == nullptr) return;

            if(iter->parent != nullptr)
            {
                if (abs(iter->parent->height - iter->height) == 1)
                {
                    if (iter->parent->leftChild != nullptr && iter->parent->rightChild != nullptr)
                    {
                        if (iter->parent->leftChild->height == iter->parent->rightChild->height)
                        {
                            iter->height = balance(iter) == 1 ? iter->height : iter->height - 1;
                            
                            return;
                        }
                    }

                    iter->height--;
                    iter = iter->parent;
                }
                else
                {
                    iter->height--;
                    return;
                }        
            }
            else
            {
                if (iter->leftChild != nullptr)
                {
                    if (iter->rightChild != nullptr)
                        iter->height = max(iter->leftChild->height, iter->rightChild->height) + 1;
                    else
                        iter->height--;
                }
                else
                    iter->height--;

                break;
            }
                
        }
    }
    
    void _leftRotate (Node* node, bool isNodeLeftChild)
    {
        if (node->rightChild == nullptr) return;

        node->rightChild->parent = node->parent;
        
        if (node->parent != nullptr)
        {            
            if (isNodeLeftChild)
                node->parent->leftChild = node->rightChild;
            else
                node->parent->rightChild = node->rightChild;
        }
        else
            root = node->rightChild;

        node->parent = node->rightChild;

        if (node->rightChild->leftChild != nullptr)
        {
            Node* temp = node->rightChild->leftChild;
            node->rightChild->leftChild->parent = node;
            node->rightChild->leftChild = node;
            node->rightChild = temp;

            if (node->leftChild != nullptr)
                node->height = max(node->leftChild->height, node->rightChild->height) + 1;
            else
                node->height = node->rightChild->height + 1;
            
            _incrementHeight(node->parent);
        }
        else
        {   
            if (node->leftChild == nullptr)
                node->height = -1;
            else
                node->height = node->leftChild->height + 1;

            _incrementHeight(node);
            
            node->rightChild->leftChild = node;
            node->rightChild = nullptr;
        }
    }

    void _rightRotate (Node* node, bool isNodeLeftChild)
    {
        if (node->leftChild == nullptr) return;

        node->leftChild->parent = node->parent;

        if (node->parent != nullptr)
        {   
            if (isNodeLeftChild)
                node->parent->leftChild = node->leftChild;
            else
                node->parent->rightChild = node->leftChild;
        }
        else
            root = node->leftChild;
        
        node->parent = node->leftChild;

        if (node->leftChild->rightChild != nullptr)
        {
            Node* temp = node->leftChild->rightChild;

            node->leftChild->rightChild->parent = node;
            node->leftChild->rightChild = node;
            node->leftChild = temp;

            if (node->rightChild != nullptr)
                node->height = max(node->rightChild->height, node->leftChild->height) + 1;
            else
                node->height = node->leftChild->height + 1;

            _incrementHeight(node->parent);
        }
        else
        {   
            if (node->rightChild == nullptr)
                node->height = -1;
            else
                node->height = node->rightChild->height + 1;
            
            _incrementHeight(node);

            node->leftChild->rightChild = node;
            node->leftChild = nullptr;
        }
    }
    
    void _balanceOut (Node* node)
    {
        Node* iter = node;
        bool isLeftChild;

        while (iter != nullptr)
        {
            if (abs(balance(iter)) > 1)
            {
                if (iter->leftChild != nullptr && iter->rightChild != nullptr)
                {
                    if (iter->leftChild->height > iter->rightChild->height)
                    {
                        iter = iter->leftChild;
                        isLeftChild = true;
                    }
                    else
                    {
                        iter = iter->rightChild;
                        isLeftChild = false;
                    }
                }
                else
                {   
                    if (iter->leftChild == nullptr)
                        isLeftChild = false;
                    else
                        isLeftChild = true;
                }
                
                if (iter->leftChild == nullptr)
                {
                    _rightRotate(iter->rightChild, false);

                    if (iter->parent != nullptr)
                    {
                        if (iter->parent->value > iter->value)
                            _leftRotate(iter, true);
                        else
                            _leftRotate(iter, false);
                    }
                    else
                        _leftRotate(iter, true);

                    _balanceOut(node);

                    break;
                }
                else if (iter->rightChild == nullptr)
                {
                    _leftRotate(iter->leftChild, true);
                    
                    if (iter->parent != nullptr)
                    {
                        if (iter->parent->value > iter->value)
                            _rightRotate(iter, true);
                        else
                            _rightRotate(iter, false);
                    }
                    else
                        _rightRotate(iter, false);
                    
                    _balanceOut(node);
                    
                    break;
                }
                else
                {
                    if (iter->leftChild->height > iter->rightChild->height)
                    {   
                        _leftRotate(iter, isLeftChild);
                        iter = iter->parent;
                        _rightRotate(iter->parent, isLeftChild);
                        
                        _balanceOut(node);

                        break;
                    }
                    else if (iter->leftChild->height < iter->rightChild->height)
                    {
                        _rightRotate(iter, isLeftChild);
                        iter = iter->parent; 
                        _leftRotate(iter->parent, isLeftChild);
                        
                        _balanceOut(node);
                        
                        break;
                    }
                    else
                    {
                        _leftRotate(iter, isLeftChild);

                        if (balance(iter) > 1)
                            _balanceOut(iter);

                        break;
                    }
                }   
            }
            else
                iter = iter->parent;
        }
    }

    void _deleteTree(Node* iter)
    {
        if (iter == nullptr) return

        _deleteTree(iter->leftChild);
        delete iter->leftChild;

        _deleteTree(iter->rightChild);
        delete iter->rightChild;
    }

    void _deleteNode (Node* node)
    {
        if (node->parent != nullptr)
        {
            if (node->parent->rightChild == node)
                node->parent->rightChild = nullptr;
            else if (node->parent->leftChild == node)
                node->parent->leftChild = nullptr;       
        }

        delete node;
        node = nullptr;
    }
};


#endif