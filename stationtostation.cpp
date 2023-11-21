#include <iostream>
#include <vector>
#include <random>
#include <functional>

using namespace std;

int power(int base, int exp, int mod) {
    int result = 1;
    base = base % mod;
    while (exp > 0) {
        if (exp % 2 == 1)
            result = (result * base) % mod;
        exp = exp >> 1;
        base = (base * base) % mod;
    }
    return result;
}

int performDHExchange(int base, int prime, int privateKey, int peerPublicKey) {
    return power(peerPublicKey, privateKey, prime);
}

vector<int> computeHMAC(const vector<int>& key, const vector<int>& message) {
    vector<int> result(key.size(), 0);

    for (size_t i = 0; i < key.size(); ++i) {
        result[i] = key[i] ^ message[i % message.size()];
    }

    return result;
}

int main() {
    int prime = 23;
    int base = 5;

    default_random_engine generator;
    uniform_int_distribution<int> distribution(2, prime - 2);
    auto randPrivateKey = bind(distribution, generator);

    int privateKeyAlice = randPrivateKey();
    int privateKeyBob = randPrivateKey();

    int publicKeyAlice = power(base, privateKeyAlice, prime);
    int publicKeyBob = power(base, privateKeyBob, prime);

    int sharedAlice = performDHExchange(base, prime, privateKeyAlice, publicKeyBob);
    int sharedBob = performDHExchange(base, prime, privateKeyBob, publicKeyAlice);

    cout<<"shared secret key of Alice: "<<sharedAlice<<endl;
    cout<<"shared secret key of Bob: "<<sharedBob<<endl;
    if (sharedAlice == sharedBob) {
        cout << "Shared secrets match. Secure key exchange successful!" << endl;

        vector<int> message = {'H', 'e', 'l', 'l', 'o'};
        vector<int> hmacKey(message.size(), sharedAlice);

        vector<int> hmacAlice = computeHMAC(hmacKey, message);
        vector<int> hmacBob = computeHMAC(hmacKey, message);

        if (hmacAlice == hmacBob) {
            cout << "HMACs match. Message authentication successful!" << endl;
        } else {
            cout << "Error: HMACs do not match. Message authentication failed." << endl;
        }
    } else {
        cout << "Error: Shared secrets do not match. Key exchange failed." << endl;
    }
    return 0;
}