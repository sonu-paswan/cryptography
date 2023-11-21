#include <bits/stdc++.h>
using namespace std;
#define ln "\n"

// autokey cipher
string autoKeyCipher(string str, int key)
{   key=key%26;
    string res;
    res += 'a' + (str[0] - 'a' + key) % 26;
    for (int i = 1; i < str.size(); i++)
    {
        int a = (str[i] - 'a' + str[i - 1] - 'a') % 26;
        res += 'a' + a;
    }
    return res;
}

string InverseAutoKeyCipher(string& str, int key)
{   key=key%26;
    string res;
    res += 'a' + (str[0] - 'a' - key + 26) % 26;
    
    for (int i = 1; i < str.size(); i++)
    {
        int a = ((str[i] - 'a') - (res[i - 1] - 'a') + 26) % 26;
        res += 'a' + a;
    }
    
    return res;
}



// vigenere cipher 
string VigenereEncrypt(string plaintext,string key) {
    string ciphertext;
    int keyIndex = 0;

    for (char c : plaintext) {
        if (isalpha(c)) {
            char encryptedChar = 'a' + (c - 'a' + key[keyIndex] - 'a') % 26;
            ciphertext += encryptedChar;
            keyIndex = (keyIndex + 1) % key.length();
        } else {
            ciphertext += c;
        }
    }

    return ciphertext;
}

string VigenereDecrypt(string& ciphertext,string& key) {
    string decryptedText;
    int keyIndex = 0;

    for (char c : ciphertext) {
        if (isalpha(c)) {
            char decryptedChar = 'a' + (c - 'a' - (key[keyIndex] - 'a') + 26) % 26;
            decryptedText += decryptedChar;
            keyIndex = (keyIndex + 1) % key.length();
        } else {
            decryptedText += c;
        }
    }

    return decryptedText;
}
int main()
{   cout<<"enter message for autoKeyCipher:";
    string m1;cin>>m1;
    cout<<"enter key for autoKeyCipher:";
    int k1;cin>>k1;
    string str=autoKeyCipher(m1,k1);
    cout<<"encrypted autokey: "<<str<<ln;
    cout<<"decrypted autokey: "<<InverseAutoKeyCipher(str,k1)<<ln;
    cout<<"enter message for vigenere:";
    string m2;cin>>m2;
    cout<<"enter key for vigenere:";
    string k2;cin>>k2;
    string str2=VigenereEncrypt(m2,k2);
    cout<<"encrypted vigenere: "<<str2<<ln;
    cout<<"decrypted vigenere: "<<VigenereDecrypt(str2,k2)<<ln;
    return 0;
}