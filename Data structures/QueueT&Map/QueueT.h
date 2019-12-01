#ifndef QUEUET_H
#define QUEUE_H

using namespace std;


template <typename T, size_t S>
class Queue
{
    public:
        T* head;
        T* tail;
        T container[S];

        Queue()
        {
            head = &container[0];
            tail = &container[0];
        }
        Queue(const Queue& q)
        {
            for(int i = 0; i < S; i++)
            {
                enqueue(q.container[i]);
            }
        }
        ~Queue()
        {
            delete [] container;
        }


        bool empty() const
        {
            return head == tail;
        }
        bool full() const
        {
            for(int i = 0; i < S; i++)
            {
                if((tail == &container[i]) && (head == &container[(i + 1) % S])) return true;
            }
            
            return false;
        }

        
        void enqueue(){}
        template <typename... Values>
        void enqueue(T value, Values... otherValues)
        {
            if(!full()) // full after adding one more element
            {
                for(int i = 0; i < S; i++)
                {
                    if(&container[i] == tail)
                    {
                        *tail = value;
 
                        tail = &container[(i + 1) % S];
                        
                        break;
                    }
                }
                enqueue(otherValues...);
            }
            else
            {
                *tail = value;

                for(int i = 0; i < S; i++)
                {
                    if(tail == &container[i])
                    {
                        tail = &container[(i + 1) % S];
                        break;
                    }
                    
                }
            }

        }

        T dequeue()
        {
            T val = *head;

            *head = 0;

            for(int i = 0; i < S; i++)
            {
                if(head == &container[i])
                {
                    head = &container[(i + 1) % S];
                    break;
                }
            }

            return val;
        }
};



#endif