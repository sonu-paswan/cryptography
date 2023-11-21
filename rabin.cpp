#include <bits/stdc++.h>
using namespace std;

int gcd(int a, int b)
{
    if (a == 0)
        return b;
    return gcd(b % a, a);
}
int extended_gcd(int a, int b)
{
    if (gcd(a, b) == 1)
    {
        int r1 = max(a, b), r2 = min(a, b);
        int s1 = 1, s2 = 0;
        int t1 = 0, t2 = 1;
        int r, t, q, s;
        while (r2 > 0)
        {
            q = r1 / r2;

            r = r1 - q * r2;
            r1 = r2;
            r2 = r;

            s = s1 - q * s2;
            s1 = s2;
            s2 = s;

            t = t1 - q * t2;
            t1 = t2;
            t2 = t;
        }
        if (t1 < 0)
            return max(a, b) + t1;
        return t1;
    }
    return 0;
}
int rabinencr(int p_key, int plaintext)
{
    int c = plaintext % p_key;
    c = c * plaintext % p_key;
    return c;
}
int chinese(int a, int b, int p, int q)
{
    int M = p * q;
    int m1 = q, m2 = p;
    int m1in = extended_gcd(m1 % p, p);
    int m2in = extended_gcd(m2 % q, q);
    return (a * m1 * m1in + b * m2 * m2in) % M;
}
vector<int> Rabindecr(int p, int q, int c)
{
    int a1 = 1, a2 = 1, b1 = 1, b2 = 1;
    for (int i = 0; i < (p + 1) / 4; i++)
    {
        a1 = (a1 * c) % p;
    }
    for (int i = 0; i < (q + 1) / 4; i++)
    {
        b1 = (b1 * c) % q;
    }
    a2 = p - a1, b2 = q - b1;
    vector<int> ans(4);
    ans[0] = chinese(a1, b1, p, q);
    ans[1] = chinese(a1, b2, p, q);
    ans[2] = chinese(a2, b1, p, q);
    ans[3] = chinese(a2, b2, p, q);
    return ans;
}
int main()
{
    int p = 23, q = 7;
    int p_key = p * q;
    int plaintext;
    cout << "Enter message : ";
    cin >> plaintext;
    int cipher = rabinencr(p_key, plaintext);
    cout << "Encypted message : " << cipher << endl;
    vector<int> ans = Rabindecr(p, q, cipher);
    cout<<"Decrcypted in one following: \n";
    for (auto it : ans)
    {
        cout << it << " ";
    }
    return 0;
}