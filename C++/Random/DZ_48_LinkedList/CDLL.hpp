#ifndef CDLL_HPP
#define CDLL_HPP

#include "Node.hpp"

class CDLL {
protected:
    Node* head;
    Node* tail;
    int size = 0;
public:
    CDLL()
    {
        head = tail = nullptr;
    }

    bool empty() const
    { 
        return (head == nullptr) && (tail == nullptr);
    }

    void append(double value)
    {
        size++;
        Node* element = new Node{value};

        if(empty())
        {
            head = element;
            tail = element;

            element->next = element;
            element->prev = element;

        }
        else
        {
            element->prev = tail;
            element->next = head;

            tail->next = element;
           
            tail = element;
            head->prev = tail;     
        }
    }

    void print() const
    {
        Node* iterator = head;
        do
        {
            iterator->print();
          
            iterator = iterator->next;

        }while(iterator != head);
    }

    void sort()
    {
        for (int i = 0; i < size; i++)
        {
            Node* border = head;
            Node* iterator = head->next;
            do
            {
                if(iterator->value < iterator->prev->value)
                    iterator->swap(*(iterator->prev));

                iterator = iterator->next;

            }while(iterator != border);

            border = border->prev;
        }
    }

    void Delete (double value)
    {
        Node* iter = head;

        do
        {
            if(iter->value == value)
            {
                iter->prev->next = iter->next;
                iter->next->prev = iter->prev;
            }

            iter = iter->next;
        }
        while(iter != head);
    }
};

#endif