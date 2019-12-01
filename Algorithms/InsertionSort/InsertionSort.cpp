#include <iostream>

using namespace std;

template <typename T, size_t S>
void insertionSort(T (&array)[S])
{
    for(int i = 0; i < S - 1; i++)
    {
        if(array[i + 1] < array[i])
        {
            int j = i + 1;

            T key = array[j];

            for(int k = i; k >= 0; k--)
            {
                array[k + 1] = array[k];
                
                if(array[k] < key)
                {
                    array[k + 1] = key;
                    break;
                }
                else if (k == 0) 
                {
                    array[k] = key;
                    break;
                }
            }

        }
    }
}
template <typename T, size_t S>
void notMineinsertionsort(T (&arr)[S])
{  
    T key;
    int j;  
    for (int i = 1; i < S; i++) 
    {  
        key = arr[i];  
        j = i - 1;  
  
        /* Move elements of arr[0..i-1], that are  
        greater than key, to one position ahead  
        of their current position */
        while (j >= 0 && arr[j] > key) 
        {  
            arr[j + 1] = arr[j];  
            j = j - 1;  
        }  
        arr[j + 1] = key;  
    }  
} 



int main()
{

    int field[] = {12, 11, 13, 5, 6};
    int field2[] = {12, 11, 13, 5, 6};

    insertionSort<int, 5>(field);

    for(auto& x : field)
        cout << x << " ";

    notMineinsertionsort<int, 5>(field2);
    cout << endl;
    for(auto& x : field2)
        cout << x << " ";

    return 0;
}