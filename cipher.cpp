#include <iostream>
#include <string>
#include "gcd.h"
using namespace std;



string additiveCipher(string str, int key)
{
    string res = "";
    for (int i = 0; i < str.size(); i++)
    {
        int a = (str[i] - 'a' + key) % 26;
        res += 'a' + a;
    }
    return res;
}

string InverseAdditiveCipher(string str, int key)
{
    int key2 = 26 - key % 26;

    string ans = additiveCipher(str, key2);
    return ans;
}

string multiplicativeCipher(string str, int key)
{
    if (gcd(key, 26) != 1)
    {
        cout << "Invalid key for multiplicative cipher. Choose another key.";
        return "-1";
    }
    string res = "";
    for (int i = 0; i < str.size(); i++)
    {
        int a = ((str[i] - 'a') * key) % 26;
        res += 'a' + a;
    }
    return res;
}

string InverseMultiplicativeCipher(string str, int key)
{
    int key2 = extended_gcd(26, key);
    if (key2 < 0)
    {
        key2 = key2 + 26;
    }
    string res = multiplicativeCipher(str, key2);
    return res;
}

string affineCipher(string str, int key, int key2)
{
    string temp = additiveCipher(str, key);
    string ans = multiplicativeCipher(temp, key2);
    return ans;
}

string InverseAffineCipher(string str, int key, int key2)
{
    string temp = InverseMultiplicativeCipher(str, key2);
    string ans = InverseAdditiveCipher(temp, key);
    return ans;
}

int main()
{
    int choice;
    cout << "Choose a cipher:" << endl;
    cout << "1. Additive Cipher" << endl;
    cout << "2. Multiplicative Cipher" << endl;
    cout << "3. Affine Cipher" << endl;

    cin >> choice;

    int key, key2;

    string str;
    cout << "Enter the message: ";
    cin >> str;

    string Text, Text2;

    switch (choice)
    {
    case 1:
        cout << "Enter key : ";
        cin >> key;
        Text = additiveCipher(str, key);
        Text2 = InverseAdditiveCipher(Text, key);
        break;
    case 2:
        cout << "Enter key : ";
        cin >> key;
        Text = multiplicativeCipher(str, key);
        Text2 = InverseMultiplicativeCipher(Text, key);
        break;
    case 3:
        cout << "Enter key and key2: ";
        cin >> key >> key2;
        Text = affineCipher(str, key, key2);
        Text2 = InverseAffineCipher(Text, key, key2);
        break;
    default:
        cout << "Invalid choice. Exiting..." << endl;
        return 1;
    }

    cout << "Encrypted cipher : " << Text << endl;
    cout << "Decrypted cipher : " << Text2 << endl;

    return 0;
}
