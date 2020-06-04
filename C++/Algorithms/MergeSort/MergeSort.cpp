#include <iostream>
#include <math.h>


using namespace std;

void merge(int (&arr)[8], const int startOfL, const int endOfL, const int endOfR) // pocetak lijevog, kraj lijvog, kraj desnog
{   
    int lenOfL = endOfL - startOfL + 1; // duljina lijevog potpolja
    int lenOfR = endOfR - endOfL; // duljina desnog potpolja

    int* L = new int[lenOfL];
    int* R = new int[lenOfR];

    int iter = 0;
    for(int i = startOfL; i <= endOfL; i++) L[iter++] = arr[i]; // lijevo potpolje L[pocetakL : krajL]

    iter = 0;
    for(int i = endOfL + 1; i <= endOfR; i++) R[iter++] = arr[i]; // desno potpolje R[krajL + 1 : krajR]
        


    int j = 0, k = 0;
    for(int i = startOfL; i <= endOfR; i++) // for kroz buduce spojeno polje
    {
        if(L[j] <= R[k])
        {
            arr[i] = L[j++];

            if(j == lenOfL)                 // ako je si iterirao kroz cijelo potpolje kopiraj ono drugo do kraja
            {
                for(int iter = i + 1; iter <= endOfR; iter++)
                {
                    arr[iter] = R[k++];
                }

                break;
            }
        }
        else if(L[j] >= R[k])
        {
            arr[i] = R[k++];

            if(k == lenOfR)
            {
                for(int iter = i + 1; iter <= endOfR; iter++)
                {
                    arr[iter] = L[j++];
                }

                break;
            }
        }
    }

    delete[] L, R;
}

void mergeSort (int (&arr)[8], int start, int end)
{
    if(start < end)
    {
        int middle = floor((start + end) / 2); // dijeli na dva sve dok ne dodes do leaf-a (len(arr) = 1)
    
        mergeSort(arr, start, middle);
        mergeSort(arr, middle + 1, end);

        merge(arr, start, middle, end);
    }
}



int main()
{
    int arr [] = {8, 2, 4, 9, 3, 6, 1, 2};

    for(auto i : arr) cout << i << " ";

    cout << endl;

    mergeSort(arr, 0, 7);

    for(auto i : arr) cout << i << " ";
}