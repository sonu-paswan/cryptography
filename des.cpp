#include <bits/stdc++.h>
#include "key_gen.h"

string hex2bin(string str)
{
    map<char, string> mp = {
        {'0', "0000"},{'1', "0001"},{'2', "0010"},{'3', "0011"},
        {'4', "0100"},{'5', "0101"},{'6', "0110"},{'7', "0111"},
        {'8', "1000"},{'9', "1001"},{'a', "1010"},{'b', "1011"},
        {'c', "1100"},{'d', "1101"},{'e', "1110"},{'f', "1111"},
    };
    string s = "";
    for (auto ch : str)
        s += mp[ch];
    return s;
}

int ip[64] = {58, 50, 42, 34, 26, 18, 10, 2,
              60, 52, 44, 36, 28, 20, 12, 4,
              62, 54, 46, 38, 30, 22, 14, 6,
              64, 56, 48, 40, 32, 24, 16, 8,
              57, 49, 41, 33, 25, 17, 9, 1,
              59, 51, 43, 35, 27, 19, 11, 3,
              61, 53, 45, 37, 29, 21, 13, 5,
              63, 55, 47, 39, 31, 23, 15, 7};

int fp[64] = {40, 8, 48, 16, 56, 24, 64, 32,
              39, 7, 47, 15, 55, 23, 63, 31,
              38, 6, 46, 14, 54, 22, 62, 30,
              37, 5, 45, 13, 53, 21, 61, 29,
              36, 4, 44, 12, 52, 20, 60, 28,
              35, 3, 43, 11, 51, 19, 59, 27,
              34, 2, 42, 10, 50, 18, 58, 26,
              33, 1, 41, 9, 49, 17, 57, 25};

int exp_d[48] = {32, 1, 2, 3, 4, 5, 4, 5,
                 6, 7, 8, 9, 8, 9, 10, 11,
                 12, 13, 12, 13, 14, 15, 16, 17,
                 16, 17, 18, 19, 20, 21, 20, 21,
                 22, 23, 24, 25, 24, 25, 26, 27,
                 28, 29, 28, 29, 30, 31, 32, 1};

int sbox[8][4][16] = {{{14, 4, 13, 1, 2, 15, 11, 8, 3, 10, 6, 12, 5, 9, 0, 7},
                       { 0, 15, 7, 4, 14, 2, 13, 1, 10, 6, 12, 11, 9, 5, 3, 8 },
                       { 4, 1, 14, 8, 13, 6, 2, 11, 15, 12, 9, 7, 3, 10, 5, 0 },
                       { 15, 12, 8, 2, 4, 9, 1, 7, 5, 11, 3, 14, 10, 0, 6, 13 }},

                      {{15, 1, 8, 14, 6, 11, 3, 4, 9, 7, 2, 13, 12, 0, 5, 10},
                       {3, 13, 4, 7, 15, 2, 8, 14, 12, 0, 1, 10, 6, 9, 11, 5},
                       {0, 14, 7, 11, 10, 4, 13, 1, 5, 8, 12, 6, 9, 3, 2, 15},
                       {13, 8, 10, 1, 3, 15, 4, 2, 11, 6, 7, 12, 0, 5, 14, 9}},

                      {{10, 0, 9, 14, 6, 3, 15, 5, 1, 13, 12, 7, 11, 4, 2, 8},
                       {13, 7, 0, 9, 3, 4, 6, 10, 2, 8, 5, 14, 12, 11, 15, 1},
                       {13, 6, 4, 9, 8, 15, 3, 0, 11, 1, 2, 12, 5, 10, 14, 7},
                       {1, 10, 13, 0, 6, 9, 8, 7, 4, 15, 14, 3, 11, 5, 2, 12}},

                      {{7, 13, 14, 3, 0, 6, 9, 10, 1, 2, 8, 5, 11, 12, 4, 15},
                       {13, 8, 11, 5, 6, 15, 0, 3, 4, 7, 2, 12, 1, 10, 14, 9},
                       {10, 6, 9, 0, 12, 11, 7, 13, 15, 1, 3, 14, 5, 2, 8, 4},
                       {3, 15, 0, 6, 10, 1, 13, 8, 9, 4, 5, 11, 12, 7, 2, 14}},

                      {{2, 12, 4, 1, 7, 10, 11, 6, 8, 5, 3, 15, 13, 0, 14, 9},
                       {14, 11, 2, 12, 4, 7, 13, 1, 5, 0, 15, 10, 3, 9, 8, 6},
                       {4, 2, 1, 11, 10, 13, 7, 8, 15, 9, 12, 5, 6, 3, 0, 14},
                       {11, 8, 12, 7, 1, 14, 2, 13, 6, 15, 0, 9, 10, 4, 5, 3}},

                      {{12, 1, 10, 15, 9, 2, 6, 8, 0, 13, 3, 4, 14, 7, 5, 11},
                       {10, 15, 4, 2, 7, 12, 9, 5, 6, 1, 13, 14, 0, 11, 3, 8},
                       {9, 14, 15, 5, 2, 8, 12, 3, 7, 0, 4, 10, 1, 13, 11, 6},
                       {4, 3, 2, 12, 9, 5, 15, 10, 11, 14, 1, 7, 6, 0, 8, 13}},

                      {{4, 11, 2, 14, 15, 0, 8, 13, 3, 12, 9, 7, 5, 10, 6, 1},
                       {13, 0, 11, 7, 4, 9, 1, 10, 14, 3, 5, 12, 2, 15, 8, 6},
                       {1, 4, 11, 13, 12, 3, 7, 14, 10, 15, 6, 8, 0, 5, 9, 2},
                       {6, 11, 13, 8, 1, 4, 10, 7, 9, 5, 0, 15, 14, 2, 3, 12}},

                      {{13, 2, 8, 4, 6, 15, 11, 1, 10, 9, 3, 14, 5, 0, 12, 7},
                       {1, 15, 13, 8, 10, 3, 7, 4, 12, 5, 6, 11, 0, 14, 9, 2},
                       {7, 11, 4, 1, 9, 12, 14, 2, 0, 6, 10, 13, 15, 3, 5, 8},
                       {2, 1, 14, 7, 4, 10, 8, 13, 15, 12, 9, 0, 3, 5, 6, 11}}};

