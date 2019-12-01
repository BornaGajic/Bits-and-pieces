#include <iostream>

using namespace std;

template <size_t S>
void bubbleSort(int (&arr)[S])
{
    int i = S - 1, border = 0;
    for(int x = S - 1; x >= 0; x--)
    {
        do
        {
            if(arr[i] <= arr[i - 1])
            {
                swap(arr[i], arr[(i - 1)]);
                i--;
            }
            else i--;
        }
        while(i > border);

        i = S - 1;
    }
}

int main()
{
    int arr [] = {8, 2, 4, 9, 3, 6, 1, 2};

    bubbleSort<8>(arr);
    
    cout << endl;
    for(auto i : arr) cout << i << " ";

    return 0;
}