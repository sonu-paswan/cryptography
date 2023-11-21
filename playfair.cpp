#include <bits/stdc++.h>
using namespace std;

const int SIZE = 5;

// Helper function to remove duplicate characters from a string
string removeDuplicateChars(const string &str)
{
    string result;
    for (char c : str)
    {
        if (find(result.begin(), result.end(), c) == result.end())
        {
            result += c;
        }
    }
    result.erase(remove(result.begin(), result.end(), 'j'), result.end());
    // cout<<result<<endl;
    return result;
}

// Helper function to prepare the key square
void prepareKeySquare(const string &key, char keySquare[SIZE][SIZE])
{
    string keyString = removeDuplicateChars(key + "abcdefghijklmnopqrstuvwxyz");

    int k = 0;
    for (int i = 0; i < SIZE; ++i)
    {
        for (int j = 0; j < SIZE; ++j)
        {
            keySquare[i][j] = keyString[k++];
        }
    }
}

// Helper function to find the row and column of a given character in the key square
void findPosition(char ch, char keySquare[SIZE][SIZE], int &row, int &col)
{
    if (ch == 'j')
    {
        ch = 'i'; // replace 'j' with 'i' in the key square
    }

    for (int i = 0; i < SIZE; ++i)
    {
        for (int j = 0; j < SIZE; ++j)
        {
            if (keySquare[i][j] == ch)
            {
                row = i;
                col = j;
                return;
            }
        }
    }
}

// Encrypts a pair of characters using the Playfair cipher
string encryptPair(char first, char second, char keySquare[SIZE][SIZE])
{
    int row1, col1, row2, col2;
    findPosition(first, keySquare, row1, col1);
    findPosition(second, keySquare, row2, col2);

    if (row1 == row2)
    {
        return string(1, keySquare[row1][(col1 + 1) % SIZE]) +
               string(1, keySquare[row2][(col2 + 1) % SIZE]);
    }
    else if (col1 == col2)
    {
        return string(1, keySquare[(row1 + 1) % SIZE][col1]) +
               string(1, keySquare[(row2 + 1) % SIZE][col2]);
    }
    else
    {
        return string(1, keySquare[row1][col2]) +
               string(1, keySquare[row2][col1]);
    }
}

// Decrypts a pair of characters using the Playfair cipher
string decryptPair(char first, char second, char keySquare[SIZE][SIZE])
{
    int row1, col1, row2, col2;
    findPosition(first, keySquare, row1, col1);
    findPosition(second, keySquare, row2, col2);

    if (row1 == row2)
    {
        return string(1, keySquare[row1][(col1 - 1 + SIZE) % SIZE]) +
               string(1, keySquare[row2][(col2 - 1 + SIZE) % SIZE]);
    }
    else if (col1 == col2)
    {
        return string(1, keySquare[(row1 - 1 + SIZE) % SIZE][col1]) +
               string(1, keySquare[(row2 - 1 + SIZE) % SIZE][col2]);
    }
    else
    {
        return string(1, keySquare[row1][col2]) +
               string(1, keySquare[row2][col1]);
    }
}

// Encrypts a plaintext using the Playfair cipher
string playfairEncrypt(const string &plaintext, const string &key)
{
    char keySquare[SIZE][SIZE];
    prepareKeySquare(key, keySquare);
    
    string ciphertext;
    for (int i = 0; i < plaintext.length(); i += 2)
    {
        char first = plaintext[i];
        char second = (i + 1 < plaintext.length()) ? plaintext[i + 1] : 'x';
        if (first == second)
        {
            second = 'x';
            i = i - 1;
        }
        ciphertext += encryptPair(first, second, keySquare);
    }

    return ciphertext;
}

// Decrypts a ciphertext using the Playfair cipher
string playfairDecrypt(const string &ciphertext, const string &key)
{
    char keySquare[SIZE][SIZE];
    prepareKeySquare(key, keySquare);

    string plaintext;
    for (int i = 0; i < ciphertext.length(); i += 2)
    {
        char first = ciphertext[i];
        char second = (i+1<ciphertext.length())?ciphertext[i + 1]:'x';
        plaintext += decryptPair(first, second, keySquare);
    }
    string ans="";
    for(int i=0;i<plaintext.size();i++){
        if(plaintext[i]=='x'){
            continue;
        }else{
            ans+=plaintext[i];
        }
    }
    return ans;
}

int main()
{
    string key = "nitap";
    string plaintext = "hello";

    cout << "Plain text: " << plaintext << endl;

    string encryptedText = playfairEncrypt(plaintext, key);
    cout << "Encrypted text: " << encryptedText << endl;

    string decryptedText = playfairDecrypt(encryptedText, key);
    cout << "Decrypted text: " << decryptedText << endl;

    return 0;
}
