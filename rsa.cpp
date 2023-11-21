#include <bits/stdc++.h>
#include "gcd.h"
using namespace std;
typedef long long ll;

vector<ll> keyGen(ll p, ll q)
{
    ll n = p * q;
    ll track;
    ll phi = (p - 1) * (q - 1);

    ll e = 2;
    while (e < phi)
    {
        track = gcd(e, phi);
        if (track == 1)
            break;
        else
            e++;
    }
    ll temp = extended_gcd(phi, e);
    if (temp < 0)
    {
        temp = phi + temp % phi;
    }
    ll d = temp; // private key
    vector<ll> arr={e,n,d};
    return arr;
}
ll rsaEncrypt(ll P,ll e,ll n){
    ll C=1;
    for(int i=1;i<=e;i++){
        C=(C*P)%n;
    }
    return C;
}
ll rsaDecrypt(int C,int d,int n){
    int P=1;
    for(int i=1;i<=d;i++){
        P=(P*C)%n;
    }
    return P;
}
int main()
{
    cout << "enter two prime numbers :";
    ll p, q;
    cin >> p >> q;
    ll Pt;
    cout << "enter message: ";
    cin >> Pt;
    vector<ll> arr= keyGen(p, q);
    ll e=arr[0],n=arr[1],d=arr[2];
    ll C=rsaEncrypt(Pt,e,n);
    cout<<"encrypted message: "<<C<<endl;
    ll Dp=rsaDecrypt(C,d,n);
    cout<<"decrypted message: "<<Dp<<endl;
    return 0;
}