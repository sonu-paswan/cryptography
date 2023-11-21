#include <bits/stdc++.h>
#include "gcd.h"
using namespace std;
int N = 3;

void getCofactor(vector<vector<int>> &A, vector<vector<int>> &temp, int p, int q, int n)
{
    int i = 0, j = 0;

    for (int row = 0; row < n; row++)
    {
        for (int col = 0; col < n; col++)
        {
            if (row != p && col != q)
            {
                temp[i][j++] = A[row][col];

                if (j == n - 1)
                {
                    j = 0;
                    i++;
                }
            }
        }
    }
}

int Determinant(vector<vector<int>> &A, int n)
{
    int D = 0;

    if (n == 1)
        return A[0][0];

    vector<vector<int>> temp(N, vector<int>(N, 0));

    int sign = 1;

    for (int f = 0; f < n; f++)
    {
        getCofactor(A, temp, 0, f, n);
        D += sign * A[0][f] * Determinant(temp, n - 1);

        sign = -sign;
    }

    return D;
}

void adjoint(vector<vector<int>> &A, vector<vector<int>> &adj)
{
    if (N == 1)
    {
        adj[0][0] = 1;
        return;
    }

    vector<vector<int>> temp(N, vector<int>(N, 0));
    int sign = 1;

    for (int i = 0; i < N; i++)
    {
        for (int j = 0; j < N; j++)
        {
            getCofactor(A, temp, i, j, N);

            sign = ((i + j) % 2 == 0) ? 1 : -1;

            adj[j][i] = sign * Determinant(temp, N - 1);
        }
    }
}

vector<vector<int>> inverseMatrix(vector<vector<int>> &A)
{
    int det = Determinant(A, N);
    if(det<0){
        det = 26+det%26;
    }

    int inverseDet = extended_gcd(26, det % 26);
    
    vector<vector<int>> inverse(N, vector<int>(N, 0));
    vector<vector<int>> adj(N, vector<int>(N, 0));
    adjoint(A, adj);

    for (int i = 0; i < N; i++)
    {
        for (int j = 0; j < N; j++)
        {
            if(adj[i][j]<0){
                adj[i][j]=26+adj[i][j]%26;
            }
            inverse[i][j] = (adj[i][j] * inverseDet) % 26;
        }
    }

    cout << "inverse key matrix:\n";
    for (int i = 0; i < N; i++)
    {
        for (int j = 0; j < N; j++)
        {

            cout << inverse[i][j] << " ";
        }
        cout << endl;
    }

    return inverse;
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
string DecryptedHillCipher(vector<vector<int>> &plt, vector<vector<int>> &key)
{

    vector<vector<int>> inverseKey = inverseMatrix(key);
    return hillcipher(plt, inverseKey);
}
vector<vector<int>> ConvertStrToTable(string str)
{
    int len = str.size();
    int row = len % N == 0 ? len / N : (len / N) + 1;
    vector<vector<int>> plt(row, vector<int>(N, 0));

    int vogus = 25;

    for (int i = 0; i < N; i++)
    {
        for (int j = 0; j < row; j++)
        {
            int index = j*N+i;
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
    return plt;
}
int main()
{
    cout << "Enter Message: ";
    string str;
    cin >> str;

    vector<vector<int>> key(N, vector<int>(N));

    srand(static_cast<unsigned int>(time(0)));
    int determinant = 0;
    while (determinant == 0 || gcd(26, determinant % 26) != 1)
    {
        for (int i = 0; i < N; i++)
        {
            for (int j = 0; j < N; j++)
            {
                key[i][j] = rand() % 10 + 1;
            }
        }
        determinant = Determinant(key, N);
        if (determinant < 0)
        {
            determinant = 26 + determinant % 26;
        }
    }
    cout<<"orignal key matrix:\n";
    for (int i = 0; i < N; i++)
    {
        for (int j = 0; j < N; j++)
        {
            cout << key[i][j] << " ";
        }
        cout << endl;
    }
    vector<vector<int>> plt = ConvertStrToTable(str);
    string str2 = hillcipher(plt, key);
    cout << "encrypted message: " << str2 << endl;
    vector<vector<int>> plt2 = ConvertStrToTable(str2);
    string str3 = DecryptedHillCipher(plt2, key);
    cout << "decrypted message: " << str3;

    return 0;
}
