#include <iostream>
#include <vector>
#include <fstream>
#include <string>

using namespace std;

// mreza labirinta
vector<vector<char>> matrix;

// kooridnate *
int x_start, y_start;

void print ()
{
    for (auto& x : matrix)
    {
        for (auto& c : x)
            cout << c;

        cout << endl;
    }

    return;
}

void solve (int i, int j)
{
    // ako je algoritam dosao do ruba labirinta; return
    if (i == 0 || i == matrix.size() - 1) return;
    if (j == 0 ||j == matrix[0].size() - 1) return;

    // svim susjedima udaljeni za jedan od matrix[i][j]
    // postavi ' ' => '#' ako je to moguce (nije zid).
    // nakon sto pormijenis u # pozovi istu fju na tom elementu.
    for (int k = i - 1; k <= i + 1; k++)
    {
        for (int l = j - 1; l <= j + 1; l++)
        {
            if (matrix[k][l] == ' ' || matrix[k][l] == '*')
            {
                matrix[k][l] = '#';
                solve(k, l);
            }
        }   
    }
    
    return;
}

int main ()
{
    ifstream labirint_file{"labirint.txt"};
    string line;

    if (labirint_file.is_open())
    {
        // za moje rjesenje nije potreban broj labirinta 
        getline(labirint_file, line);
        
        int i = 0;
        while (getline(labirint_file, line))
        {
            // ako pocinjes na - dosao sam do kraja trenutnog labirinta
            if (line[0] == '-')
            {
                // pozovi na koordinatu *
                solve(y_start, x_start);
                
                print();

                // pripremi matricu za novi labirint
                for (auto& x : matrix)
                    x.clear();                    
                matrix.clear();

                i = 0;

                continue;
            }
            else
            {
                // za svaki line u txt fileu pushaj novi vector
                matrix.push_back(vector<char>{});

                for(int j = 0; j < line.length(); j++)
                {
                    if(line[j] == '*')
                    {
                        x_start = j;
                        y_start = i;
                    }

                    matrix[i].push_back(line[j]);
                }
                    
                i++;
            }
        }

        labirint_file.close();
    }

    return 0;
}