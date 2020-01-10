#ifndef CDLL_H
#define CDLL_H

using namespace std;

#include "Node.h"

class CDLL {
protected:
    Node* head;
    Node* tail;
    int size;
public:
    CDLL()
    {
        head = tail = nullptr;
    }
    CDLL(const CDLL& c)
    {
        Node* iter = c.head;
        do
        {
            append(iter->value);

            iter = iter->next;
            
        }
        while(iter != c.head);
    }
    ~CDLL()
    {
        Node* iter = head->next;
        do
        {
            iter = iter->next;
            delete iter->prev;

            if(iter->next == head)
            {
                delete iter->next;
                delete iter;
                break;
            }
        }
        while(true);
    }

    bool empty() const
    { 
        return (head == nullptr) && (tail == nullptr);
    }

    void append(double value)
    {
        Node* element = new Node{value};
        size++;
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
    // postavi vrijednost na kraj
    void prepend(double value)
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
            element->next = head;
            element->prev = tail;

            head->prev = element;

            head = element;
            tail->next = head;
        }
        
    }
    // ukloni čvor s početka
    // i vrati njegovu vrijednost
    double removeFromHead()
    {
        size--;
        double val = head->value;

        head = head->next;

        delete head->prev;

        head->prev = tail;

        tail->next = head;        

        return val;
    }
    // ukloni čvor s kraja
    // i vrati njegovu vrijednost
    double removeFromTail()
    {
        size--;
        double val = tail->value;

        tail = tail->prev;

        delete tail->next;

        head->prev = tail;
        tail->next = head;

        return val;

    }
    // ispisujemo adresu head-a, tail-a te sve čvorove
    void print() const
    {
        cout << "Head at: " << head << " Tail at: " << tail << endl;
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
                {
                    iterator->swap(*(iterator->prev));
                    
                }

                iterator = iterator->next;

            }while(iterator != border);

            border = border->prev;
        }
    } 
};

#endif
