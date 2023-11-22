#include <bits/stdc++.h>

using namespace std;

int pc1[] = {57, 49, 41, 33, 25, 17, 9, 1,
             58, 50, 42, 34, 26, 18, 10, 2,
             59, 51, 43, 35, 27, 19, 11, 3,
             60, 52, 44, 36, 63, 55, 47, 39,
             31, 23, 15, 7, 62, 54, 46, 38,
             30, 22, 14, 6, 61, 53, 45, 37,
             29, 21, 13, 5, 28, 20, 12, 4};

int leftShifts[] = {1, 1, 2, 2, 2, 2, 2, 2, 1, 2, 2, 2, 2, 2, 2, 1};

int pc2[] = {14, 17, 11, 24, 1, 5, 3, 28,
             15, 6, 21, 10, 23, 19, 12, 4,
             26, 8, 16, 7, 27, 20, 13, 2,
             41, 52, 31, 37, 47, 55, 30, 40,
             51, 45, 33, 48, 44, 49, 39, 56,
             34, 53, 46, 42, 50, 36, 29, 32};

string bin2hex(string str)
{
    map<string, char> mp = {{"0000", '0'},{"0001", '1'},{"0010", '2'},{"0011", '3'},
                            {"0100", '4'},{"0101", '5'},{"0110", '6'},{"0111", '7'},
                            {"1000", '8'},{"1001", '9'},{"1010", 'a'},{"1011", 'b'},
                            {"1100", 'c'},{"1101", 'd'},{"1110", 'e'},{"1111", 'f'}};
    string s = "";
    for (int i = 0; i < str.size(); i += 4)
    {
        string temp = str.substr(i, 4);
        s += mp[temp];
    }
    return s;
}



vector<string> generateRoundKeys(string originalKey){
    // Apply initial permutation choice
    string keyAfterPC1="";
    for (int i = 0; i < 56; ++i)
        keyAfterPC1+=originalKey[pc1[i] - 1];
    //cout<<bin2hex(keyAfterPC1)<<endl;
    // Split the key into C and D halves
    string C="", D="";
    for (int i = 0; i < 28; ++i)
    {
        C+=keyAfterPC1[i];
        D+=keyAfterPC1[i + 28];
    }

    // Generate 16 subkeys
    vector<string> roundKeys;
    for (int round = 0; round < 16; round++){
        // Perform key rotation
        for (int i = 0; i < leftShifts[round]; i++){
            char tempL = C[0];
            char tempR = D[0];
            for (int j = 1; j <= 27; j++) C[j - 1] = C[j], D[j - 1] = D[j];
            C[27] = tempL, D[27] = tempR;
        }

        // Combine C and D
        string combinedCD;
        combinedCD.reserve(56);
        for (int i = 0; i < 28; i++)
        {
            combinedCD[i] = C[i];
            combinedCD[i + 28] = D[i];
        }
        // Apply permutation choice 2 (PC-2)
        string roundKey="";
        for (int i = 0; i < 48; ++i) roundKey+=combinedCD[pc2[i] - 1];
        roundKeys.push_back(roundKey);
    }
    return roundKeys;
}