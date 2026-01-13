#include "User.h"

void User::signup() {
    cout << "Create Username: ";
    cin >> username;
    cout << "Create Password: ";
    cin >> password;

    saveCredentialsToFile();

    cout << "Account created successfully!\n";
}

bool User::login() {
    string uname, pass;
    cout << "Enter Username: ";
    cin >> uname;
    cout << "Enter Password: ";
    cin >> pass;

    if (uname == username && pass == password) {
        cout << "Login successful!\n";
        return true;
    }
    else if (checkCredentialsInFile(uname, pass)) {
        username = uname;
        password = pass;
        cout << "Login successful!\n";
        return true;
    }
    else {
        cout << "Invalid credentials!\n";
        return false;
    }
}

string User::getUsername() const {
    return username;
}

void User::saveCredentialsToFile() {
    ofstream outFile("users.dat", ios::app);
    if (outFile.is_open()) {
        outFile << username << " " << password << endl;
        outFile.close();
    }
    else {
        cout << "Warning: Unable to save credentials to file.\n";
    }
}

bool User::checkCredentialsInFile(const string& uname, const string& pass) {
    ifstream inFile("users.dat");
    if (inFile.is_open()) {
        string fileUname, filePass;
        while (inFile >> fileUname >> filePass) {
            if (fileUname == uname && filePass == pass) {
                inFile.close();
                return true;
            }
        }
        inFile.close();
    }
    return false;
}