
#include <iostream>
#include <string>
#include <array>
#include <cstdint>

using namespace std;

constexpr int KEY_LENGTH = 10;

const array<uint8_t, KEY_LENGTH> target = {
    3, 20, 130, 120, 80,
    110, 138, 140, 27, 34
};

bool checkFormat(const string& input) {
    if (input.size() != KEY_LENGTH)
        return false;

    for (int i = 0; i < 6; i++) {
        if (input[i] < 'A' || input[i] > 'Z')
            return false;
    }

    for (int i = 6; i < KEY_LENGTH; i++) {
        if (input[i] < '0' || input[i] > '9')
            return false;
    }

    return true;
}

bool checkChecksum(const string& input) {
    unsigned int sum = 0;

    for (int i = 0; i < KEY_LENGTH; i++) {
        sum += (i + 1) *
               static_cast<unsigned char>(input[i]);
    }

    return sum == 3230;
}

bool checkEncryption(const string& input) {
    for (int i = 0; i < KEY_LENGTH; i++) {
        int index = (i * 3) % KEY_LENGTH;

        uint8_t value =
            static_cast<uint8_t>(input[index]);

        value ^= static_cast<uint8_t>(0x4D + i * 7);
        value = static_cast<uint8_t>(value + i * 11 + 3);

        if (value != target[i])
            return false;
    }

    return true;
}

int main() {
    string password;


    cout << "       MBH CRACKME Medium         \n";
  


    cout << "\n[+] Security system initialized";
    cout << "\n[+] Enter license key: ";

    cin >> password;

    if (checkFormat(password) &&
        checkChecksum(password) &&
        checkEncryption(password)) {

        cout << "\n[+] ACCESS GRANTED!\n";
        cout << "[+] Challenge completed!\n";

    } else {
        cout << "\n[-] ACCESS DENIED!\n";
        cout << "[-] Invalid license key.\n";
    }

    return 0;
}
