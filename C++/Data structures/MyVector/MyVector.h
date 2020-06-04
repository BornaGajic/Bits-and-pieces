#ifndef MYVECTOR_H
#define MYVECTOR_H

#include <iostream>

using namespace std;

class MyVector {

protected:

    unsigned int _size, _capacity;
    int* field;

public:
    MyVector()
    {
        field = new int[1];
        _size = 0;
        _capacity = 1;
    }
    MyVector(const MyVector& mycv)
    {
        for(int i = 0; i < mycv.getSize(); i++)
        {
            pushBack(mycv.field[i]);
        }
    }
    ~MyVector()
    {
        delete [] field;
    }

    void pushBack(int value)
    {
        if(!full())
        {
            field[_size++] = value;
        }
        else
        {
            int* backupField = new int[_size];

            for(int i = 0; i < _size; i++)
            {
                backupField[i] = field[i];
            }

            delete [] field;
            _capacity *= 2;
            field = new int [_capacity];

            for(int i = 0; i < _size; i++)
            {
                field[i] = backupField[i];
            }           

            delete [] backupField;

            field[_size++] = value;

        }
    }
    void popBack()
    {
        if(!empty())
        {
            field[_size--] = 0;

            if(_size * 2 == _capacity)
            {
                int* backupField = new int[_size];

                for(int i = 0; i < _size; i++)
                {
                    backupField[i] = field[i];
                }

                delete [] field;
                _capacity /= 2;
                field = new int [_capacity];

                for(int i = 0; i < _size; i++)
                {
                    field[i] = backupField[i];
                }           

                delete [] backupField;      

                field[_size--] = 0;          
            }
        }
        else
        {
            cout << "Can't do that" << endl;
        }
    }

    int getCapacity() const { return _capacity; }
    int getSize() const { return _size; }

    bool empty(){ return _size == 0; }
    bool full(){ return _size == _capacity; }

    int& at(int pos){ return field[pos]; }
    int& front() { return field[0]; }
    int& back() { return field[_size - 1]; }

    //operator pridruživanja
    MyVector& operator=(const MyVector& vect)
    {   
        for(int i = 0; i < vect.getSize(); i++)
        {
            pushBack(vect.field[i]);
        } 

        return *this;      
    }
    /*
    Povećaj element na itom mjestu za vrijednost
    koja se nalazi na itom mjestu vektora
    prosljeđenog po referenci
    */
    MyVector& operator+=(const MyVector& vect)
    {
        int size = _size >= vect.getSize() ? vect.getSize() : _size;

        for(int i = 0; i < size; i++)
        {
            field[i] += vect.field[i];
        }

        return *this;
    }   
    //zbroj vektora
    MyVector operator+(const MyVector& vect) const
    {
        MyVector* summedResult = new MyVector{};

        int size = _size >= vect.getSize() ? vect.getSize() : _size;

        for(int i = 0; i < size; i++)
        {
            summedResult->field[i] = field[i] + vect.field[i];
        }       

        return *summedResult;
    }
    //skalarni produkt vektora
    int operator*(const MyVector& vect) const
    {
        int result = 0;
        for(int i = 0; i < _size; i++)
        {
            result += field[i] * vect.field[i];
        } 

        return result;
    }
    //provjera jesu li dva vektora jednaki po elementima
    bool operator==(const MyVector& vect) const
    {
        if(_size != vect.getSize()) return false;
        else
        {
            for(int i = 0; i < _size; i++)
            {
                if(field[i] != vect.field[i]) return false;
            }
        }

        return true;
    }
    //provjera jesu li dva vektora različiti po elementima
    bool operator!=(const MyVector& vect) const
    {
        if(_size != vect.getSize()) return false;
        else
        {
            for(int i = 0; i < _size; i++)
            {
                if(field[i] != vect.field[i]) return true;
            }
        }

        return false;        
    }
    //operatori dohvaćanja
    const int& operator[](int x) const{ return field[x]; }
    int& operator[](int x){ return field[x]; }
    /*
    početak i kraj vektora
    (obratite pažnju što treba vraćati end)
    */
    int* begin() const { return &field[0]; }
    int* end() const { return &field[_size]; }

    friend ostream& operator<<(ostream& os, const MyVector& v)
    {
        for(int x : v)
        {
            os << x << " ";
        }
        os << endl;
        
        return os;
    }
};

#endif