#include<bits/stdc++.h>
using namespace std;

int gcd(int a,int b){
    if(a==0) return b;
    return gcd(b%a,a);
}
int extended_gcd(int a, int b){
    int r1=a, r2=b;
    int s1=1, s2=0;
    int t1=0, t2=1;
    int r,t,q,s;
    while(r2>0){
        q=r1/r2;

        r=r1-q*r2;
        r1=r2;r2=r;

        s=s1-q*s2;
        s1=s2;s2=s;

        t=t1-q*t2;
        t1=t2;t2=t;
    }
    if(t1<0) t1=a+t1%a;
    return t1;
}

int main(){
    cout<<"enter two numbers: ";
    int a, b;
    cin>>a>>b;
    cout<<"inverse of "<<b<<",in "<<a<<" is "<<extended_gcd(a,b)<<endl;
}