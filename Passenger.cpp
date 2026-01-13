#include "Passenger.h"

void Passenger::getDetails() {
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    cout << "Enter Full Name: ";
    getline(cin, name);

    do {
        cout << "Enter Age: ";
        cin >> age;
        if (cin.fail() || age <= 0 || age >= 120) {
            cout << "Invalid age. Please enter a valid age between 1 and 119.\n";
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }
        else break;
    } while (true);

    cin.ignore(numeric_limits<streamsize>::max(), '\n');

    regex email_pattern(R"(([\w.%+-]+)@([\w.-]+)\.([a-zA-Z]{2,}))");
    do {
        cout << "Enter Email: ";
        getline(cin, email);
        if (!regex_match(email, email_pattern)) {
            cout << "Invalid email format. Try again.\n";
        }
        else break;
    } while (true);

    cout << "Enter Contact Number: ";
    getline(cin, contact);

    cout << "Select Seat Class (business/standard): ";
    cin >> seatClass;

    while (seatClass != "business" && seatClass != "standard") {
        cout << "Invalid seat class. Enter 'business' or 'standard': ";
        cin >> seatClass;
    }
}

double Passenger::calculateFare(double base) {
    if (seatClass == "business") {
        return base * 1.5;
    }
    return base;
}

double ChildPassenger::calculateFare(double base) {
    if (seatClass == "business") {
        return base * 1.5 * 0.5;
    }
    return base * 0.5;
}

double SeniorPassenger::calculateFare(double base) {
    if (seatClass == "business") {
        return base * 1.5 * 0.7;
    }
    return base * 0.7;
}

Passenger* createPassengerByAge(int age) {
    if (age < 12)
        return new ChildPassenger();
    else if (age >= 60)
        return new SeniorPassenger();
    else
        return new Passenger();
}