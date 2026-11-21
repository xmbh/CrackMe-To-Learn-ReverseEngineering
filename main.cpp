
#include <iostream>
#include <string>
#include <array>
#include <cstdint>

using namespace std;

using Byte = uint8_t;

constexpr size_t N = 12;

constexpr array<int, N> order = {
    7, 1, 10, 3, 0, 11,
    5, 8, 2, 9, 6, 4
};

constexpr array<Byte, N> target = {
    132, 227, 26, 154, 237, 234,
    240, 89, 44, 23, 89, 119
};

Byte rotl8(Byte value, unsigned int n) {
    return static_cast<Byte>(
        (value << n) | (value >> (8 - n))
    );
}

uint32_t rotl32(uint32_t value, unsigned int n) {
    return (value << n) | (value >> (32 - n));
}

bool verifyFormat(const string& key) {
    if (key.size() != N)
        return false;

    for (int i = 0; i < 8; i++) {
        if (key[i] < 'A' || key[i] > 'Z')
            return false;
    }

    for (int i = 8; i < 12; i++) {
        if (key[i] < '0' || key[i] > '9')
            return false;
    }

    return true;
}

bool verifyStage1(const string& key) {
    Byte state = 0x6D;

    for (int i = 0; i < 12; i++) {
        Byte value = static_cast<Byte>(key[order[i]]);

        value ^= static_cast<Byte>(0x31 + i * 13);

        value = rotl8(value, (i % 5) + 1);

        value = static_cast<Byte>(
            value + (0x17 ^ (i * 9))
        );

        value ^= state;

        if (value != target[i])
            return false;

        state = static_cast<Byte>(
            state + value + 0x23
        );
    }

    return true;
}

bool verifyStage2(const string& key) {
    uint32_t sum = 0;
    uint32_t mix = 0x31415927;

    for (int i = 0; i < 12; i++) {
        uint32_t c = static_cast<Byte>(key[i]);

        sum += (i + 3) * (c * c + 7 * i);

        mix = rotl32(mix, 5) ^
              (c + 0x9E3779B9u + i * 17);
    }

    return sum == 471599 &&
           mix == 0xA0A0B9E8;
}

string decryptFlag(const string& key) {
    constexpr array<Byte, 19> encrypted = {
        142, 80, 47, 34, 99,
        34, 189, 62, 69, 129,
        240, 218, 22, 65, 131,
        48, 45, 64, 22
    };

    string result;

    for (size_t i = 0; i < encrypted.size(); i++) {
        Byte value = static_cast<Byte>(
            key[(i * 7 + 3) % N]
        );

        Byte k = rotl8(
            static_cast<Byte>(
                value ^ static_cast<Byte>(0xA5 + i * 11)
            ),
            (i % 7) + 1
        );

        result += static_cast<char>(encrypted[i] ^ k);
    }

    return result;
}

int main() {
    string key;

    cout << "       MBH CRACKME v3           \n";
    
   

    cout << "\n[+] Initializing security...";
    cout << "\n[+] License verification ready.";
    cout << "\n\n[?] Enter license key: ";

    cin >> key;

    if (!verifyFormat(key) ||
        !verifyStage1(key) ||
        !verifyStage2(key)) {

        cout << "\n[-] ACCESS DENIED\n";
        cout << "[-] Invalid license key.\n";
        return 1;
    }

    cout << "\n[+] ACCESS GRANTED\n";
    cout << "[+] License verified.\n";

    cout << "\n[FLAG] " << decryptFlag(key) << "\n";

    return 0;
}
