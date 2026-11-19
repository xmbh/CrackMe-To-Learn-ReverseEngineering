int main() {
    string password;
    string secret = "67Kebab";

    cout << "          MBH CRACK ME          " << endl;

    cout << "Enter the password: ";
    cin >> password;

    if (password == secret) {
        cout << "Password correct! You have cracked the code." << endl;
    } else {
        cout << "Incorrect password." << endl;
    }

    return 0;
}