int s_per[32] = {16, 7, 20, 21,
                 29, 12, 28, 17,
                 1, 15, 23, 26,
                 5, 18, 31, 10,
                 2, 8, 24, 14,
                 32, 27, 3, 9,
                 19, 13, 30, 6,
                 22, 11, 4, 25};

string xora(string a, string b, int n)
{
    string s = "";
    for (int i = 0; i < n; i++)
    {
        if (a[i] == b[i])
            s += '0';
        else
            s += '1';
    }
    return s;
}

string substitute(string inBlock)
{
    string out="";
    int inBl[48];
    for(int i=0;i<48;i++) inBl[i]=(inBlock[i]=='0')?0:1;
    //for(auto it:inBl) cout<<it<<" ";
    for (int i = 0; i < 8; i++)
    {
        int row = ((2 * inBl[6 * i]) + (inBl[6 * i + 5]));
        int col = ((8 * inBl[6 * i + 1]) + (4 * inBl[6 * i + 2]) + (2 * inBl[6 * i + 3]) + (inBl[6 * i + 4]));
        //cout<<"Row: "<<row<<" "<<"Col: "<<col<<endl;
        int val = sbox[i][row][col];
        out += (int(val / 8)) == 0 ? '0' : '1';
        val = val % 8;
        out += (int(val / 4)) == 0 ? '0' : '1';
        val = val % 4;
        out += (int(val / 2)) == 0 ? '0' : '1';
        val = val % 2;
        out += (int(val)) == 0 ? '0' : '1';
    }
    return out;
}

string f(string in, string rk)
{
    string out = "";
    string afterPerm = "";
    for (int i = 0; i < 48; i++) afterPerm += in[exp_d[i] - 1];
    //cout<<"In f: "<<afterPerm<<endl; 
    string ap = xora(afterPerm, rk, 48);
    //cout<<"After Xor: "<<ap<<endl;
    string t1 = substitute(ap);
    //cout<<"After substitution: "<<t1<<endl;
    for (int i = 0; i < 32; i++) out += t1[s_per[i] - 1];
    //cout<<"t2: "<<out<<endl;
    return out;
}

string mixer(string left, string right, string keyo)
{
    string t1 = right;
    string t2 = f(t1, keyo);
    //cout<<"Left before: "<<left<<endl;
    left = xora(left, t2, 32);
    //cout<<"Left after: "<<left<<endl;
    return left;
}

string encrypt(string plainBlock, vector<string> key)
{
    // initial permutation
    string afterperm1 = "";
    for (int i = 0; i < 64; i++)
        afterperm1 += plainBlock[ip[i] - 1];
    //cout << "After Perm1: " << bin2hex(afterperm1) << endl;
    // now we need to split into left and right
    string left = "", right = "";
    for (int i = 0; i < 32; i++)
        left += afterperm1[i], right += afterperm1[i + 32];

    // now going for 16 rounds
    for (int round = 0; round < 16; round++)
    {
        // the main
        left = mixer(left, right, key[round]);
        if (round != 15)
        {
            string temp;
            temp = left;
            left = right;
            right = temp;
        }

        cout << "Left: " << bin2hex(left) << " ";
        cout << "Right: " << bin2hex(right) << " ";
        cout << "Round " << round + 1 << " : " << bin2hex(key[round]) << endl;
    }
    // combining the left and right
    string combined;
    combined.reserve(64);
    for (int i = 0; i < 32; i++){
        combined[i] = left[i];
        combined[i + 32] = right[i];
    }

    cout<<bin2hex(combined)<<endl;
    // the final permutation
    string finalPerm = "";
    for (int i = 0; i < 64; i++)
        finalPerm += combined[fp[i] - 1];
    return finalPerm;
}

int main()
{
    string inp, k;
    cin >> inp >> k;
    string oriKey = hex2bin(k);
    string input = hex2bin(inp);
    vector<string> s = generateRoundKeys(oriKey);
    //for(auto it:s) cout<<bin2hex(it)<<endl;
    string e = encrypt(input, s);
    cout<<"Encrypted Message: " <<bin2hex(e) << endl;
    cout<<"\n";
    reverse(s.begin(),s.end());
    string ans=bin2hex(encrypt(e,s));
    cout<<"Decrypted Message: "<<ans<<endl;;
    return 0;
}