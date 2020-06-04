#ifndef SLL_H
#define SLL_H

#include <iostream>
#include "Node.h"

using namespace std;

template <typename T>
class SLL {
private:
        Node<T>* head, * tail;
public:
    SLL(): head(nullptr), tail(nullptr){}
    SLL(const SLL& copySLL)
    {
        Node<T>* iter = copySLL.head;

        do
        {
            prepend(iter->value);

            iter = iter->next;

        } while (iter != copySLL.head);
        

    }
    ~SLL(){}

    bool isEmpty() const
    {
        return head == nullptr;
    }

    void prepend(const T& item)
    {
        Node<T>* newNode = new Node<T>{item};

        if(isEmpty())
        {   
            head = newNode;
            tail = newNode;
        }
        else
        {
            Node<T>* lastHead = head;

            head = newNode;
            head->next = lastHead;
        }
    }
    void append(const T& item)
    {
        Node<T>* newNode = new Node<T>{item};

        if(isEmpty())
        {
            head = newNode;
            tail = newNode;
        }
        else
        {
            tail->next = newNode;

            tail = newNode;
        }
    }

    T headValue() const
    {
        return head->value;
    }
    T tailValue() const
    {
        return tail->value;
    }

    bool removeFromHead()
    {
        if(isEmpty()) return false;
        else
        {
            Node<T>* temp = head->next;

            if(head == tail)
            {
                head = tail = nullptr;
                delete head;

                return true;
            }

            head = nullptr;
            delete head;

            head = temp;
            
            return true;
        }
    }
    bool removeFromTail()
    {
        if(isEmpty())
        {
            return false;
        }
        else
        {
            Node<T>* iter = head;

            do
            {
                if(iter->next == tail)
                {
                    tail = nullptr;
                    delete tail;

                    tail = iter;

                    iter = iter->next;

                    if(tail == head)
                    {
                        delete tail;

                        head = tail = nullptr;

                        return true;
                    }

                    return true;
                }
                else  iter = iter->next;


            } while (iter != tail);
        }
        
    }
    
    bool remove(Node<T>* node)
    {
        if(isEmpty()) return false;
        else if (node == tail)
        {
            return removeFromTail();
        }
        else if (node == head)
        {
            return removeFromHead();
        }
        else
        {
            Node<T>* iter = head;
            do
            {
                if(iter->next == node)
                {
                    iter->next = node->next;

                    delete node;

                    return true;
                }
                else iter = iter->next;

            } while (iter != tail); 
        }
    }

    void print()
    {
        if(isEmpty()) return;

        Node<T>* iter = head;
        
        do
        {
            cout << iter->value << " ";

            iter = iter->next;

        } while (iter != tail);

        cout << iter->value << " ";
        cout << endl;
    }


    template <typename A>
    friend ostream& operator<<(ostream& os, const SLL<A>& s);
};


template <typename A>
ostream& operator<<(ostream& os, const SLL<A>& s)
    {
        Node<A>* iter = s.head;
        
        do
        {
            os << *iter << " ";

            iter = iter->next;

        } while (iter != s.tail);

        os << *iter << " ";
        os << endl;

        return os;
    }

template <typename B>
ostream& operator<<(ostream& os, const Node<B>& n)
{
    os << "Value: " << n.value << endl;

    return os;
}

#endif