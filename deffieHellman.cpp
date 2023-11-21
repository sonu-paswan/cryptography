#include <bits/stdc++.h>
#include "getpremitiveroot.h"
using namespace std;
int main()
{
    int q;
    cout << "Enter a large prime number : ";
    cin >> q;
    int a = prem_root(q);
    // Two user A and B
    cout << "Enter private number of A and B : ";
    int private_A, private_B;
    cin >> private_A >> private_B;
    int YA = 1, YB = 1;
    for (int i = 0; i < private_A; i++)
    {
        YA = (YA * a) % q;
    }
    for (int i = 0; i < private_B; i++)
    {
        YB = (YB * a) % q;
    }

    int kA=1,kB=1;
    for (int i = 0; i < private_A; i++)
    {
        kA = (kA * YB) % q;
    }
    for (int i = 0; i < private_B; i++)
    {
        kB = (kB * YA) % q;
    }
    cout<<"Key get by A : "<<kA<<" "<<"Key get by B : "<<kB;
    return 0;
}