#include <bits/stdc++.h>
using namespace std;
int SIZE = 3;

int gcd(int a, int b)
{
    if (a == 0)
        return b;
    return gcd(b % a, a);
}

string hillcipher(vector<vector<int>> &plt, vector<vector<int>> &key)
{
    int row = plt.size(), col = plt[0].size();
    vector<vector<int>> result(row, vector<int>(col, 0));

    for (int i = 0; i < row; ++i)
    {
        for (int j = 0; j < col; ++j)
        {
            for (int k = 0; k < col; ++k)
            {
                result[i][j] += plt[i][k] * key[k][j];
            }
            result[i][j] %= 26; // Modulo 26 for the encryption
        }
    }

    string encr = "";
    for (int i = 0; i < row; i++)
    {
        for (int j = 0; j < col; j++)
        {
            encr += (char)(result[i][j] + 'a');
        }
    }

    return encr;
}

int main()
{   cout<<"enter message: ";
    string str;
    cin >> str;

    int len = str.size();
    vector<vector<int>> key(SIZE, vector<int>(SIZE));

    srand(static_cast<unsigned int>(time(0)));
    int determinant = 0;
    while (determinant == 0 || gcd(26, determinant % 26) != 1)
    {
        for (int i = 0; i < SIZE; i++)
        {
            for (int j = 0; j < SIZE; j++)
            {
                key[i][j] = rand() % 10 + 1;
            }
        }
        
        int First = key[0][0] * (key[1][1] * key[2][2] - key[2][1] * key[1][2]);
        int Second = key[0][1] * (key[2][2] * key[1][0] - key[2][0] * key[1][2]);
        int Third = key[0][2] * (key[1][0] * key[2][1] - key[2][0] * key[1][1]);
        determinant = First - Second + Third;
        if (determinant < 0)
        {
            determinant = 26 + determinant % 26;
        }
    }
    cout<<"Key\n";
    for (int i = 0; i < SIZE; i++)
    {
        for (int j = 0; j < SIZE; j++)
        {
            cout << key[i][j] << " ";
        }
        cout << endl;
    }
    cout<<"Determinant is : "<<determinant<<endl;
    int row = len % SIZE == 0 ? len / SIZE : (len / SIZE) + 1;
    vector<vector<int>> plt(row, vector<int>(SIZE, 0));

    int vogus = 25;

    for (int i = 0; i < SIZE; i++)
    {
        for (int j = 0; j < row; j++)
        {
            int index = i * row + j;
            if (index < len)
            {
                plt[j][i] = (int)str[index] - 'a';
            }
            else
            {
                plt[j][i] = vogus;
            }
        }
    }

    cout << hillcipher(plt, key);

    return 0;
}
