#include <iostream>
#include <vector>
#include <stdlib.h>
#include <time.h>

using namespace std;

int partition(vector<int>& array, int s, int f)
{   
    int pivotIndex = rand() % (f - s + 1) + s;
    
    int i = s;

    for(int j = s; j <= f; j++)
    {
        if(j == pivotIndex) continue;

        if(array[j] <= array[pivotIndex])
        {
            if (pivotIndex == i)
                pivotIndex = j;

            swap(array[j], array[i++]);
        }
    }

    swap(array[i], array[pivotIndex]);
    pivotIndex = i;
    
    return pivotIndex;  
}

void QuickSort(vector<int>& A, int s, int f)
{
    if(s < f)
    {
        srand (time(NULL)); 
        
        int pivotIndex = partition(A, s, f);
        
        QuickSort(A, s, pivotIndex - 1);
        QuickSort(A, pivotIndex + 1, f);
    }
}


int main()
{
    vector<int> A = {5, 4, 3, 2, 1, 6, 7, 8, 12, -2};
    vector<int> B = {5, 4, 3, 2, 1};

   
    QuickSort(A, 0, A.size() - 1);
    QuickSort(B, 0, B.size() - 1);

    for(auto x : A)
        cout << x << " ";

    cout << endl;

    for(auto x : B)
        cout << x << " ";


    return 0;
}