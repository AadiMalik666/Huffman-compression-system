#ifndef USER_H
#define USER_H

#include <string>
#include <fstream>
#include <iostream>

using namespace std;

class User {
protected:
    string username;
    string password;

public:
    virtual void signup();
    virtual bool login();
    virtual string getUsername() const;
    void saveCredentialsToFile();
    bool checkCredentialsInFile(const string& uname, const string& pass);
    virtual ~User() {}
};

#endif