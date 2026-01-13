#ifndef PASSENGER_H
#define PASSENGER_H

#include "User.h"
#include <string>
#include <regex>

using namespace std;

class Passenger : public User {
public:
    string name, email, contact;
    int age = 0;
    string seatClass;

    void getDetails();
    virtual double calculateFare(double base);
};

class ChildPassenger : public Passenger {
public:
    double calculateFare(double base) override;
};

class SeniorPassenger : public Passenger {
public:
    double calculateFare(double base) override;
};

Passenger* createPassengerByAge(int age);

#endif